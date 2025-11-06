

#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
//#include <mpg123.h>


  // add -lncurses -lwiringPi to build

//#define DEBUG

#define	A_Left 	 	0  // Missile Status Indicator-Launcher Panel
#define A_Right 	1
#define	B_Left    	2  
#define	B_Right  	3
#define	C_Left  	4
#define	C_Right     5
#define	D_Left     	6
#define	D_Right   	7
#define	E_Left      8
#define	E_Right     9

#define	up_arrow	259  // wireless input codes from curses
#define	left_arrow	260
#define	right_arrow	261
#define	down_arrow	258
#define	enter		10
#define	ok			10
#define	page_up		339
#define	page_down	338
#define	del		263
#define	key_0	48
#define	key_1	49
#define	key_2	50
#define	key_3	51
#define	key_4	52
#define	key_5	53
#define	key_6	54
#define	key_7	55
#define	key_8	56
#define	key_9	57


// Ax_OUT15 is the bit 15 of the shift register for A MSIP AR an AL
// Bx_OUT15 is the bit 15 of the shift register for B MSIP BR an BL
#define		Ax_OUT15		    0b1000000000000000  
#define		Bx_OUT15		    0b1000000000000000  
#define		STRATEGIC_ALERT		0b0100000000000000
#define		NOT_AUTHENTICATED	0b0010000000000000
#define		STANDBY 			0b0001000000000000
#define		CLIP_COMMAND 		0b0000100000000000
#define		FAULT				0b0000010000000000
#define		WARHEAD_ALARM 		0b0000001000000000
#define		ENABLE_COMMAND 		0b0000000100000000
#define		ENABLED 			0b0000000010000000
#define		LAUNCH_COMMAND 		0b0000000001000000
#define		LANUCH_INHIBIT		0b0000000000100000
#define		LAUNCH_IN_PROCESS	0b0000000000010000
#define		MISSILE_AWAY 		0b0000000000001000
#define		OUTER_SECURITY 		0b0000000000000100
#define		INNER_SECURITY 		0b0000000000000010
#define		ANTI_JAM_MODE 		0b0000000000000001
#define	 	local_off	        0b0000000000000000  // All off including   _OUT15
#define		local_on            0b1111111111111111  // All on including   _OUT15

// pin numbers are WiringPi numbers
//#define   SDA1 8 
//#define   SCL1 9 


//#define   MISO_Conn_pin GPIO9 pin 13  // To Connector
//#define   MOSI_0_T_pin   // SPI GPIO10 pin 12
//#define   SCLK_0_T_pin   // SPI  GPIO11 pin 14
#define     Strobe_LE_R_E_pin 10 // SPI
#define     Strobe_CS_L_pin 25 //SPI

#define     Audio_ENABLE_L_pin 23
#define     MUTE_L_pin 15

//#define   MCLK_pin  =7 //I2S GPIO4
//#define   Digital_audio_CLK_u_pin  =1  // Digital_audio_CLK_u
//#define   L/R_audio_CLK_u_pin  // L/R_audio_CLK_u
//#define   Audio_Data_u_pin  =29   // Audio_Data_u

#define     OE_ALL_u_L_pin 26
#define     Mux0_pin 3
#define     Mux1_pin 4 
#define     Mux2_pin 5
#define     Mux3_pin 6
#define     Strobe_CS_L 25


// GPIO1_pin 31  Not connected
// GPIO0 pin 30 Not Connected
// GPIO22 pin 22 Not Connected
// GPIO6_pin 6  Not connected

//#define     GPIO5_pin 5 // To connector
//#define     GPIO15_pin 16  // To connector
//#define     GPIO16_pin 27  // To connector
//#define     GPIO17_pin 0  // To connector   This maybe used by AUDIO!
//#define     GPIO27_pin 2  // To connector
//#define     CS_Conn_pin 11  // To connector




