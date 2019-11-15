//testing AEAT-6012-A06 SSI encoder

//standard library
#include "Arduino.h"

//pin assignement & constants
int PIN_CS = 8;
int PIN_CLK = 9;
int PIN_D0 = 10;
int SERIAL_BAUD_RATE = 9600; //debugging

//setup
void setup()
{
    pinMode(PIN_CS, OUTPUT);
	pinMode(PIN_CLK, OUTPUT);
	pinMode(PIN_D0, INPUT);

    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);
}

//loop variables
int ii;
int read_value;
short position; //16 bit int

//main loop
void loop()
{
    // turn CS down (select) and clk down
	digitalWrite(PIN_CS, LOW);
	digitalWrite(PIN_CLK, LOW);
	delay(1); //ensure TCLKFE

	//generate 12 CLK events and read D0
	position = 0;
	for (ii=1; ii<=12; ii++)
	{
		digitalWrite(PIN_CLK, HIGH);
		delay(1); //wait TDO_valid
		read_value = digitalRead(PIN_D0);
		if (read_value == HIGH)
		{
			position = position | (int)(1<<(12-ii));
		}
		digitalWrite(PIN_CLK, LOW);
		delay(1); //wait TDO_valid
	}
	Serial.print("position: ");
    Serial.println(position, DEC);

	// turn CS high (de-select) and clk down
    //digitalWrite(PIN_CS, HIGH);
	delay(20); //relax

}
