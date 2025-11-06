/*
 * THIS IS TEST CODE 
 * maybe should have used pigpio vs. wiringPi
 * gcc -Wall -o "%e" "%f" -lwiringPi  -lncurses
 * set start up volume in void initialize(void)
 * 
 * 
 * 
 * GPIO 0 should go low dtoverlay=gpio-poweroff,gpiopin=0, active_low="y"
 * 
 * 
 * 
*/

#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdlib.h>
#include <time.h>

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
//#define     Strobe 10 
#define     Strobe_CS_L_pin 25 //SPI

#define     OE_ALL_u_L_pin 26
#define     Mux0_pin 3
#define     Mux1_pin 4 
#define     Mux2_pin 5
#define     Mux3_pin 6


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
#define    MUTE_pin 7  



#define     delay_min   1000  // min delay time in milliseconds
#define     delay_delta 4000  // Maximum delay time is delay_min + delay_delta in milliseconds
#define     after_action_delay_millsec 10000 //delay after running an action



void annunciator (unsigned char ,  unsigned short int );
void run_demo_seq(void);
void lamp_test(void);
void run_launch_seq(void);
void test(void);
volatile unsigned char status_N = 0;
volatile unsigned char lamp_test_N = 0;

unsigned int short bell_vol = 32768 ;		//default
unsigned int short buzzer_vol = 32768 ;		//default
unsigned int short pas_vol = 32768 ;		//default
unsigned int short vol_increment = 2048; //default

volatile unsigned int short key_9_down  = 0;
void initialize(void);
void All_OFF(void);
void All_ON(void);
void run_seq(void);  // only good for test
unsigned char random_N(void);
void bell_on(void);
void buzzer_on(void);
void pas_on(void);
void volume_control_down(void);
void volume_control_up(void);
void home(void);
void security (unsigned char);
void fault (unsigned char);
void not_authenticated (unsigned char);
void anti_jam_mode (unsigned char);
void missile_away (unsigned char);
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




int main()