#define     delay_min   1000  // min delay time in milliseconds
#define     delay_delta 4000  // Maximum delay time is delay_min + delay_delta in milliseconds
#define BELL 1  //uses these to call audio and play
#define BUZZER 2
#define PAS 3
#define TRACK 4

void annunciator (unsigned char ,  unsigned short int );
void run_demo_seq(void);
void lamp_test(void);
void run_launch_seq(void);

volatile unsigned char status_N = 0;
volatile unsigned char lamp_test_N = 0;
void initialize(void);
void All_OFF(void);
void All_ON(void);
void run_seq(void);  // only good for test
unsigned char random_N(void);
void bell_on(void);
void buzzer_on(void);
void pas_on(void);
void bell_off(void);
void buzzer_off(void);
void pas_off(void);
void play_sound_track(void);
void audio_chip_setup(void);
void volume_control_up(void);
void volume_control_down(void);
void home(void);
void security (unsigned char);
void fault (unsigned char);
void not_authenticated (unsigned char);
void anti_jam_mode (unsigned char);
void missile_away (unsigned char);
void audio ( void *play_this_one);
volatile unsigned short int A_Left_copy;
volatile unsigned short int A_Right_copy;
volatile unsigned short int B_Left_copy;
volatile unsigned short int B_Right_copy;
volatile unsigned short int C_Left_copy;
volatile unsigned short int C_Right_copy;
volatile unsigned short int D_Left_copy;
volatile unsigned short int D_Right_copy;
volatile unsigned short int E_Left_copy;
volatile unsigned short int E_Right_copy;
char audio_on;


int main()


{
	


initscr();  // setup curses


     keypad(stdscr, TRUE);	

 	
	
 fflush(stdout);
	
	puts("ss");
  noecho();	
	printf("%s \n", "help");

	
	
	
	time_t t;   //random seed from time
	t = time(NULL);
	srandom(t);

     

wiringPiSetup();

printf ("call2");
initialize(); // call the initialize function


while(1){
int input =0;
 printf("WAIT FOR KEY\r\n");
  input = getch(); //   Get input from controller this will need work for volume 

  
  
  
  	
#ifdef DEBUG
 printw("4");

#endif
// the following switch statement is for key definition
// there are functions for the static/dynamic LED displays


   switch(input) {
	  case up_arrow:
      printf("up_arrow\r\n");
      volume_control_up();
	 
	  
	  break;
	  
	  case left_arrow:
		printf("left_arrow\r\n");
	  break;
	  
	  case right_arrow:
	   printf("right_arrow\r\n");
	  break;
	  
	  case down_arrow:			// use for volume down
	  printf("down_arrow\r\n");
	 volume_control_down();
	  
	  break;
	  
	  case enter:  				// enter and ok are the same code
	  printf("enter or ok \r\n");
	  break;
	  
	  	  
	  
	  case page_up:				
	  printf("page_up\r\n");

	 	 
	  break;
	  
	  
	  case page_down:
	  printf("page_down\r\n");
	  break;
	  
	  case key_0:  			// Take to HOME state 
	  printf("key_0\r\n");
	  home();
	  break;
	  
	  case key_1:  
	  printf("key_1\r\n");
	  lamp_test();
	   	  	   
	  break; 

	  case key_2:  
	  printf("key_2\r\n");
	  run_seq();
	  
	  break;
	  
	  case key_3:  
	  printf("key_3\r\n");
	  play_sound_track();
	  
	  
	  break; 
	  
	  case key_4:  
	  printf("key_4\r\n");
	  run_demo_seq();
	  
	  break;
	  
	  case key_5:  
	  printf("key_5\r\n");
	  
	  break;

	  case key_6:  
	  printf("key_6\r\n");
	  break;
	  
	  case key_7:  
	  printf("key_7\r\n");
	  run_launch_seq();
	  break; 
		
	  case key_8:  
	  printf("key_8\r\n");
	  break; 

	  case key_9:  
	  printf("key_9\r\n");
	  system ("sudo shutdown -P now");
	 // GPIO 0 should go low dtoverlay=gpio-poweroff,gpiopin=0, active_low="y"
	  break;
	  
		  
	  default:
	  break;
	  
  }
  
  
  
  	  
  

}

	 endwin();	//End curses mode
	return 0;
}
	
	
void initialize(void)
{
	printf("initializer\r\n");
	lamp_test_N = 0;
	digitalWrite(OE_ALL_u_L_pin, 1);  // put Output enable high so LEDs are off
	pinMode(Mux0_pin, OUTPUT);	// Configure GPIOs
	pinMode(Mux1_pin, OUTPUT);	
	pinMode(Mux2_pin, OUTPUT);	
	pinMode(Mux3_pin, OUTPUT);
	pinMode(Audio_ENABLE_L_pin, OUTPUT);	
	pinMode(MUTE_L_pin, OUTPUT);
	pinMode(Strobe_CS_L_pin, OUTPUT);
	pinMode(OE_ALL_u_L_pin, OUTPUT);
	
digitalWrite(Audio_ENABLE_L_pin, 1);
// set the defult volume etc

digitalWrite(MUTE_L_pin, LOW);  // set mute pin low so the audio is muted

digitalWrite(Strobe_CS_L_pin, 1);  // Set Chip Slect high will drive low when SPI starts











//Clock idle high, Data change on falling edge, latched on rising edge

wiringPiSPISetupMode( 0, 1000000,3);  // SPI channel 0 at 1MHz




// Set up I2S MCLK, Audio CLK, Audio L/R, and Audio Data


//int fd = wiringPiI2CSetup(0x20);
//wiringPiI2CSetup(fd);


// int wiringPiI2CSetup(const int devId);
// wiringPiI2CWrite(0, xx);
//adress is 0x20
// set the defult volume etc
audio_chip_setup();
All_OFF(); // function call to turn all off
digitalWrite(OE_ALL_u_L_pin, 0);  // put Output enable low so LEDs are on

printf("Finshed initializer\r\n");

return;

}

