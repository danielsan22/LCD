/*
@author: 		Walter Gonzalez Domenzain
@description: 	8020 Group
@functions:		None
@environment: 	KL25Z
@date: 			22/01/2014
@comments:		
@version:		1.0 - Initial
*/

#include "derivative.h" /* include peripheral declarations */
#define GPIO_PIN_MASK 0x1Fu
#define GPIO_PIN(x) (((1)<<(x & GPIO_PIN_MASK)))
#define	nBit0	0x01	//'00000001'
#define	nBit1	0x02	//'00000010'
#define	nBit2	0x04	//'00000100'
#define	nBit3	0x08	//'00001000'
#define	nBit4	0x10	//'00010000'
#define	nBit5	0x20	//'00100000'
#define	nBit6	0x40	//'01000000'
#define	nBit7	0x80	//'10000000'
//Time definitions
#define nt15_msec	3500
#define nt40_usec	35
//LCD Control
#define nIns	0
#define nData	1
#define PortLCD    	GPIOD_PDOR
//Enable connected to portb_01
#define Enable_1	GPIOB_PDOR |= 0x01
#define Enable_0	GPIOB_PDOR &= 0xFE
#define RS_1   		GPIOB_PDOR |= 0x02
#define RS_0   		GPIOB_PDOR &= 0xFD
#define	Set_GPIOB_PDOR(x)	(GPIOB_PDOR |= (1 << (x-1)))

int int_Temp;

//Cursor Blink off initialization
const unsigned char InitializeLCD[5] = {0x38, 0x38, 0x38, 0x0C, 0x01};
//--------------------------------------------------------------
//Declare Prototypes
/* Functions */
void cfgPorts(void);
void initLCD(void);
void delay(long time);
void sendCode(int Code, int Data);

/*@description: Initial Port Cfg 
*/
			
int main(void)
{
	//Configure ports
	cfgPorts();
	//Initialize LCD
	initLCD();
	//Set position to print character
	sendCode(nIns, 0x80);
	//Print character
	char myName[] = {'D','a', 'n', 'i', 'e', 'l', '-','S'};
	int x;
	for(x = 0; x <8; x++){
		sendCode(nData, myName[x]);
	}
	//sendCode(nIns, 0x80);
	

	for(;;)
	{/* The logic for the buttons works if a pull-down 
		resistor is used */
		/*
		if ((GPIOC_PDIR && 0x0F) == 0x00)
		{// No button is pressed
			//do noting
		}
		else if ((GPIOC_PDIR && 0x0F) == 0x01)
		{// Button 1 has been pressed
			sendCode(nData, '1');
		}
		else if ((GPIOC_PDIR && 0x0F) == 0x02)
		{// Button 2 has been pressed
			sendCode(nData, '2');
		}
		else if ((GPIOC_PDIR && 0x0F) == 0x04) 
		{// Button 3 has been pressed
			sendCode(nData, '3');
		}
		else if ((GPIOC_PDIR && 0x0F) == 0x08) 
		{// Button 4 has been pressed
			sendCode(nData, '4');	
		}
		else if ((GPIOC_PDIR && 0x0F) == 0x03) 
		{// Buttons 1&2 have been pressed
			
		}
		else if ((GPIOC_PDIR && 0x0F) == 0x07) 
		{// Buttons 1&2&3 have been pressed
			
		}
		else if ((GPIOC_PDIR && 0x0F) == 0x0F) 
		{// Buttons 1&2&3&4 have been pressed
			
		}*/
 
	}
	
	return 0;
}

void cfgPorts(void)
{
	//Turn on clock for portb
	SIM_SCGC5 = SIM_SCGC5_PORTB_MASK;	
	//Turn on clock for portd
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;	
	////Turn on clock for portc
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	/* Set pins of PORTB as GPIO */
	PORTC_PCR0 = PORT_PCR_MUX(1);
	PORTC_PCR1 = PORT_PCR_MUX(1);
	PORTC_PCR2 = PORT_PCR_MUX(1);
	PORTC_PCR3 = PORT_PCR_MUX(1);
	PORTC_PCR4 = PORT_PCR_MUX(1);
	PORTC_PCR5 = PORT_PCR_MUX(1);
	PORTC_PCR6 = PORT_PCR_MUX(1);
	PORTC_PCR7 = PORT_PCR_MUX(1);
	
	/* Set pins of PORTC as GPIO */
	PORTB_PCR0= PORT_PCR_MUX(1);
	PORTB_PCR1= PORT_PCR_MUX(1);
	
	/* Set pins of PORTD as GPIO */
	PORTD_PCR0= PORT_PCR_MUX(1);
	PORTD_PCR1= PORT_PCR_MUX(1);
	PORTD_PCR2=(0|PORT_PCR_MUX(1));
	PORTD_PCR3=(0|PORT_PCR_MUX(1));
	PORTD_PCR4=(0|PORT_PCR_MUX(1));
	PORTD_PCR5=(0|PORT_PCR_MUX(1));
	PORTD_PCR6=(0|PORT_PCR_MUX(1));
	PORTD_PCR7=(0|PORT_PCR_MUX(1));
	
	//Initialize PortB
	GPIOB_PDOR = 0x00;
	
	//Initialize PortC
	GPIOC_PDOR = 0x00;

	//Configure PortB as outputs
	GPIOB_PDDR = 0xFF;
	
	//Configure PortD as outputs
	GPIOD_PDDR = 0xFF;
	
	//Configure PortC as outputs
	GPIOC_PDDR = 0xFF;
}

