int GetRespons()
{
	int tm1 = micros();
	pinMode(p1, INPUT);
	while(digitalRead(p1)== HIGH)
	{
		if(micros() - tm1 > 1000000) return -1;
	}
	int st = micros();
	tm1 = micros();
	while(digitalRead(p1)== LOW)
	{
		if(micros() - tm1 > 1000000) return -2;
	}
	int en = micros();
	tm1 = micros();
	while(digitalRead(p1)== HIGH)
	{
		if(micros() - tm1 > 1000000) return -3;
	}
	if(en - st < 20) return -1;
	return 0;
}

int ReadData()
{
	int st ,en;
	for (int i = 0; i < MAX_BIT; i++) Data[i] = 0;
	for (int i = 0; i < MAX_BIT; i++)
	{
		int tm1 = micros();
		while(digitalRead(p1)== LOW)
		{
			if(micros() - tm1 > 1000000) return -4;
		}
		st = micros();
		tm1 = micros();
		while(digitalRead(p1)== HIGH)
		{
			if(micros() - tm1 > 1000000) return -5;
		}
		en = micros();
		Data[i/8] <<= 1;
		if(en - st > THRASHOLD)Data[i/8] |=1;
	}
	if (Data[0] + Data[1] + Data[2] + Data[3] == Data[4])return 1;
	return 0;
}

void Run()
{
	for(int i=0; i<1;i++)
	{
		StartSignal();
		int r = GetRespons();
		printf("<%d>",co);
		co++;
		if(r < 0) 
		{
			printf("%d",r);
			continue;
		}

		int ret = ReadData();
		tret=ret;
		if(ret < 0)
		{
			printf("%d", ret);
			continue;
		}
		printf("습도 :  %d.%d%% 온도 : %d.%d℃ Checksum : %d", Data[0], Data[1], Data[2], Data[3], Data[4]);
		if (ret == 1)
		{
			printf("...OK\n");
		}
		else 
		{
			printf("...ERROR!\n");
		}
				
		delay(1000);
	}
	
}

void average()
{
	avrData[0]=((double)Data[0]+(double)Data2[0])/2;
	avrData[1]=((double)Data[1]+(double)Data2[1])/2;
	avrData[2]=((double)Data[2]+(double)Data2[2])/2;
	avrData[3]=((double)Data[3]+(double)Data2[3])/2;
	printf("<평균>  습도 :  %.1f%% 온도 : %.1f℃", avrData[0]+(avrData[1]/10), avrData[2]+(avrData[3]/10));
	if (tret==2)
	{
		printf("...OK\n");
		if(avrData[2]+(avrData[3]/10) < TEMP)  //TEMP = 25
		{
			digitalWrite(pin_L,1);
		}
		else
		{
			digitalWrite(pin_L,0);
		}
	}
	else 
	{
		printf("...ERROR!\n");
	}
}