void All_OFF(void) {
	printf("ALL_OFF\r\n");
	
	
	digitalWrite(MUTE_L_pin, LOW);  // set mute pin low so the audio is muted
	//pthread_cancel(pthread_t th_audio);  // cancel any audio that is playing

	unsigned char count = 0;
	

	
	
	while(count <= 9){
	unsigned char Mux3_value = (count & 0b1000)>>3;  //step thru all 10 Mux values and write 0s to bits
	unsigned char Mux2_value = (count & 0b0100)>>2;
	unsigned char Mux1_value = (count & 0b0010)>>1;
	unsigned char Mux0_value = (count & 0b0001);
	digitalWrite(Mux3_pin, Mux3_value);
	digitalWrite(Mux2_pin, Mux2_value);
	digitalWrite(Mux1_pin, Mux1_value);
	digitalWrite(Mux0_pin, Mux0_value);
	
	digitalWrite(Strobe_CS_L_pin, 0);
	
	unsigned char Array[] ={0x00, 0x00};
	
	wiringPiSPIDataRW(0,Array,2);
	
	
	digitalWrite(Strobe_CS_L_pin, 1);
	++count;
	
}
	return;
	
}
void run_seq(void){  // this is only good for testing
	unsigned char j=0;
	unsigned char k=0;
	while (j <= 9) {
		while (k <=15) {
			annunciator (j,k);
			  ++k;
			  delay(100);
			  }
	printf("j   %d\r\n",j);
	k=0;
		++j;
		  }	
	
	
	return;
	
}
	
	void All_ON(void) {  // this is for LAMP TEST 
		printf("ALL_ON\r\n");
	unsigned char count = 0;
	
	while(count <= 9){
	unsigned char Mux3_value = (count & 0b1000)>>3;  //step thru all 10 Mux values and write 0s to bits
	unsigned char Mux2_value = (count & 0b0100)>>2;
	unsigned char Mux1_value = (count & 0b0010)>>1;
	unsigned char Mux0_value = (count & 0b0001);
	digitalWrite(Mux3_pin, Mux3_value);
	digitalWrite(Mux2_pin, Mux2_value);
	digitalWrite(Mux1_pin, Mux1_value);
	digitalWrite(Mux0_pin, Mux0_value);
	
	digitalWrite(Strobe_CS_L_pin, 0);
	unsigned char Array[] ={0xFF, 0xFF};
	
	wiringPiSPIDataRW(0,Array,2);
	
	
	digitalWrite(Strobe_CS_L_pin, 1);
	++count;
}
	return;
	
}
	
	
	
	
	
	
	void annunciator (unsigned char WHICH_ONE,  unsigned short int WhatsON){
		printf("annunciator\r\r\n");
		if (WHICH_ONE == A_Left){A_Left_copy =  WhatsON;}  // keep a copy of what is in the shift registers
		if (WHICH_ONE == A_Right){A_Right_copy =  WhatsON;}
		if (WHICH_ONE == B_Left){B_Left_copy =  WhatsON;}  
		if (WHICH_ONE == B_Right){B_Right_copy =  WhatsON;}
		if (WHICH_ONE == C_Left){C_Left_copy =  WhatsON;}  
		if (WHICH_ONE == C_Right){C_Right_copy =  WhatsON;}
		if (WHICH_ONE == D_Left){D_Left_copy =  WhatsON;}  
		if (WHICH_ONE == D_Right){D_Right_copy =  WhatsON;}
		if (WHICH_ONE == E_Left){E_Left_copy =  WhatsON;}  
		if (WHICH_ONE == E_Right){E_Right_copy =  WhatsON;}
		printf("which one   %d\r\n",WhatsON); 
			
		unsigned char LSB_WhatsON;
		unsigned char MSB_WhatsON;
		MSB_WhatsON = (unsigned char) (WhatsON >> 8);
		LSB_WhatsON = (unsigned char) WhatsON;
	
	
	
		unsigned char Mux3_value = (WHICH_ONE & 0b1000)>>3; // parse WHICH_ONE into bits
		unsigned char Mux2_value = (WHICH_ONE & 0b0100)>>2;
		unsigned char Mux1_value = (WHICH_ONE & 0b0010)>>1;
		unsigned char Mux0_value = (WHICH_ONE & 0b0001);
		digitalWrite(Mux3_pin, Mux3_value);
		digitalWrite(Mux2_pin, Mux2_value);
		digitalWrite(Mux1_pin, Mux1_value);
		digitalWrite(Mux0_pin, Mux0_value);
		
		printf("which one Annuciatorlam   %d%d%d%d\r\n",Mux3_value, Mux2_value,Mux1_value,Mux0_value); 
		
		digitalWrite(Strobe_CS_L_pin,1);
		
	unsigned char Array[] ={MSB_WhatsON, LSB_WhatsON};
		wiringPiSPIDataRW(0,Array,2);
		digitalWrite(Strobe_CS_L_pin, 1);
	
	delayMicroseconds(1);
	
	digitalWrite(Strobe_CS_L_pin, 0);
	delayMicroseconds(1);
	
		digitalWrite(Strobe_CS_L_pin, 1);
	
delayMicroseconds(1);

	
	return;
	
}


