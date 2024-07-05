import asyncio  # 비동기화 통신을 위한 라이브러리
import bleak  # bleak 라이브러리
from bleak import BleakClient

# ESP32 맥 주소
address = "40:F5:20:70:62:66"
# ESP32 BLE_notify 예제에 있는 캐릭터리스틱 주소
notity_charcteristic_uuid = "0000abf2-0000-1000-8000-00805f9b34fb"

# ESP32가 notify로 보낸 데이터를 받는 콜백 함수
def notify_callback(sender: int, data: bytearray):
    print('sender: ', sender, 'data: ', data)

async def run(address):
    # BleakClient 클래스 생성 및 바로 연결 시작
    # address: ESP32 맥주소
    # timeout: 연결 제한 시간 5초가 넘어가면 더 이상 연결하지 말고 종료
    async with BleakClient(address, timeout=5.0) as client:
        # 연결을 성공함
        print('connected')
        # 연결된 BLE 장치의 서비스 요청
        services = await client.get_services()
        # 서비스들을 루프 돌려 내부 캐릭터리스틱 정보 조회
        for service in services:
            print('service uuid:', service.uuid)
            # 각 서비스들에 있는 캐릭터리스틱을 루프 돌려 속성들 파악하기
            for characteristic in service.characteristics:
                print('  uuid:', characteristic.uuid)
                # handle 정보도 함께 확인
                print('  handle:', characteristic.handle)
                print('  properties: ', characteristic.properties)
                # 캐릭터리스틱 UUID가 우리가 찾는 UUID인지 먼저 확인
                if characteristic.uuid == notity_charcteristic_uuid:
                    # 우리가 찾던 UUID가 맞다면
                    # 해당 캐릭터리스틱에 notify 속성이 있는지 확인
                    if 'notify' in characteristic.properties:
                        # notify 속성이 있다면 BLE 장치의 notify 속성을
                        # 활성화 작업 후 notify_callback 함수 연결
                        print('try to activate notify.')
                        await client.start_notify(characteristic, notify_callback)
        
        # 데이터 수신을 무한 루프로 유지 (KeyboardInterrupt로 종료될 때까지)
        try:
            while client.is_connected:
                await asyncio.sleep(1)
        except KeyboardInterrupt:
            print('KeyboardInterrupt received, stopping notify and disconnecting...')
            await client.stop_notify(notity_charcteristic_uuid)

    print('disconnect')

loop = asyncio.get_event_loop()
try:
    loop.run_until_complete(run(address))
except KeyboardInterrupt:
    print('Program interrupted by user.')
finally:
    loop.close()
print('done')
