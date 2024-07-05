import asyncio
import pandas as pd
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
    global received_data
    received_data.append(data.decode("utf-8"))
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
                received_data.append("S")
                await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
                is_receiving = True
                print("Started receiving notifications..." + "time : " + str(k))
            
            elif len(user_input)==0 and is_receiving:
                await client.stop_notify(CHARACTERISTIC_UUID)
                received_data.append("E")
                
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


def get_pitch(ax,ay,az):
    return math.atan2(ay,math.sqrt(ax*ax+az*az))
def get_roll(ax,ay,az):
    return math.atan2(ax,math.sqrt(ay*ay+az*az))


#start data preprocessing...
#print(received_data)
sliced_data = []

while len(received_data)>1:
    start = received_data.index('S')
    end = received_data.index('E')
    sliced_data.append(received_data[start+1:end])
    received_data = received_data[end+1:]


for i in range(len(sliced_data)):
    for j in range(len(sliced_data[i])):
        sliced_data[i][j] = sliced_data[i][j].split(',')
        sliced_data[i][j][0] = int(sliced_data[i][j][0])
        for k in range(1,len(sliced_data[i][j])):
            sliced_data[i][j][k]=float(sliced_data[i][j][k])

# set time
# set gyro to radian
# append roll and pitch
for i in range(len(sliced_data)):
    start = sliced_data[i][0][0]
    for j in range(len(sliced_data[i])):
        sliced_data[i][j][1] *= (math.pi/180.0)
        sliced_data[i][j][2]*= (math.pi/180.0)
        sliced_data[i][j][3]*= (math.pi/180.0)
        sliced_data[i][j][0] = sliced_data[i][j][0] - start
        sliced_data[i][j].append(get_pitch(sliced_data[i][j][4],sliced_data[i][j][5],sliced_data[i][j][6]))
        sliced_data[i][j].append(get_roll(sliced_data[i][j][4],sliced_data[i][j][5],sliced_data[i][j][6]))
        

# set index
for i in range(len(sliced_data)):
    for j in range(len(sliced_data[i])):
        sliced_data[i][j].insert(0,i)

#print(sliced_data)
df = pd.DataFrame(columns=['num','time','gX','gY','gZ','aX','aY','aZ','pitch','roll'])
for i in range(len(sliced_data)):
    for j in range(len(sliced_data[i])):
        df.loc[len(df)] = sliced_data[i][j]

print(df.head())
df.to_csv('dfcsv.csv',index=False)