unsigned char random_N(void){ // return N between 0 and 9
	printf("radom_N\r\n");
	unsigned char N;
	N = random()  %10;
	return N;
}


/*
	 * 
	 * NOT AUTHENTICATED 	Buzzer
	 * FAULT 				Buzzer
	 * WARHEAD ALARM		Buzzer
	 * ENABLED				Bell
	 * LAUNCH COMMAND		Bell
	 * LAUNCH IN PROCESS	Bell
	 * OUTER SECURITY		Buzzer
	 * INNER SECURITY		Buzzer
	 * ANTI-JAM MODE		Buzzer
	 *
	 * 
*/

void bell_on(void){ 
	printf("playing BELL \r\n");
	pthread_t th1;
 
 int play_this = BELL;
 
  pthread_create ( &th1, NULL, ( void* ) audio, &play_this );  
	
	
		digitalWrite(MUTE_L_pin, 1);  // set mute pin HIGH
	return;
}

void bell_off(void){
	printf("Bell off \r\n");
	digitalWrite(MUTE_L_pin, 0);
	audio_on = 0;
	return;
}

void buzzer_on(void){ 
	printf("playing BUZZER \r\n");
		
	pthread_t th1;
 
 int play_this = BUZZER;
 
  pthread_create ( &th1, NULL, ( void* ) audio, &play_this );  
	digitalWrite(MUTE_L_pin, 1);  // set mute pin HIGH
	
	return;	
}

