
	
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
	
	pinMode(MUTE_L_pin, OUTPUT);
	
	
	
	
	

	fd = wiringPiI2CSetup(0x20);  
		
	wiringPiI2CWriteReg8(fd, 0x35, 0x58);  //standard i2s
	wiringPiI2CWriteReg8(fd, 0x36, 0x53);  //turn on limiter and default i2s sck pol
        // program limiters
	
	
	
	wiringPiI2CWriteReg8(fd, 0x1D, 0x02);	//power mode profile 2
	
	
	wiringPiI2CWriteReg8(fd, 0x40, 0X30);	//set volume to 
	wiringPiI2CWriteReg8(fd, 0x42, 0x30); 	//set volume to 
	wiringPiI2CWriteReg8(fd, 0x43, 0xFF);	//set volume to 
	wiringPiI2CWriteReg8(fd, 0x44, 0xFF);	//set volume to 
	wiringPiI2CWriteReg8(fd, 0x45, 0xFF);	//set volume to 
	
	
	
	
	volume = wiringPiI2CReadReg8(fd,0x40);
	printf("Volume   %d\r\n",volume);
	

 

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
