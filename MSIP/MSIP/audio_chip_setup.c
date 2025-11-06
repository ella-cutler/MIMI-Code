
	
#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>
	

	
	
void audio_chip_setup(void){
	int fd;	
	
	fd = wiringPiI2CSetup(0x20);
	//read_data = wiringPiI2cReadReg8(fd,reg number);
	wiringPiI2CWriteReg8(fd, 0x36, 0x41);  //turn on limiter and default i2s sck pol
        wiringPiI2CWriteReg8(fd, 0x08, 0x35);  //auto processor on right justified 20 bits
	wiringPiI2CWriteReg8(fd, 0x03, 0x1D);	//power mode profile 3
	wiringPiI2CWriteReg8(fd, 0x3A, 0x40);	//set volume to -34 dB

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