{
	

int input =key_0;
	initscr();  // setup curses
timeout(-1);

    keypad(stdscr, TRUE);	
	
	fflush(stdout);
	
	noecho();	
	
	time_t t;   //random seed from time
	t = time(NULL);
	srandom(t);
   
	wiringPiSetup();

printf("RUN INITIALIZER \r\n");

initialize(); // call the initialize function


while(1){

 printf("WAIT FOR KEY\r\n");
 flushinp();
  input = getch(); //   Get input from controller this will need work for volume 

  
  
  
  	
#ifdef DEBUG
 printw("DEBUG");

#endif
// the following switch statement is for key definition
// there are functions for the static/dynamic LED displays


   switch(input) {
	  case up_arrow:
      printf("up_arrow\r\n");
      flushinp();
     volume_control_up();
	 key_9_down  = 0;  // reset count to turn off
	  
	  break;
	  
	  case left_arrow:
		printf("left_arrow\r\n");
		key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  case right_arrow:
	   printf("right_arrow\r\n");
	   key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  case down_arrow:			// use for volume down
	  printf("down_arrow\r\n");
	 volume_control_down();
	  key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  case enter:  				// enter and ok are the same code
	  printf("enter or ok \r\n");
	  key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  	  
	  
	  case page_up:				
	  printf("page_up\r\n");
		key_9_down  = 0;  // reset count to turn off
	 	 
	  break;
	  
	  
	  case page_down:
	  printf("page_down\r\n");
	  key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  case key_0:  			// Take to HOME state 
	  printf("key_0\r\n");
	  key_9_down  = 0;  // reset count to turn off
	  home();
	  break;
	  
	  case key_1:  
	  printf("key_1\r\n");
	  lamp_test();
	  key_9_down  = 0;  // reset count to turn off
	   	  	   
	  break; 

	  case key_2:  
	  printf("key_2\r\n");
	  security (random_N());
	  delay(after_action_delay_millsec);
	  home();
	  key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  case key_3: 
	   
	  fault (random_N());
	  printf("key_3\r\n");
	  delay(after_action_delay_millsec);
	  home();  
	  key_9_down  = 0;  // reset count to turn off
	  break; 
	  
	  case key_4:  
	  printf("key_4\r\n");
	  not_authenticated (random_N());
	  delay(after_action_delay_millsec);
	  home();
	  key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  case key_5:  
	  printf("key_5\r\n");
	  
	  anti_jam_mode (random_N());
	  delay(after_action_delay_millsec);
	  home();
	  key_9_down  = 0;  // reset count to turn off
	  break;

	  case key_6:  
	  printf("key_6\r\n");
	  run_demo_seq();
	  key_9_down  = 0;  // reset count to turn off
	  break;
	  
	  case key_7:  
	  printf("key_7\r\n");
	  run_launch_seq();
	  key_9_down  = 0;  // reset count to turn off
	  break; 
		
	  case key_8:  
	  printf("key_8\r\n");
	  test();
	  key_9_down  = 0;  // reset count to turn off
	  break; 

	  case key_9:  
	  printf("key_9\r\n");
	
	 key_9_down++;
    delay(500);	
    if(key_9_down == 10) {  // if 9 key is held for 5 seconds turn off power
		char buf[16];
	
	 	sprintf(buf, "shutdown -h now");
		system(buf);
			
 }
      
   	  
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
//setPadDrive(1,0x05000003);  // bit 4, slew control on 0, slew off 1
	lamp_test_N = 0;

	

	
	pinMode(Mux0_pin, OUTPUT);	// Configure GPIOs
	pinMode(Mux1_pin, OUTPUT);	
	pinMode(Mux2_pin, OUTPUT);	
	pinMode(Mux3_pin, OUTPUT);
	pinMode(Strobe_CS_L_pin, OUTPUT);
	digitalWrite(Strobe_CS_L_pin, 1);
	pinMode(OE_ALL_u_L_pin, OUTPUT);
	digitalWrite(OE_ALL_u_L_pin, 1);  // put Output enable high so LEDs are off
	pinMode(MUTE_pin, OUTPUT);
    digitalWrite(MUTE_pin, 1);
 

//Clock idle high, Data change on falling edge, latched on rising edge

wiringPiSPISetupMode( 0, 1000000,3);  // SPI channel 0 at 1MHz





All_OFF(); // function call to turn all off
digitalWrite(OE_ALL_u_L_pin, 0);  // put Output enable low so LEDs are on

printf("Finshed initializer\r\n");
home();

return;

}

void All_OFF(void) {
	printf("ALL_OFF\r\n");
			
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
		
	unsigned char Array[] ={0x00, 0x00};
	
	wiringPiSPIDataRW(0,Array,2);
	digitalWrite(Strobe_CS_L_pin, 0);
		delayMicroseconds(1);
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
	
	void All_ON(void)
	 {  // this is for LAMP TEST 
		printf("ALL_ON\r\n");
	unsigned char count = 0;
	
	while(count <= 9){
	unsigned char Mux3_value = ((count & 0b1000)>>3);  //step thru all 10 Mux values and write 0s to bits
	unsigned char Mux2_value = ((count & 0b0100)>>2);
	unsigned char Mux1_value = ((count & 0b0010)>>1);
	unsigned char Mux0_value = (count & 0b0001);
	digitalWrite(Mux3_pin, Mux3_value);
	digitalWrite(Mux2_pin, Mux2_value);
	digitalWrite(Mux1_pin, Mux1_value);
	digitalWrite(Mux0_pin, Mux0_value);
	
	
	unsigned char Array[] ={0xFF, 0xFF};
	
	wiringPiSPIDataRW(0,Array,2);
	digitalWrite(Strobe_CS_L_pin, 0);
		delayMicroseconds(1);
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
		
		printf("which one Annuciator   %d%d%d%d\r\n",Mux3_value, Mux2_value,Mux1_value,Mux0_value); 
		
		
		
	unsigned char Array[] ={MSB_WhatsON, LSB_WhatsON};
		wiringPiSPIDataRW(0,Array,2);
		
	
	delayMicroseconds(1);
	
	digitalWrite(Strobe_CS_L_pin, 0);
	delayMicroseconds(1);
	
		digitalWrite(Strobe_CS_L_pin, 1);
	


	
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
	char buf[24];
	
	

	 // aplay uses 0 to 65536

		
		
		
			
		sprintf(buf, "amixer set Master %d", bell_vol);
		system(buf);
	
	
	
	system("aplay  /home/pi/MSIP/bell_2s.wav") ;
	

	return;
}



void buzzer_on(void){ 
	printf("playing BUZZER \r\n");
	char buf[24];
	
	 // aplay uses 0 to 65536
			
		sprintf(buf, "amixer set Master %d", buzzer_vol);
		system(buf);

	system("aplay  /home/pi/MSIP/buzzer_2s.wav") ;

	return;	
}


void pas_on(void){ 
	printf("playing PAS \r\n");
	char buf[24];
	
	

	 // aplay uses 0 to 65536
			
		sprintf(buf, "amixer set Master %d", pas_vol);
		system(buf);

	 system("aplay /home/pi/MSIP/pas_3s.wav") ;  	

	return;	
}














void home(void) {
	 printf("HOME \r\n");
	  status_N = 0;
	  lamp_test_N = 0;
	  //All_OFF();
      timeout(-1);  // make sure getch() is blocking
		
	  
	  

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
	 // annunciator (which_MISILP, 0x00);
	  annunciator (which_MISILP, STRATEGIC_ALERT);
	  annunciator (which_MISILP, STRATEGIC_ALERT | OUTER_SECURITY);
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
      annunciator(which_MISILP, STRATEGIC_ALERT | OUTER_SECURITY | INNER_SECURITY);
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
	  annunciator (which_MISILP,  WARHEAD_ALARM);
	  buzzer_on();
	  delay(((random() % delay_delta) + delay_min));
	  annunciator (which_MISILP, FAULT |WARHEAD_ALARM);
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
	// pas_on();
	//  annunciator (which_MISILP, 0x00);
	//  annunciator (which_MISILP, STRATEGIC_ALERT);
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
 
	void run_demo_seq(void){
	unsigned char puMSILP;
      if (status_N == 0){
		 puMSILP = random_N();
	
	printf("which one puMSILP  %d\r\n",puMSILP);
	printf("Status N  %d\r\n",status_N);
	
	  pas_on();  }
	//  annunciator (puMSILP, 0x00);
	 // annunciator (puMSILP, STRATEGIC_ALERT);
	 if(status_N == 1){
	  annunciator (puMSILP, ENABLED | STRATEGIC_ALERT);
	  bell_on();
	  printf("ENABLE\r\r\n");
	  printf("Status N  %d\r\n",status_N);
					}
	//  delay(((random() % delay_delta) + delay_min));
	  if(status_N == 2 ){
	  annunciator (puMSILP, LAUNCH_COMMAND | ENABLED | STRATEGIC_ALERT);
	  bell_on();
	  printf("LAUNCH COMMAND\r\r\n");
	  printf("Status N  %d\r\n",status_N);
						}
	//  delay(((random() % delay_delta) + delay_min));
	  if(status_N == 3 ){
	  annunciator (puMSILP, LAUNCH_IN_PROCESS | LAUNCH_COMMAND | ENABLED | STRATEGIC_ALERT);
	  bell_on();
	  printf("LAUNCH IN PROCESS\r\r\n");
	  printf("Status N  %d\r\n",status_N);
						}
	//  delay(((random() % delay_delta) + delay_min));
	  if(status_N == 4 ){
	  annunciator (puMSILP, INNER_SECURITY | LAUNCH_IN_PROCESS | LAUNCH_COMMAND | ENABLED | STRATEGIC_ALERT);
	  buzzer_on();
	  printf("INNER SECURITY\r\r\n");
	  printf("Status N  %d\r\n",status_N);
						}  
	//  delay(((random() % delay_delta) + delay_min));
	  if(status_N == 5 ){
	  annunciator (puMSILP, OUTER_SECURITY | INNER_SECURITY | LAUNCH_IN_PROCESS | ENABLED | STRATEGIC_ALERT);
	  buzzer_on();
	  printf("OUTER SECURITY\r\r\n");
	  printf("Status N  %d\r\n",status_N);
						}  
	//  delay(((random() % delay_delta) + delay_min));
	  if(status_N == 6 ){
	  annunciator (puMSILP, MISSILE_AWAY | OUTER_SECURITY | INNER_SECURITY | LAUNCH_IN_PROCESS | ENABLED | STRATEGIC_ALERT);
	  printf("MISSILE AWAY  NOW\r\r\n");
	  printf("Status N  %d\r\n",status_N);
						}
	  if(status_N == 7 ){ 
	  printf("Go home\r\r\n");
	  printf("Status N  %d\r\n",status_N);
	  home();
	  status_N = -1;
						}	
	++status_N;	
	printf("Status N  %d\r\n",status_N);				
						  
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
    pas_on();
    
    
    // block untill key is pushed after PAS is played
    
    getch();
 
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
  
    timeout(0);
    int key = getch();
    if(key == key_0) {
    timeout(-1);
    home();
    break;
}
    
     missile_away(array[p]);
 }
      
    
    
    return ;
}
	

	



	
void volume_control_down(void){
	printf("Turn down volume\r\n");
	char buf[24];
	
	bell_vol = bell_vol - vol_increment;
	buzzer_vol = buzzer_vol - vol_increment;
	pas_vol = pas_vol - vol_increment;

	 // aplay uses 0 to 65536
	 
	 
		sprintf(buf, "amixer set Master %d", bell_vol);
		sprintf(buf, "amixer set Master %d", buzzer_vol);	
		sprintf(buf, "amixer set Master %d", pas_vol);
		system(buf);
		
		bell_on();
	//	buzzer_on();
	//	pas_on();

	return;
}

void volume_control_up (void){
	printf("Turn up volume\r\n");
    char buf[24];
	
	

	 // aplay uses 0 to 65536

		bell_vol = bell_vol + vol_increment;
	buzzer_vol = buzzer_vol + vol_increment;
	pas_vol = pas_vol + vol_increment;
		
		sprintf(buf, "amixer set Master %d", bell_vol);
		sprintf(buf, "amixer set Master %d", buzzer_vol);	
		sprintf(buf, "amixer set Master %d", pas_vol);
		system(buf);
		

		bell_on();
	//	buzzer_on();
	//	pas_on();
	
       

	return;
}

void test(void){
	
      printf("STRATEGIC ALERT\r\n");
	  annunciator (A_Left, STRATEGIC_ALERT);
	  delay(100); 
	  annunciator (A_Right, STRATEGIC_ALERT);
	  delay(100); 
	  annunciator (B_Left, STRATEGIC_ALERT);
	  delay(100);
	  annunciator (B_Right, STRATEGIC_ALERT);
	  delay(100);
	  annunciator (C_Left, STRATEGIC_ALERT);
	  delay(100);
	  annunciator (C_Right, STRATEGIC_ALERT);
	  delay(100);
	  annunciator (D_Left, STRATEGIC_ALERT);
	  delay(100);
	  annunciator (D_Right, STRATEGIC_ALERT);
	  delay(100);
	  annunciator (E_Left, STRATEGIC_ALERT);
	  delay(100);
	  annunciator (E_Right, STRATEGIC_ALERT);
	  delay(2000);
	  printf("NOT AUTHENTICATED\r\n");
	  annunciator (A_Left, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (A_Right, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (B_Left, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (B_Right, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (C_Left, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (C_Right, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (D_Left, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (D_Right, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (E_Left, NOT_AUTHENTICATED);
	  delay(100);
	  annunciator (E_Right, NOT_AUTHENTICATED);
	  delay(2000);
	  printf("STANDBY\r\n");
	  annunciator (A_Left, STANDBY ); 
	  delay(100); 
	  annunciator (A_Right, STANDBY );
	  delay(100);
	  annunciator (B_Left, STANDBY );
	  delay(100);
	  annunciator (B_Right, STANDBY );
	  delay(100);
	  annunciator (C_Left, STANDBY );
	  delay(100);
	  annunciator (C_Right, STANDBY );
	  delay(100);
	  annunciator (D_Left, STANDBY );
	  delay(100);
	  annunciator (D_Right, STANDBY );
	  delay(100);
	  annunciator (E_Left, STANDBY );
	  delay(100);
	  annunciator (E_Right, STANDBY );
	  delay(2000);
	  printf("CLIP COMMAND\r\n");
	  annunciator (A_Left, CLIP_COMMAND);
	  delay(100); 
	  annunciator (A_Right, CLIP_COMMAND);
	  delay(100);
	  annunciator (B_Left, CLIP_COMMAND);
	  delay(100);
	  annunciator (B_Right, CLIP_COMMAND);
	  delay(100);
	  annunciator (C_Left, CLIP_COMMAND);
	  delay(100);
	  annunciator (C_Right, CLIP_COMMAND);
	  delay(100);
	  annunciator (D_Left, CLIP_COMMAND);
	  delay(100);
	  annunciator (D_Right, CLIP_COMMAND);
	  delay(100);
	  annunciator (E_Left, CLIP_COMMAND);
	  delay(100);
	  annunciator (E_Right, CLIP_COMMAND);
	  delay(2000);
	  printf("FAULT\r\n");
	  annunciator (A_Left, FAULT);
	  delay(100); 
	  annunciator (A_Right, FAULT);
	  delay(100); 
	  annunciator (B_Left, FAULT);
	  delay(100);
	  annunciator (B_Right, FAULT);
	  delay(100);
	  annunciator (C_Left, FAULT);
	  delay(100);
	  annunciator (C_Right, FAULT);
	  delay(100);
	  annunciator (D_Left, FAULT);
	  delay(100);
	  annunciator (D_Right, FAULT);
	  delay(100);
	  annunciator (E_Left, FAULT);
	  delay(100);
	  annunciator (E_Right, FAULT);
	  delay(2000);
	  printf("WARHEAD ALARM\r\n");
	  annunciator (A_Left, WARHEAD_ALARM);
	  delay(100);
	  annunciator (A_Right, WARHEAD_ALARM);
	  delay(100);
	  annunciator (B_Left, WARHEAD_ALARM);
	  delay(100);
	  annunciator (B_Right, WARHEAD_ALARM);
	  delay(100);
	  annunciator (C_Left, WARHEAD_ALARM);
	  delay(100);
	  annunciator (C_Right, WARHEAD_ALARM);
	  delay(100);
	  annunciator (D_Left, WARHEAD_ALARM);
	  delay(100);
	  annunciator (D_Right, WARHEAD_ALARM);
	  delay(100);
	  annunciator (E_Left, WARHEAD_ALARM);
	  delay(100);
	  annunciator (E_Right, WARHEAD_ALARM);
	  delay(2000);
	  printf("ENABLE COMMAND Y\r\n");
	  annunciator (A_Left, ENABLE_COMMAND  ); 
	  delay(100); 
	  annunciator (A_Right, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (B_Left, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (B_Right, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (C_Left, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (C_Right, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (D_Left, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (D_Right, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (E_Left, ENABLE_COMMAND  );
	  delay(100);
	  annunciator (E_Right, ENABLE_COMMAND  );
	  delay(2000);
	  printf("ENABLED \r\n");
	  annunciator (A_Left, ENABLED );
	  delay(100); 
	  annunciator (A_Right, ENABLED);
	  delay(100);
	  annunciator (B_Left, ENABLED);
	  delay(100);
	  annunciator (B_Right, ENABLED);
	  delay(100);
	  annunciator (C_Left, ENABLED);
	  delay(100);
	  annunciator (C_Right, ENABLED);
	  delay(100);
	  annunciator (D_Left, ENABLED);
	  delay(100);
	  annunciator (D_Right, ENABLED);
	  delay(100);
	  annunciator (E_Left, ENABLED);
	  delay(100);
	  annunciator (E_Right, ENABLED);
	  delay(2000);	  
	  printf("LAUNCH COMMAND\r\n");
	  annunciator (A_Left, LAUNCH_COMMAND);
	  delay(100); 
	  annunciator (A_Right, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (B_Left, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (B_Right, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (C_Left, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (C_Right, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (D_Left, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (D_Right, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (E_Left, LAUNCH_COMMAND);
	  delay(100);
	  annunciator (E_Right, LAUNCH_COMMAND);
	  delay(2000);	  
	  printf("LANUCH NHIBIT\r\n");
	  annunciator (A_Left, LANUCH_INHIBIT);
	  delay(100); 
	  annunciator (A_Right, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (B_Left, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (B_Right, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (C_Left, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (C_Right, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (D_Left, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (D_Right, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (E_Left, LANUCH_INHIBIT);
	  delay(100);
	  annunciator (E_Right, LANUCH_INHIBIT);
	  delay(2000);	  
	  printf("LAUNCH_IN_PROCESS\r\n");
	  annunciator (A_Left, LAUNCH_IN_PROCESS);
	  delay(100); 
	  annunciator (A_Right, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (B_Left, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (B_Right, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (C_Left, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (C_Right, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (D_Left, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (D_Right, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (E_Left, LAUNCH_IN_PROCESS);
	  delay(100);
	  annunciator (E_Right, LAUNCH_IN_PROCESS);
	  delay(2000);	  
	  printf("MISSILE_AWAY\r\n");
	  annunciator (A_Left, MISSILE_AWAY);
	  delay(100); 
	  annunciator (A_Right, MISSILE_AWAY);
	  delay(100);
	  annunciator (B_Left, MISSILE_AWAY);
	  delay(100);
	  annunciator (B_Right, MISSILE_AWAY);
	  delay(100);
	  annunciator (C_Left, MISSILE_AWAY);
	  delay(100);
	  annunciator (C_Right, MISSILE_AWAY);
	  delay(100);
	  annunciator (D_Left, MISSILE_AWAY);
	  delay(100);
	  annunciator (D_Right, MISSILE_AWAY);
	  delay(100);
	  annunciator (E_Left, MISSILE_AWAY);
	  delay(100);
	  annunciator (E_Right, MISSILE_AWAY);
	  delay(2000);	  
	  printf("OUTER_SECURITY\r\n");
	  annunciator (A_Left, OUTER_SECURITY);
	  delay(100); 
	  annunciator (A_Right, OUTER_SECURITY);
	  delay(100);
	  annunciator (B_Left, OUTER_SECURITY);
	  delay(100);
	  annunciator (B_Right, OUTER_SECURITY);
	  delay(100);
	  annunciator (C_Left, OUTER_SECURITY);
	  delay(100);
	  annunciator (C_Right, OUTER_SECURITY);
	  delay(100);
	  annunciator (D_Left, OUTER_SECURITY);
	  delay(100);
	  annunciator (D_Right, OUTER_SECURITY);
	  delay(100);
	  annunciator (E_Left, OUTER_SECURITY);
	  delay(100);
	  annunciator (E_Right, OUTER_SECURITY);
	  delay(2000);
	  printf("INNER_SECURITY\r\n");
	  annunciator (A_Left, INNER_SECURITY);
	  delay(100); 
	  annunciator (A_Right, INNER_SECURITY);
	  delay(100);
	  annunciator (B_Left, INNER_SECURITY);
	  delay(100);
	  annunciator (B_Right, INNER_SECURITY);
	  delay(100);
	  annunciator (C_Left, INNER_SECURITY);
	  delay(100);
	  annunciator (C_Right, INNER_SECURITY);
	  delay(100);
	  annunciator (D_Left, INNER_SECURITY);
	  delay(100);
	  annunciator (D_Right, INNER_SECURITY);
	  delay(100);
	  annunciator (E_Left, INNER_SECURITY);
	  delay(100);
	  annunciator (E_Right, INNER_SECURITY);
	  delay(2000);
	  printf("ANTI_JAM_MODE \r\n");
	  annunciator (A_Left, ANTI_JAM_MODE );
	  delay(100); 
	  annunciator (A_Right, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (B_Left, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (B_Right, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (C_Left, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (C_Right, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (D_Left, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (D_Right, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (E_Left, ANTI_JAM_MODE );
	  delay(100);
	  annunciator (E_Right, ANTI_JAM_MODE );
	  delay(2000);	  
	  initialize();
	  home();  
	  
	  	  
	  return;
  }
  
