

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE  *fp;
	unsigned int vol= 1;  // aplay uses 0 to 65536

	printf("here");
	
		fp = fopen("/media/pi/USB_VOLUME/vol.bin", "rb+");
//		
//	}
	
		fread(&vol, 1,1, fp); //use this in init
		
		
		char buf[32];
			
		sprintf(buf, "amixer set Master %d", vol);
		system(buf);
		
		printf("%d", vol);
		
		
		fwrite(&vol, 1,1,fp);
	
	fclose(fp);
	return 0;
}