void buzzer_off(void){ 
	printf("Buzzer off \r\n");
	digitalWrite(MUTE_L_pin, 0);
	audio_on = 0;
	return;	
}

void pas_on(void){ 
	printf("playing PAS \r\n");
		
	pthread_t th1;
 
 int play_this = PAS;
 
  pthread_create ( &th1, NULL, ( void* ) audio, &play_this );  
	digitalWrite(MUTE_L_pin, 1);  // set mute pin HIGH
	
	return;	
}



void pas_off(void){
	printf("PAS off \r\n");
	digitalWrite(MUTE_L_pin, 0);
	audio_on = 0;
	return;
}



void play_sound_track(void){ 
	printf("playing Sound Track \r\n");
	pthread_t th1;
 
 int play_this = TRACK;
 
  pthread_create ( &th1, NULL, ( void* ) audio, &play_this );  
	
	
		digitalWrite(MUTE_L_pin, 1);  // set mute pin HIGH
	return;
}







void home(void) {
	 printf("HOME \r\n");
	  status_N = 0;
	  lamp_test_N = 0;
	  //All_OFF();
	  bell_off();  // I guess clean up 3 times  :)
	  buzzer_off();
	  pas_off();
	  
	  
	  // make sure to clean up all pointers and threads

	  annunciator (A_Left, STRATEGIC_ALERT);  // turn on ALL STRATEGIC ALERTs
	  annunciator (A_Right, STRATEGIC_ALERT);
	  annunciator (B_Left, STRATEGIC_ALERT);
	  annunciator (B_Right, STRATEGIC_ALERT);
	  annunciator (C_Left, STRATEGIC_ALERT);
	  annunciator (C_Right, STRATEGIC_ALERT);
	  annunciator (D_Left, STRATEGIC_ALERT);
	  annunciator (D_Right, STRATEGIC_ALERT);
	  annunciator (E_Left, STRATEGIC_ALERT);
	  annunciator (E_Right, STRATEGIC_ALERT);
	  
	  return;
	  
}	  

void security (unsigned char which_MISILP){
	/* Strategic Alert on
	 * Outer Security on
	 * Buzzer on
	 * delay and Inner Secutity and Buzzer on
	 */
	  printf("security\r\n");
	  annunciator (which_MISILP, 0x00);
	  annunciator (which_MISILP, STRATEGIC_ALERT);
	  annunciator (which_MISILP, STRATEGIC_ALERT | OUTER_SECURITY);
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
      annunciator(which_MISILP, INNER_SECURITY);
	  buzzer_on();
	 
	 return;
	  
 }


void fault (unsigned char which_MISILP){
	/* Strategic Alert on
	 * delay Warhead Alarm and Buzzer on
	 * delay Fault and Buzzer on
	 * 
	 */
	  printf("fault\r\n");
	  annunciator (which_MISILP, 0x00);
	  annunciator (which_MISILP, STRATEGIC_ALERT);
	  annunciator (which_MISILP, WARHEAD_ALARM | STRATEGIC_ALERT);
	
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
      annunciator(which_MISILP, FAULT | WARHEAD_ALARM | STRATEGIC_ALERT);
	  buzzer_on();
	 
       return;
 }

