
	
#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>
//#include <mpg123.h>

#define     Audio_ENABLE_L_pin 15
#define     MUTE_L_pin 16	
#define     boost 0
	
	
int main(int argc, char **argv)
{
	wiringPiSetup();
	
	//mpg123_init();
//	system("mpg123  /home/pi/MSIP/bell_new.mp3") ;


	
	int fd;	
	char volume;
	//unsigned int reg number;
	//unsigned int read_data;
	pinMode(Audio_ENABLE_L_pin, OUTPUT);	
	pinMode(MUTE_L_pin, OUTPUT);
	pinMode(boost, OUTPUT);
	digitalWrite(boost, HIGH); 
	delay(10);
	
	digitalWrite(Audio_ENABLE_L_pin, HIGH); 
	digitalWrite(MUTE_L_pin, LOW); 
	
	delayMicroseconds(1); 	
	digitalWrite(Audio_ENABLE_L_pin, LOW); 
	
	fd = wiringPiI2CSetup(0x20);  // how do you clean up fd
	//while(1){
	
	//read_data = wiringPiI2cReadReg8(fd,reg number);
	
	//wiringPiI2CWriteReg8(fd, reg, data);
	wiringPiI2CWriteReg8(fd, 0x35, 0x58);  //standard i2s
	wiringPiI2CWriteReg8(fd, 0x36, 0x53);  //turn on limiter and default i2s sck pol
        // program limiters
	wiringPiI2CWriteReg8(fd, 0x1D, 0x02);	//power mode profile 3
	
	
	wiringPiI2CWriteReg8(fd, 0x40, 0x30);	//set volume to -34 dB
	wiringPiI2CWriteReg8(fd, 0x42, 0x20); 	//set volume to -34 dB
	wiringPiI2CWriteReg8(fd, 0x43, 0xFF);	//set volume to -34 dB
	wiringPiI2CWriteReg8(fd, 0x44, 0xFF);	//set volume to -34 dB
	wiringPiI2CWriteReg8(fd, 0x45, 0xFF);	//set volume to -34 dB
	
	
	
 system("mpg123  /home/pi/MSIP/clock_only.mp3") ;
	volume = wiringPiI2CReadReg8(fd,0x40);
	printf("Volume   %d\r\n",volume);
	delay(1000);
	//wiringPiI2CWriteReg8(fd, ++volume, 0x40);  //increase volume 1 dB
   //   }
 
digitalWrite(MUTE_L_pin, HIGH); 
	return 0;
}
   /*
    * 
    * 
    * 
    * 
    * 0x40 Mstr Volume 1 dB defualt 0x18
    * 0x41 Mstr Volume 0.25 dB defualt 0x00
    * 0x42 LVol   defualt 0x18
    * 0x43 RVol   defualt  0x18
    * 0x47 Lim thresh Volume default 0x18
    * 0x48 Lim thresh Volume default 0x18
    * 0x36 Mute and Limiter Enable default 0x01  NOT Muted and Limiter Bypassed
    * 
    */
