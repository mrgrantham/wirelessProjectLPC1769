#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lpc17xx_pinsel.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_exti.h"

void Init_Pwr(void)
{
	// Turn on peripheral GPIO0
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);
}

void RedLED(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_0,(1 << PINSEL_PIN_22));
	else
		GPIO_SetValue(PINSEL_PORT_0, (1 << PINSEL_PIN_22));
}

void BlueLED(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_3,(1 << PINSEL_PIN_26));
	else
		GPIO_SetValue(PINSEL_PORT_3, (1 << PINSEL_PIN_26));
}

void GreenLED(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_3,(1 << PINSEL_PIN_25));
	else
		GPIO_SetValue(PINSEL_PORT_3, (1 << PINSEL_PIN_25));
}

void Custom0LED(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_2,(1 << PINSEL_PIN_12));
	else
		GPIO_SetValue(PINSEL_PORT_2, (1 << PINSEL_PIN_12));
}

void Custom1LED(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_1,(1 << PINSEL_PIN_18));
	else
		GPIO_SetValue(PINSEL_PORT_1, (1 << PINSEL_PIN_18));
}

void Custom2LED(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_2,(1 << PINSEL_PIN_13));
	else
		GPIO_SetValue(PINSEL_PORT_2, (1 << PINSEL_PIN_13));
}

void Custom3LED(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_2,(1 << PINSEL_PIN_11));
	else
		GPIO_SetValue(PINSEL_PORT_2, (1 << PINSEL_PIN_11));
}

void testTX(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_0,(1 << PINSEL_PIN_9));
	else
		GPIO_SetValue(PINSEL_PORT_0, (1 << PINSEL_PIN_9));
}

void testRX(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_0,(1 << PINSEL_PIN_8));
	else
		GPIO_SetValue(PINSEL_PORT_0, (1 << PINSEL_PIN_8));
}

void testSwitch(int i)
{
	if (i == 0 )
		GPIO_ClearValue(PINSEL_PORT_2,(1 << PINSEL_PIN_10));
	else
		GPIO_SetValue(PINSEL_PORT_2, (1 << PINSEL_PIN_10));
}

int  on = 1;
void EINT3_IRQHandler(void)
//void checkTestSwitch()
{
	//uint8_t aSwitch = 0b01 & (GPIO_ReadValue(PINSEL_PORT_2) >> PINSEL_PIN_10);

/*
	if (aSwitch)
		Custom2LED(1);
	else
		Custom2LED(0);
		*/
		if (LPC_GPIOINT->IO2IntStatR & (1<<PINSEL_PIN_10)) {
			Custom2LED(1);
			//on = 0;
			LPC_GPIOINT->IO2IntClr=(1<<PINSEL_PIN_10);
		}
		if (LPC_GPIOINT->IO2IntStatF & (1<<PINSEL_PIN_10)){
			Custom2LED(0);
			//on = 1;
			LPC_GPIOINT->IO2IntClr=(1<<PINSEL_PIN_10);
		}
}