void not_authenticated (unsigned char which_MISILP){
	/* Strategic Alert off
	 * delay Not Authenticated and Buzzer on
	 * delay Outer Security and Buzzer on
	 * 
	 */
	  printf("not authenticated \r\n");
	  annunciator (which_MISILP, 0x00);  // turn all off
	  annunciator (which_MISILP, NOT_AUTHENTICATED);
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
      annunciator(which_MISILP, OUTER_SECURITY | NOT_AUTHENTICATED);
	  buzzer_on();
	 
	 return;
 }

void anti_jam_mode (unsigned char which_MISILP){
	/* Strategic Alert off
	 * Anti-Jam Mode on and Buzzer on
	 * delay Not Authenticated on and Buzzer on
	 * dalay Outer Security and Buzzer on
	 * 
	 */
	  printf("anti jam mode\r\n");
	  annunciator (which_MISILP, 0x00);
	  annunciator (which_MISILP, ANTI_JAM_MODE);
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
      annunciator(which_MISILP, NOT_AUTHENTICATED | ANTI_JAM_MODE);
	  buzzer_on(); 
	  delay(((random() % delay_delta) + delay_min));
      annunciator(which_MISILP, OUTER_SECURITY | NOT_AUTHENTICATED | ANTI_JAM_MODE);
	  buzzer_on(); 
	  
	 return;
	 
 }
 
void missile_away (unsigned char which_MISILP){
 /* Strategic Alert on
	 * delay Eanbled on an Bell on
	 * delay Lauch Command and Bell on
	 * delay Launch in Process and Bell on
	 * delay Inner Security and Buzzer on
	 * delay Outer Security and Buzzer on
	 * 
	 */
	  printf("missile away\r\r\n");
	  pas_on();
	  annunciator (which_MISILP, 0x00);
	  annunciator (which_MISILP, STRATEGIC_ALERT);
	  annunciator (which_MISILP, ENABLED | STRATEGIC_ALERT);
	  bell_on();
	  delay(((random() % delay_delta) + delay_min));
	  annunciator (which_MISILP, LAUNCH_COMMAND | ENABLED | STRATEGIC_ALERT);
	  bell_on();
	  delay(((random() % delay_delta) + delay_min));
	  annunciator (which_MISILP, LAUNCH_IN_PROCESS | ENABLED | STRATEGIC_ALERT);
	  bell_on();
	  delay(((random() % delay_delta) + delay_min));
	  annunciator (which_MISILP, INNER_SECURITY | LAUNCH_IN_PROCESS | ENABLED | STRATEGIC_ALERT);
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
	  annunciator (which_MISILP, OUTER_SECURITY | INNER_SECURITY | LAUNCH_IN_PROCESS | ENABLED | STRATEGIC_ALERT);
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
	  annunciator (which_MISILP, MISSILE_AWAY | OUTER_SECURITY | INNER_SECURITY | LAUNCH_IN_PROCESS | ENABLED | STRATEGIC_ALERT);
	  
	  	  
	 return;
	 
 }
 
	void run_demo_seq(void){
	unsigned char puMSILP;
      if (status_N == 0){
		 puMSILP = random_N();
	
	printf("which one puMSILP  %d\r\n",puMSILP);
	printf("Status N  %d\r\n",status_N); 
	     security(puMSILP);}
		  
	  if (status_N == 1){
		 fault(puMSILP);
		printf("which one puMSILP  %d\r\n",puMSILP);
		  printf("Status N  %d\r\n",status_N);}
	  if (status_N == 2){
		  not_authenticated(puMSILP);
		  printf("which one puMSILP  %d\r\n",puMSILP); 
		  printf("Status N  %d\r\n",status_N);}
	  if (status_N == 3){
		  anti_jam_mode(puMSILP);
		  printf("which one puMSILP  %d\r\n",puMSILP); 
		  printf("Status N  %d\r\n",status_N);}
		  
	  if (status_N == 4){
		  missile_away(puMSILP);
		  printf("which one puMSILP  %d\r\n",puMSILP); 
		  printf("Status N  %d\r\n",status_N);}
		if (status_N ==5){
			home();}else{			
			++status_N;}
			return;
		}


