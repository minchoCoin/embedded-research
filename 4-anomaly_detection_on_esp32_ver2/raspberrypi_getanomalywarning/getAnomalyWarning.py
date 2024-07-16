import asyncio
import pandas as pd
import datetime
import math
from bleak import BleakClient

# 블루투스 기기의 주소와 알림을 받을 특성의 UUID를 정의합니다.
DEVICE_ADDRESS = "40:F5:20:70:62:66"
CHARACTERISTIC_UUID = "0000abf2-0000-1000-8000-00805f9b34fb"

# 알림을 받을 문자열 배열을 정의합니다.
received_data = []

# 알림을 처리할 콜백 함수입니다.
def notification_handler(sender, data):
    # 바이트 데이터를 문자열로 변환하여 배열에 추가합니다.
    now=datetime.datetime.now()
    global received_data
    print(now.strftime('%Y-%m-%d %H:%M:%S') + ';'+data.decode("utf-8"))
    received_data.append(now.strftime('%Y-%m-%d %H:%M:%S') + ';'+data.decode("utf-8"))
    #print(f"Received notification: {data.decode('utf-8')}")

async def main():
    global received_data
    client = BleakClient(DEVICE_ADDRESS)
    await client.connect()
    await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
    print('anomaly recevied starting...')
    try:
        while client.is_connected:
            await asyncio.sleep(1)
    
    except KeyboardInterrupt:
        print('KeyboardInterrupt received, stopping notify and disconnecting...')
        await client.stop_notify(CHARACTERISTIC_UUID)
        await client.disconnect()

# 비동기 함수 실행
loop = asyncio.get_event_loop()
try:
    loop.run_until_complete(main())
except KeyboardInterrupt:
        print("Program interrupted by user")
finally:
    loop.close()
    print("Event loop closed")

# received data 처리
df = pd.DataFrame(columns=['time','gx','gy','gz','ax','ay','az','pitch','roll','anomaly_index','anomaly_value','expected_value'])
df.astype('float')
df.astype({'time':'str','anomaly_index':'int'})

for data in received_data:
    raw_data = data.split('\n')[0].strip()
    anomaly_info = data.split('\n')[1].strip()

    time = raw_data.split(';')[0].strip()
    gyro_acce_values = raw_data.split(';')[2].split(',')

    gx = float(gyro_acce_values[0].strip())
    gy = float(gyro_acce_values[1].strip())
    gz = float(gyro_acce_values[2].strip())
    ax = float(gyro_acce_values[3].strip())
    ay = float(gyro_acce_values[4].strip())
    az = float(gyro_acce_values[5].strip())
    pitch = float(gyro_acce_values[6].strip())
    roll = float(gyro_acce_values[7].strip())

    anomaly_index = int(anomaly_info.split(':')[1].strip())
    anomaly_value = float(anomaly_info.split(':')[2].strip())
    expected_value = float(anomaly_info.split(':')[4].strip())
     
    df.loc[len(df)] = [time,gx,gy,gz,ax,ay,az,pitch,roll,anomaly_index,anomaly_value,expected_value]

print(df.head())
df.to_csv('anomaly_detection_data.csv',index=False)