void Init_GPIO_Pins(void)
{
	// Configure GPIO Pins for LED control (RED Led and Blue Led)
	PINSEL_CFG_Type LedPin;
	LedPin.Portnum = PINSEL_PORT_0;
	LedPin.Pinnum = PINSEL_PIN_22;
	LedPin.Funcnum = PINSEL_FUNC_0; // Default GPIO
	LedPin.Pinmode = PINSEL_PINMODE_PULLUP;
	LedPin.OpenDrain = PINSEL_PINMODE_NORMAL;
	// Configure P0.22 (RED Led) for output
	PINSEL_ConfigPin(&LedPin);
	// Configure P3.26 (BLUE Led) for output
	LedPin.Portnum = PINSEL_PORT_3;
	LedPin.Pinnum = PINSEL_PIN_26;
	PINSEL_ConfigPin(&LedPin);
	// Configure P3.25 (GREEN Led) for output
	LedPin.Portnum = PINSEL_PORT_3;
	LedPin.Pinnum = PINSEL_PIN_25;
	PINSEL_ConfigPin(&LedPin);

	// Configure P2.10 (CUSTOM Led) for output
	//LedPin.Pinmode = PINSEL_PINMODE_PULLDOWN;
	LedPin.Portnum = PINSEL_PORT_2;
	LedPin.Pinnum = PINSEL_PIN_10;
	PINSEL_ConfigPin(&LedPin);

	// Configure P2.11 (CUSTOM Led) for output
	//LedPin.Pinmode = PINSEL_PINMODE_PULLDOWN;
	LedPin.Portnum = PINSEL_PORT_2;
	LedPin.Pinnum = PINSEL_PIN_11;
	PINSEL_ConfigPin(&LedPin);

	// Configure P2.12 (CUSTOM Led) for output
	//LedPin.Pinmode = PINSEL_PINMODE_PULLDOWN;
	LedPin.Portnum = PINSEL_PORT_2;
	LedPin.Pinnum = PINSEL_PIN_12;
	PINSEL_ConfigPin(&LedPin);

	LedPin.Portnum = PINSEL_PORT_1;
	LedPin.Pinnum = PINSEL_PIN_18;
	PINSEL_ConfigPin(&LedPin);

	//LedPin.Pinmode = PINSEL_PINMODE_PULLDOWN; // make a 0 low
	LedPin.Portnum = PINSEL_PORT_2;
	LedPin.Pinnum = PINSEL_PIN_13;
	PINSEL_ConfigPin(&LedPin);

	// checking the pins used for the connection to the RF module
	LedPin.Portnum = PINSEL_PORT_0;
	LedPin.Pinnum = PINSEL_PIN_9;
	PINSEL_ConfigPin(&LedPin);

	//LedPin.Pinmode = PINSEL_PINMODE_PULLDOWN;
	LedPin.Portnum = PINSEL_PORT_0;
	LedPin.Pinnum = PINSEL_PIN_8;
	PINSEL_ConfigPin(&LedPin);

	// Set IO Direction
	GPIO_SetDir(PINSEL_PORT_0, (1 << PINSEL_PIN_22), GPIO_DIR_OUTPUT); // Red LED
	GPIO_SetDir(PINSEL_PORT_3, (1 << PINSEL_PIN_26), GPIO_DIR_OUTPUT); // Blue LED
	GPIO_SetDir(PINSEL_PORT_3, (1 << PINSEL_PIN_25), GPIO_DIR_OUTPUT); // Green LED
	GPIO_SetDir(PINSEL_PORT_2, (1 << PINSEL_PIN_12), GPIO_DIR_OUTPUT); // Custom LED
	GPIO_SetDir(PINSEL_PORT_2, (1 << PINSEL_PIN_11), GPIO_DIR_OUTPUT); // Custom LED
	GPIO_SetDir(PINSEL_PORT_2, (1 << PINSEL_PIN_10), GPIO_DIR_INPUT); // Switch interrup (not sure if i need to configure it
																																		// to input before setup of interrupts)
	GPIO_SetDir(PINSEL_PORT_1, (1 << PINSEL_PIN_18), GPIO_DIR_OUTPUT); // Custom LED
	GPIO_SetDir(PINSEL_PORT_2, (1 << PINSEL_PIN_13), GPIO_DIR_OUTPUT); // Custom LED


	GPIO_SetDir(PINSEL_PORT_0, (1 << PINSEL_PIN_9), GPIO_DIR_OUTPUT); // TX
	GPIO_SetDir(PINSEL_PORT_0, (1 << PINSEL_PIN_8), GPIO_DIR_OUTPUT); // RX

	// SET EXTERNAL INTERRUPT FOR P2 10 SWITCH
	LPC_GPIOINT->IO2IntEnF = (1<<10);    /* Port2.10 is falling edge. */
	LPC_GPIOINT->IO2IntEnR = (1<<10);    /* also rising Edge */
	LPC_SC->EXTINT = 0xF;
	LPC_SC->EXTMODE = EXTI_MODE_EDGE_SENSITIVE;
	LPC_SC->EXTPOLAR = 0;                /*falling edge by default */
	//NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);


	// Set them all off (set to 1)
	RedLED(1);
	BlueLED(1);
	GreenLED(1);
	Custom0LED(1);
	Custom1LED(1);
	Custom2LED(0);
	Custom3LED(1);
	//testSwitch(1);

}


int main(void)
{
	int i;
	Init_Pwr();
	Init_GPIO_Pins();

	while(1)
	{
		// RedLED(0);
		// for(i = 0; i < 100000; i++);
		// RedLED(1);
		// for(i = 0; i < 100000; i++);
		//
		// RedLED(0);
		// BlueLED(0);
		// for(i = 0; i < 100000; i++);
		// BlueLED(1);
		// RedLED(1);
		// for(i = 0; i < 100000; i++);
		//
		// BlueLED(0);
		// GreenLED(0);
		// for(i = 0; i < 100000; i++);
		// GreenLED(1);
		// BlueLED(1);
		// for(i = 0; i < 100000; i++);
		//
		//
		// BlueLED(0);
		// for(i = 0; i < 100000; i++);
		// BlueLED(1);
		// for(i = 0; i < 100000; i++);
		//
		// GreenLED(0);
		// for(i = 0; i < 100000; i++);
		// GreenLED(1);
		// for(i = 0; i < 100000; i++);
		//
		// GreenLED(0);
		// RedLED(0);
		// for(i = 0; i < 300000; i++);
		// GreenLED(1);
		// RedLED(1);
		// for(i = 0; i < 300000; i++);
		//
		// Custom0LED(0);
		// for(i = 0; i < 300000; i++);
		// Custom0LED(1);
		// for(i = 0; i < 300000; i++);


		// Custom1LED(0);
		// for(i = 0; i < 300000; i++);
		// Custom1LED(1);
		// for(i = 0; i < 300000; i++);


		//checkTestSwitch();
		// Custom2LED(1);
		// for(i = 0; i < 1000000; i++);
		// Custom2LED(0);
		// for(i = 0; i < 1000000; i++);
		// Custom2LED(1);
		// for(i = 0; i < 1000000; i++);
		// Custom2LED(0);
		// for(i = 0; i < 1000000; i++);
		// Custom2LED(1);
		// for(i = 0; i < 1000000; i++);
		// Custom2LED(0);
		// for(i = 0; i < 1000000; i++);
		//
		//
		// Custom3LED(0);
		// for(i = 0; i < 1000000; i++);
		// Custom3LED(1);
		// for(i = 0; i < 1000000; i++);
		//
		// testTX(0);
		// for(i = 0; i < 1000000; i++);
		// testTX(1);
		// for(i = 0; i < 1000000; i++);
		//
		// testRX(0);
		// for(i = 0; i < 1000000; i++);
		// testRX(1);
		// for(i = 0; i < 1000000; i++);
		//
		// testSwitch(0);
		// for(i = 0; i < 3000000; i++);
		// testSwitch(1);
		// for(i = 0; i < 3000000; i++);

	}

    return 0 ;
}
