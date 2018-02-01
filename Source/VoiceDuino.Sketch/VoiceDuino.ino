#include <Bridge.h>
#include <stdio.h>

#define M1_1  	5 
#define M1_2  	4
#define M2_1  	6 
#define M2_2  	7
#define M_SPEED	127

char data[10];
byte command;
unsigned long value;
unsigned long long stime;
 
void stop() 
{
	analogWrite(M1_1, 0);
	digitalWrite(M1_2, 0);
	analogWrite(M2_1, 0);
	digitalWrite(M2_2, 0);
}

void check() 
{
	if(stime <= millis())
		stop();
}

void forward(long value) 
{
	analogWrite(M1_1, M_SPEED);
	digitalWrite(M1_2, 1);
	analogWrite(M2_1, M_SPEED);
	digitalWrite(M2_2, 1);
	stime = millis() + value;
}

void backward(long value) 
{
	analogWrite(M1_1, M_SPEED);
	digitalWrite(M1_2, 0);
	analogWrite(M2_1, M_SPEED);
	digitalWrite(M2_2, 0);
	stime = millis() + value;
}

void left(long value) 
{
	analogWrite(M1_1, M_SPEED);
	digitalWrite(M1_2, 1);
	analogWrite(M2_1, M_SPEED);
	digitalWrite(M2_2, 0);
	stime = millis() + value;
}

void right(long value) 
{
	analogWrite(M1_1, M_SPEED);
	digitalWrite(M1_2, 0);
	analogWrite(M2_1, M_SPEED);
	digitalWrite(M2_2, 1);
	stime = millis() + value;
}

bool parse() 
{
	if (data[0] != -96) return false;
	if (data[1] != -95) return false;
	if (data[2] != 10) return false;
	if (data[8] != -95) return false;
	if (data[9] != -96) return false;
	
	command = (int) data[3];
	value = ((byte)data[4] << 24) | ((byte)data[5] << 16) | ((byte)data[6] << 8) | ((byte)data[7] << 0);
	
	return true;
}

void setup() 
{
	Serial.begin(115200);
	digitalWrite(13, 1);

	pinMode(M1_1, OUTPUT);
	pinMode(M1_2, OUTPUT);
	pinMode(M2_1, OUTPUT);
	pinMode(M2_2, OUTPUT);
	
	memset(data, 0, 10);

	Bridge.begin();
	
	digitalWrite(13, 0);
	delay(500);
	digitalWrite(13, 1);
	delay(500);
	
	stop();
	digitalWrite(13, 0);
}
  
void loop() 
{
	check();
	digitalWrite(13, command);
	
	Bridge.get("data", data, 10);
	delay(10);
	
	if(!parse()) return;

	for(int i = 0; i < 10; i++) 
	{
		Serial.print(data[i], HEX);
		Serial.print(" ");
	}
	
	Serial.println();
	
	Bridge.put("data", "0000000000");
	delay(10);
	
	Serial.print(command);
	Serial.print("|");
	Serial.print(value);
	Serial.println("|");
	
	if(command == 1) forward(value);
	if(command == 2) backward(value);
	if(command == 3) left(value);
	if(command == 4) right(value);
	if(command == 5) stop();
}
