#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#define BELL 1  //uses these to call audio and play
#define BUZZER 2
#define PSA 3
#define TRACK 4

void *audio ( void *play_this_one){
  
    printf(" playing audio \r\n");
    int *value = (int *) play_this_one;
    printf ("value is  %d", *value);
    
    if(*value ==BELL){
 // FILE *fp;
  //fp = fopen("./bell.mp3", "r");
   printf(" playing bell\r\n");
 }
 
   if(*value ==BUZZER){
 // FILE *fp;
  //fp = fopen("./buzzer.mp3", "r");
   printf(" playing buzzer\r\n");
  } 
  
   if(*value ==PSA){
 // FILE *fp;
  //fp = fopen("./psa.mp3", "r");
   printf(" playing psa\r\n");
   
 }
   

 
 // fclose(fp);

 
   while (1)
    {
        // Turn it on
          printf("Audio \r\n");
        
        // wait a bit
       delay(5000);
         printf("finshed audio \r\n");
         
       }
         
 
return NULL;
  
  

  };

 
int main()
{
    
 pthread_t th1;
 
 int play_this = PSA;
 
  pthread_create ( &th1, NULL, ( void* ) audio, &play_this );  
 
  
    
  while (1)
    {
        
          printf("LEDs \r\n");
        
        // wait a bit
        delay(500);
       
       
              
    }
 
}
 
 