void lamp_test(void){
	
	 printf("Lamp Test\r\n");
	    	  
	  printf("which one lamp  %d\r\n",lamp_test_N);  
	 
       if (lamp_test_N < 10) {
		annunciator (lamp_test_N, local_on);
		if (lamp_test_N != 0){annunciator (lamp_test_N-1, STRATEGIC_ALERT);}  //leave STRATEGIC ALERT LAMP on
		
		++lamp_test_N;
	}
		else{	home();}
			
	  //++lamp_test_N;
	  
return;
	
}


void run_launch_seq(void){
	
	// make random sequence
	
	   int array[10];
    int x, p;
  
    int i=0;

    srandom(time(NULL));

 
    while(i<10){
        int r=random()%10;

        for (x = 0; x < i; x++)
        {
            if(array[x]==r){
                break;
            }
        }
        if(x==i){
            array[i++]=r;
        }
    }
    for(p=0;p<10;p++){
        printf("%d ", array[p]);
  
    
     missile_away(array[p]);
 }
      bell_off();
	  buzzer_off();
	  pas_off();
    
    
    return ;
}
	
void _track(void){
	printf("Playing Sound Track\r\n");
	 pthread_t th1;
 
 int play_this = TRACK;
 
  pthread_create ( &th1, NULL, ( void* ) audio, &play_this ); 
	
}	
	
void audio_chip_setup(void){
	printf("Audio chip setup \r\n");
	//int fd;	
	digitalWrite(Audio_ENABLE_L_pin, 0); //Eable audio chip
	
	//fd = wiringPiI2CSetup(0x20);
	//read_data = wiringPiI2cReadReg8(fd,reg number);
	//wiringPiI2CWriteReg8(fd, 0x36, 0x41);  //turn on limiter and default i2s sck pol
    //wiringPiI2CWriteReg8(fd, 0x08, 0x35);  //auto processor on right justified 20 bits
	//wiringPiI2CWriteReg8(fd, 0x03, 0x1D);	//power mode profile 3
	//wiringPiI2CWriteReg8(fd, 0x3A, 0x40);	//set volume to -34 dB

	return;

}



	
void volume_control_down(void){
	printf("Turn down volume\r\n");
	//int fd;	
	//char volume;
	//fd = wiringPiI2CSetup(0x20);
	//volume = wiringPiI2CReadReg8(fd,0x41);
	//wiringPiI2CWriteReg8(fd, volume-1, 0x41);  //increase volume 1 dB
       

	return;
}

void volume_control_up (void){
	printf("Turn up volume\r\n");
//	int fd;	
//	char volume;
//	fd = wiringPiI2CSetup(0x20);
//	volume = wiringPiI2CReadReg8(fd,0x41);
//	wiringPiI2CWriteReg8(fd, volume+1, 0x41);  //increase volume 1 dB
       

	return;
}


void audio ( void *play_this_one){
  
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
  
   if(*value ==PAS){
 // FILE *fp;
  //fp = fopen("./pas.mp3", "r");
   printf(" playing pas\r\n");
 }
 
 if(*value ==TRACK
 ){
 // FILE *fp;
  //fp = fopen("./track.mp3", "r");
   printf(" playing pas \r\n");
   
   
 }  

 
   while (audio_on)
    {
        // Turn it on  // loop audio forever
          printf("Audio \r\n");
        
        // wait a bit
       delay(5000);
         printf("finshed audio \r\n");
         
       }
         
 
return;
  
}

  
