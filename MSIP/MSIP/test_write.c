
 
#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
//#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>

#include <stdio.h>
unsigned int short vol = 0 ;
unsigned int short cow = 32768 ;
int main(int argc, char **argv)
{
	FILE  *fp;

	
		fp = fopen("/media/pi/USB_VOLUME/vol.bin", "ab+");
		
			
	fread(&vol, 2,1, fp); 
 printf("VOL= %d \r\n",vol);	
		
			
	
		
		fp = fopen("/media/pi/USB_VOLUME/vol.bin", "wb");
		fwrite(&cow, 2,1,fp);
		
		 printf("COW= %d \r\n",cow);
		fclose(fp);
		
		
	
	
	
	

	fp = fopen("/media/pi/USB_VOLUME/vol.bin", "rb");
	fread(&vol, 2,1, fp); 
 printf("VOL= %d \r\n",vol);	

	fclose(fp);	
	return 0;
}

