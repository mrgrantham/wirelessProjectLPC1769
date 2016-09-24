#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lpc17xx_pinsel.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_gpio.h"

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

	LedPin.Portnum = PINSEL_PORT_2;
	LedPin.Pinnum = PINSEL_PIN_13;
	PINSEL_ConfigPin(&LedPin);

	// Set IO Direction
	GPIO_SetDir(PINSEL_PORT_0, (1 << PINSEL_PIN_22), GPIO_DIR_OUTPUT); // Red LED
	GPIO_SetDir(PINSEL_PORT_3, (1 << PINSEL_PIN_26), GPIO_DIR_OUTPUT); // Blue LED
	GPIO_SetDir(PINSEL_PORT_3, (1 << PINSEL_PIN_25), GPIO_DIR_OUTPUT); // Green LED
	GPIO_SetDir(PINSEL_PORT_2, (1 << PINSEL_PIN_12), GPIO_DIR_OUTPUT); // Custom LED
	GPIO_SetDir(PINSEL_PORT_2, (1 << PINSEL_PIN_11), GPIO_DIR_OUTPUT); // Custom LED
	GPIO_SetDir(PINSEL_PORT_1, (1 << PINSEL_PIN_18), GPIO_DIR_OUTPUT); // Custom LED
	GPIO_SetDir(PINSEL_PORT_2, (1 << PINSEL_PIN_13), GPIO_DIR_OUTPUT); // Custom LED

	// Set them all off (set to 1)
	RedLED(1);
	BlueLED(1);
	GreenLED(1);
	Custom0LED(1);
	Custom1LED(1);
	Custom2LED(1);
	Custom3LED(1);

}


int main(void)
{
	int i;
	Init_Pwr();
	Init_GPIO_Pins();

	while(1)
	{
		RedLED(0);
		for(i = 0; i < 1000000; i++);
		RedLED(1);
		for(i = 0; i < 1000000; i++);

		RedLED(0);
		BlueLED(0);
		for(i = 0; i < 1000000; i++);
		BlueLED(1);
		RedLED(1);
		for(i = 0; i < 1000000; i++);

		BlueLED(0);
		GreenLED(0);
		for(i = 0; i < 1000000; i++);
		GreenLED(1);
		BlueLED(1);
		for(i = 0; i < 1000000; i++);


		BlueLED(0);
		for(i = 0; i < 1000000; i++);
		BlueLED(1);
		for(i = 0; i < 1000000; i++);

		GreenLED(0);
		for(i = 0; i < 1000000; i++);
		GreenLED(1);
		for(i = 0; i < 1000000; i++);

		GreenLED(0);
		RedLED(0);
		for(i = 0; i < 3000000; i++);
		GreenLED(1);
		RedLED(1);
		for(i = 0; i < 3000000; i++);

		Custom0LED(0);
		for(i = 0; i < 3000000; i++);
		Custom0LED(1);
		for(i = 0; i < 3000000; i++);


		Custom1LED(0);
		for(i = 0; i < 3000000; i++);
		Custom1LED(1);
		for(i = 0; i < 3000000; i++);

		Custom2LED(0);
		for(i = 0; i < 3000000; i++);
		Custom2LED(1);
		for(i = 0; i < 3000000; i++);

		Custom3LED(0);
		for(i = 0; i < 3000000; i++);
		Custom3LED(1);
		for(i = 0; i < 3000000; i++);

	}

    return 0 ;
}
