/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"
#include "xgpio.h"
#include "ssd.h"

#ifdef __MICROBLAZE__
#define CPU_CLOCK_FREQ_HZ (XPAR_CPU_CORE_CLOCK_FREQ_HZ)
#else
#define CPU_CLOCK_FREQ_HZ (XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ)
#endif

#define LED_CHANNEL 1
#define KEYPAD_CHANNEL 1
#define SSD_CHANNEL 1
#define XPAR_LEDS_8BIT_DEVICE_ID 1
void print(char *str);

#define SSD_DEVICE_ID XPAR_XPS_GPIO_0_DEVICE_ID
#define KEYPAD_DEVICE_ID XPAR_XPS_GPIO_1_DEVICE_ID


#define DISPLAY_C  (1 << 0)
#define DISPLAY_AG (1 << 1)
#define DISPLAY_AF (1 << 2)
#define DISPLAY_AE (1 << 3)
#define DISPLAY_AD (1 << 4)
#define DISPLAY_AC (1 << 5)
#define DISPLAY_AB (1 << 6)
#define DISPLAY_AA (1 << 7)

#define DISPLAY_0 (DISPLAY_AA | DISPLAY_AB | DISPLAY_AC | DISPLAY_AD | DISPLAY_AE | DISPLAY_AF)
#define DISPLAY_1 (DISPLAY_AB | DISPLAY_AC)
#define DISPLAY_2 (DISPLAY_AA | DISPLAY_AB | DISPLAY_AD | DISPLAY_AE | DISPLAY_AG)
#define DISPLAY_3 (DISPLAY_AA | DISPLAY_AB | DISPLAY_AC | DISPLAY_AD | DISPLAY_AG)
#define DISPLAY_4 (DISPLAY_AB | DISPLAY_AC | DISPLAY_AF | DISPLAY_AG)
#define DISPLAY_5 (DISPLAY_AA | DISPLAY_AF | DISPLAY_AG | DISPLAY_AC | DISPLAY_AD)
#define DISPLAY_6 (DISPLAY_AA | DISPLAY_AF | DISPLAY_AG | DISPLAY_AC | DISPLAY_AD | DISPLAY_AE)
#define DISPLAY_7 (DISPLAY_AA | DISPLAY_AB | DISPLAY_AC)
#define DISPLAY_8 (~DISPLAY_C)
#define DISPLAY_9 (DISPLAY_AA | DISPLAY_AB | DISPLAY_AC | DISPLAY_AD | DISPLAY_AF | DISPLAY_AG)


XGpio KeypadGpio;
XGpio sGpio;

int Status;

int readKey();
int readKeyPad();
void displaySSD(int x);

int main()
{

    init_platform();

    // Initialize SSD
	Status = XGpio_Initialize(&sGpio, SSD_DEVICE_ID);
	if (Status  != XST_SUCCESS) {
		exit(1);
	}
	XGpio_SetDataDirection(&sGpio, 1, 0); // Output

	displaySSD(1);




	// Initialize Keypad
	Status = XGpio_Initialize(&KeypadGpio, KEYPAD_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		exit(1);
	}
	XGpio_SetDataDirection(&KeypadGpio, KEYPAD_CHANNEL, 0x0f); // Input


	print("Press the keypad :)\n");
	while(1)
	{
		int display_me = readKeyPad();
		displaySSD(display_me);
	}


    return 0;


}



int readKeyPad() {
	while(1) {
		if (readKey() == 17 || readKey() == 57 || readKey() == 59)
		{
			while (readKey() != 255); // one input for each key press
			print("Key pressed is 1\n");
			return 1;
		}
		if (readKey() == 33)
		{
			while (readKey() != 255);
			print("Key pressed is 2\n");
			return 2;
		}
		if (readKey() == 65)
		{
			while (readKey() != 255);
			print("Key pressed is 3\n");
			return 3;
		}
		if (readKey() == 18 || readKey() == 58)
		{
			while (readKey() != 255);
			print("Key pressed is 4\n");
			return 4;
		}
		if (readKey() == 34)
		{
			while (readKey() != 255);
			print("Key pressed is 5\n");
			return 5;
		}
		if (readKey() == 66)
		{
			while (readKey() != 255);
			print("Key pressed is 6\n");
			return 6;
		}
		if (readKey() == 20)
		{
			while (readKey() != 255);
			print("Key pressed is 7\n");
			return 7;
		}
		if (readKey() == 36)
		{
			while (readKey() != 255);
			print("Key pressed is 8\n");
			return 8;
		}
		if (readKey() == 68)
		{
			while (readKey() != 255);
			print("Key pressed is 9\n");
			return 9;
		}
	}
}

int readKey() {
	int col = 0;
	unsigned int Data = 0;
	u32 out = 0;
	for(col = 0; col < 4; col++) {
		int row = 0;
		//u32 colMask = ~(1 << col);
		u32 colMask = 0xF0 ^ (0x10 << col);
		XGpio_DiscreteWrite(&KeypadGpio, 1, colMask);
		Data = XGpio_DiscreteRead(&KeypadGpio, 1);
		out |= ~Data & 0x0F;
				if (~Data & 0x0F) {
					out |= 0x10 << col;
				}


	}

	char data[100];
	sprintf(data, "%d", out);
	return out;
	//print("Updated input. Data: ");
	//print(data);
	//print("\n");

}

void displaySSD(int x) {
	switch(x) {
	case 0: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_0); break;
	case 1: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_1); break;
	case 2: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_2); break;
	case 3: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_3); break;
	case 4: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_4); break;
	case 5: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_5); break;
	case 6: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_6); break;
	case 7: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_7); break;
	case 8: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_8); break;
	case 9: XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_9); break;
	default:XGpio_DiscreteWrite(&sGpio, 1, DISPLAY_C); break;
	}
}


// DUMP

//XGpio_DiscreteWrite(&sGpio, 1, 0b00101011);
//XGpio_DiscreteWrite(&sGpio, 1, 0b00001000);
//XGpio_DiscreteWrite(&sGpio, 1, 0b00111011);
//XGpio_DiscreteWrite(&sGpio, 1, 0b00011000);

//XGpio_DiscreteWrite(&sGpio, 1, 0b00111000);

//XGpio_DiscreteWrite(&sGpio, 1, 0b00111000);
//XGpio_DiscreteWrite(&sGpio, 1, 0b00011000);
//XGpio_DiscreteWrite(&sGpio, 1, 0b11011000);
//XGpio_DiscreteWrite(&sGpio, 1, 0b00111000);

//XGpio_DiscreteWrite(&sGpio, 1, 0b00011100);
//int G_1 = 0b00111000;
//int G_2 = 0b00011000;

//int blah = 0b00101001;
//int blah2 = 0b00101010;