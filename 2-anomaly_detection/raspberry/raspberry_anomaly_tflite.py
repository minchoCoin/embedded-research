import asyncio
import pandas as pd
import math
import numpy as np
from keras.utils import pad_sequences
from keras.layers import Masking
from tensorflow.python.client import device_lib
from keras.models import Model
from keras.layers import Input, LSTM, RepeatVector, TimeDistributed, Dense
from keras.callbacks import EarlyStopping
import keras
import tensorflow as tf
from pickle import load
from bleak import BleakClient

# 블루투스 기기의 주소와 알림을 받을 특성의 UUID를 정의합니다.
DEVICE_ADDRESS = "40:F5:20:70:62:66"
CHARACTERISTIC_UUID = "0000abf2-0000-1000-8000-00805f9b34fb"

# 알림을 받을 문자열 배열을 정의합니다.
received_data = []
interpreter = tf.lite.Interpreter(model_path = 'model.tflite')
interpreter.allocate_tensors()
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()
with open('minmax_scaler.pkl', 'rb') as f:
    scaler = load(f)
def calculate_error(original,reconstructed):
  return np.mean(np.abs(original-reconstructed),axis=(1))

def get_pitch(ax,ay,az):
    return math.atan2(ay,math.sqrt(ax*ax+az*az))
def get_roll(ax,ay,az):
    return math.atan2(ax,math.sqrt(ay*ay+az*az))
# 알림을 처리할 콜백 함수입니다.
def notification_handler(sender, data):
    global received_data
    # 바이트 데이터를 문자열로 변환하여 배열에 추가합니다.
    tmp = data.decode("utf-8").split(',')[1:]
    for i in range(len(tmp)):
        tmp[i] = float(tmp[i])
    tmp.append(get_pitch(tmp[3],tmp[4],tmp[5]))
    tmp.append(get_roll(tmp[3],tmp[4],tmp[5]))
    received_data.append(tmp)

    scaled_data = scaler.transform(received_data)
    sequences = [scaled_data]
    sequences = np.array(sequences)

    interpreter.set_tensor(input_details[0]['index'],sequences)
    interpreter.invoke()
    output_data = interpreter.get_tensor(output_details[0]['index'])

    reconstructed_error = calculate_error(sequences,output_data)
        
    anomalies = reconstructed_error> 1
    for i in range(len(anomalies)):
        if len(np.where(anomalies[i]==1))>0:
            print('anomalies detected: ',received_data[i])
    received_data = []
    
    #print(f"Received notification: {data.decode('utf-8')}")

async def wait_for_input():
    loop = asyncio.get_running_loop()
    return await loop.run_in_executor(None, input, "Press Enter...\n")

async def wait_for_end():
    loop = asyncio.get_running_loop()
    await loop.run_in_executor(None, input, "Press Enter to end...\n")

async def main():
    k=0
    global received_data
    client = BleakClient(DEVICE_ADDRESS)
    is_receiving=False
    await client.connect()
    try:
        while True:
            user_input=await wait_for_input()
            if len(user_input)==0 and not is_receiving:
                k=k+1
                await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
                is_receiving = True
                print("Started receiving notifications..." + "time : " + str(k))
            
            elif len(user_input)==0 and is_receiving:
                await client.stop_notify(CHARACTERISTIC_UUID)
                #received_data = received_data[:len(received_data) - received_data[-1::-1].index("E")]
                is_receiving = False
                print("Stopped receiving notifications.")
                #print("Received data:", received_data)
            
            elif len(user_input)>0:
                if is_receiving:
                    await client.stop_notify(CHARACTERISTIC_UUID)
                await client.disconnect()
                received_data.append('T')
                print("Exiting program.")
                break
            
            else:
                print("Invalid input.")
    except Exception as e:
        print(f"An error occurred: {e}")
        if is_receiving:
            await client.stop_notify(CHARACTERISTIC_UUID)
        await client.disconnect()

# 비동기 함수 실행
asyncio.run(main())

