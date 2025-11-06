
	
#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>
	

	
	
void audio_chip_setup(void){
	int fd;	
	char volume;
	fd = wiringPiI2CSetup(0x20);
	volume = wiringPiI2CReadReg8(fd,0x41);
	wiringPiI2CWriteReg8(fd, volume+1, 0x41);  //increase volume 1 dB
       

	return;
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
