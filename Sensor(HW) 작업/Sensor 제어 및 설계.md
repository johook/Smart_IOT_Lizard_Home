# Sensor 제어 및 설계

## 온습도 제어, 먹이(급양기, 급수기), 설계(엔지니어링) 작업

### 급양기, 급수기(일정 시간이 되면 주는 것, 양 조절)
-  **급양기(Motor.c)**
	-  스텝모터를 활용한 자동 급양기 구현
일정 시간(양 조절, 시간 조절)이 되면 통이 돌아가면서 먹이(귀뚜라미) 떨어뜨려 주기
![설계서1](https://github.com/johook/Data-Synchronization/assets/116954375/b4809ec4-d3a7-4c13-a818-dd5aec4b960c)
![설계서2](https://github.com/johook/Data-Synchronization/assets/116954375/a488c040-2d2a-4f23-8713-eca155e081b9)
![설계서3](https://github.com/johook/Data-Synchronization/assets/116954375/e11ba607-e43e-4c24-8216-1385af8be1a3)
![급양기](https://github.com/johook/Data-Synchronization/assets/116954375/c52e4f42-a2ef-4bcb-9486-d0ddf26b53da)

		**스텝모터**
		 <Motor.c Mechanism>
    
	   급양기 회전부의 칸 수가 총 8칸이고 회전부 하판은 45도 각도로 한 칸 크기 정도 구멍이 뚫려있다.
    
	   스텝모터와 회전부 고정판을 연결하여 특정시간이 되면 급양기를 45*n도(n= 특정시간이 되었을 때의 count 수, count는 특정시간이 될 때마다 +1해줌)만큼 돌려줌
   
		<스텝모터 구동원리>
![스텝모터 구동원리](https://github.com/johook/Data-Synchronization/assets/116954375/caa2e877-521e-44b9-8eb8-0ca23b66bb6c)

		S극 전자석 A,B,C,D에 전류를 흘러주면 자기력이 발생하여 중앙에 있는 N극 전자석이 전류에 따른 자기력을 따라 정렬

		예를들어 표의 2번처럼 A와B에 전류를 흘려준다면 두번째 그림의 2번처럼 N극 전자석이 A와B 사이에 위치함

		이런식으로 전류를 360도 돌려주면 모터는 360도 회전, 특정각도를 원하면 전류를 바꿔주면 된다.

- **<온습도 센서 DHT11 / DHT.c Test> - DHT센서 2개를 양쪽 끝에 배치하여 각각의 온도, 습도 값을 받아오고 평균값을 구해 저장 → 스팟램프와 연결하여 전원 on,off**
   **<문제>** - DHT센서의 값을 끊임없이 받아와야 하는데 최대 50회(1분 가량) 받아오면 어떤 이유인지 프로그램이 멈추며 더이상 받아지지 않음
   
   **<1차 문제 해결>** - DHT-브레드보드, DHT-전선 사이의 틈이 생겨 신호를 적절히 못 받아온다고 판단

	1.  DHT-전선을 납땜 하여 틈 없이 밀착 시켜줌
	2.  여전히 1분 이내로 프로그램이 멈추며 값을 받아오지 않음

   **<2차 문제 해결>** - 타이밍 문제(프로그램은 최초 High에서 Low가 오길 기다리는데, 센서는 Low를 넘어 다음 High에 가 있어서 만날 수 없음)

	1.  무한Loop코드를 수정
    
	2.  GetRespons, ReadData 함수에서 High와 Low인 상태의 대기 시간이 일정 시간 이상 길어질 경우
        
	3.  음수의 값을 받고
        
	4.  Run함수에서 해당 While(for)문 에서Continue
        

   **<스팟램프와 연결>** - average 함수에서 **(avrData[2]+(avrData[3]/10)** 즉 평균 온도가 TEMP(25)보다 작으면 스팟램프를 키고 커지면 끔
	
