/*
 * ssd.h
 *
 *  Created on: Nov 27, 2019
 *      Author: CS152B
 */

#ifndef SSD_H_
#define SSD_H_
#include "xgpio.h"

#define DISPLAY_A      (1 << 0)
#define DISPLAY_F      (1 << 1)
#define DISPLAY_E      (1 << 2)
#define DISPLAY_D      (1 << 3)
#define DISPLAY_DIGIT  (1 << 4)
#define DISPLAY_G      (1 << 5)
#define DISPLAY_C      (1 << 6)
#define DISPLAY_B      (1 << 7)

#define DISPLAY_OFF 0

#define DISPLAY_CHAR_0 (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F            )
#define DISPLAY_CHAR_1 (            DISPLAY_B | DISPLAY_C                                                )
#define DISPLAY_CHAR_2 (DISPLAY_A | DISPLAY_B             | DISPLAY_D | DISPLAY_E             | DISPLAY_G)
#define DISPLAY_CHAR_3 (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D                         | DISPLAY_G)
#define DISPLAY_CHAR_4 (            DISPLAY_B | DISPLAY_C                         | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_5 (DISPLAY_A             | DISPLAY_C | DISPLAY_D             | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_6 (DISPLAY_A             | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_7 (DISPLAY_A | DISPLAY_B | DISPLAY_C                                                )
#define DISPLAY_CHAR_8 (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_9 (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D             | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_A (DISPLAY_A | DISPLAY_B | DISPLAY_C             | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_B (                        DISPLAY_C | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_C (DISPLAY_A                         | DISPLAY_D | DISPLAY_E | DISPLAY_F            )
#define DISPLAY_CHAR_D (            DISPLAY_B | DISPLAY_C | DISPLAY_D | DISPLAY_E             | DISPLAY_G)
#define DISPLAY_CHAR_E (DISPLAY_A                         | DISPLAY_D | DISPLAY_E | DISPLAY_F | DISPLAY_G)
#define DISPLAY_CHAR_F (DISPLAY_A                                     | DISPLAY_E | DISPLAY_F | DISPLAY_G)

void displayChar(char c, XGpio DisplayGpio) {
	switch(toupper(c)) {
	case '0': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_0); break;
	case '1': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_1); break;
	case '2': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_2); break;
	case '3': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_3); break;
	case '4': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_4); break;
	case '5': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_5); break;
	case '6': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_6); break;
	case '7': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_7); break;
	case '8': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_8); break;
	case '9': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_9); break;
	case 'A': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_A); break;
	case 'B': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_B); break;
	case 'C': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_C); break;
	case 'D': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_D); break;
	case 'E': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_E); break;
	case 'F': XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_CHAR_F); break;
	default:  XGpio_DiscreteWrite(&DisplayGpio, 1, DISPLAY_OFF); break;
	}
}


#endif /* SSD_H_ */