void initLCD(void)
{
	int i;
	delay(nt15_msec);
	
	/* Send initialization instructions */
	/* Loop for sending each character from the array */
	for(i=0;i<5;i++)
	{										
		sendCode(nIns, InitializeLCD[i]);	/* send initialization instructions */
	}
	
}

void sendCode(int Code, int Data)
{
	//Assign a value to pin RS
	/*HINT: When RS is 1, then the LCD receives a data
	when RS is 0, then the LCD receives an instruction */
	// Initialize RS and Enable with 0
	RS_0;
	Enable_0;
	//Assign the value we want to send to the LCD
	PortLCD = Data;	
	
	//We make the algorithm to establish if its an instruction we start with 0 on RS value, otherwise if its a data command we start with RS as 1;
	if (Code == nIns)
	{
		Enable_1;
		delay(nt40_usec);
		Enable_0;
		RS_0;
	}		
	else if(Code == nData)
	{
		RS_1;
		Enable_1;
		delay(nt15_msec);
		Enable_0;
		RS_0;
	}
}
void delay(long time)
{
	while (time > 0)
	{
		time--;
	}
}

/*
#include "derivative.h" /* include peripheral declarations 
#define portB GPIOB_PDOR
#define portBIn GPIOB_PDIR
#define portD GPIOD_PDOR
#define readPortB(x) ((GPIOB_PDIR >>(x)) & 0x00000001)

#define turnRedLedOn 0xFFFBFFFF
#define turnBlueLedOn 0xFFFFFFFD
#define turnGreenLedOn 0xFFF7FFFF
#define turnLedsOff  0xFFFFFFFF
#define oneSec 1600000
//BUTTONS
#define buttonPressed 0
#define buttonNotPressed 1
#define buttonA readPortB(0)
#define buttonB readPortB(1)
#define buttonC readPortB(2)


//CODIGO FUNCIONANDO	

void cfgPorts(void);
void Delay(long ms);


int main(void)
{
	
	cfgPorts();
	portB=turnLedsOff;
	portD=turnLedsOff;
	Delay(oneSec);
	
	for(;;) {
		
		if(buttonA == buttonPressed)//PUSH BUTTON 1
		{
			portB = turnLedsOff;
			portD = turnLedsOff;
			portB=turnRedLedOn;
		}
		if(buttonB == buttonPressed)//PUSH BUTTON 2
		{
			portB = turnLedsOff;
			portD = turnLedsOff;
			portB=turnGreenLedOn;
		}
		if(buttonC == buttonPressed)//PUSH BUTTON 3a
		{
			portB = turnLedsOff;
			portD = turnLedsOff;
			portD=turnBlueLedOn;
		
		}
		//portB=turnLedsOff;
		//portD=turnLedsOff;
		/*else
		{
			portB=turnLedsOff;
		}
		*/
		/*
		portB = 0xFFFBFFFF; // encender led rojo
		Delay(1800000);
		apagarLeds();
		Delay(1800000);
		portB = 0xFFF7FFFF; // encender led verde
		Delay(1800000);
		apagarLeds();
		Delay(1800000);
		portD = 0xFFFFFFFD; // encender el azul
		Delay(1800000);
		apagarLeds();
		Delay(1800000);
		
	}
	
	return 0;
}


void cfgPorts(void)
{
	// TURN ON CLOCK
	SIM_SCGC5 = SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	// SELECT PORT MODE: SET PINS OF PORTB AS GPIO
	PORTB_PCR0= PORT_PCR_MUX(1);
	PORTB_PCR1= PORT_PCR_MUX(1);
	PORTB_PCR2= PORT_PCR_MUX(1);
	
	PORTB_PCR18= PORT_PCR_MUX(1);
	PORTB_PCR19= PORT_PCR_MUX(1);
	PORTD_PCR1= PORT_PCR_MUX(1); 
	
	
	// CONFIGURE PORTB FROM 31 TO 3 AS OUTPUT , 0-2 AS INPUT
	GPIOB_PDDR= 0xFFFFFFF8;
	GPIOD_PDDR= 0xFFFFFFFF;
}

void Delay(long ms)
{
	do
	{
		ms--;
	}
	while(ms!=0);
	
}

/*
