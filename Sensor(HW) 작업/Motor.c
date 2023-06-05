void setsteps(int n1, int n2, int n3, int n4) //S극 전자석의 전류를 흘려줄 수 있도록 세팅
{
	pinMode(IN1, OUTPUT);
	digitalWrite(IN1, n1);
	pinMode(IN2, OUTPUT);
	digitalWrite(IN2, n2);
	pinMode(IN3, OUTPUT);
	digitalWrite(IN3, n3);
	pinMode(IN4, OUTPUT);
	digitalWrite(IN4, n4);
}

void forward(int br, int steps) //모터를 시계 방향으로 돌려주는 함수
{
	int i;
	for (i = 0; i <= steps; i++)   //steps수만큼 1step을 돌려준다.
	{
		setsteps(1, 1, 0, 0); delay(br);  //delay(br) : 속도를 조절해줌
		setsteps(0, 1, 0, 0); delay(br);
		setsteps(0, 1, 1, 0); delay(br);
		setsteps(0, 0, 1, 0); delay(br);
		setsteps(0, 0, 1, 1); delay(br);
		setsteps(0, 0, 0, 1); delay(br);
		setsteps(1, 0, 0, 1); delay(br);
		setsteps(1, 0, 0, 0); delay(br);
	}
}

void backward(int br, int steps) //모터를 반시계 방향으로 돌려주는 함수
{
	int i;
	for (i = 0; i <= steps; i++)
	{
		setsteps(1, 0, 0, 0); delay(br);
		setsteps(1, 0, 0, 1); delay(br);
		setsteps(0, 0, 0, 1); delay(br);
		setsteps(0, 0, 1, 1); delay(br);
		setsteps(0, 0, 1, 0); delay(br);
		setsteps(0, 1, 1, 0); delay(br);
		setsteps(0, 1, 0, 0); delay(br);
		setsteps(1, 1, 0, 0); delay(br);
	}
}

int main() //특정시간이 되면 급양기를 45*n도(n= 특정시간이 되었을 때의 count 수, count는 특정시간이 될 때마다 +1해줌)만큼 돌려줌
{
	wiringPiSetup();
	time_t current;
	struct  tm* t;
	
	current = time(NULL);
	t = localtime(&current);

	//시간이 00:00:00이면 while loop 돌려줌
	while (1)
	{
		if (t->tm_hour == 0 && t->tm_min == 0 && t->tm_sec == 0)
		{
			count++;
			if (count == 8) break; //급양기의 칸이 7칸만 사용가능->7번만 돌아야함
			for (int i = count; i < count + 1; i++)
			{
				forward(speed, STEP * i); delay(2000);
				backward(speed, STEP * i); delay(2000);
			}
		}
	]
		
	return 0;
}
