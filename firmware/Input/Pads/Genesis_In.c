/*
* MD2PCE - Sega Genesis Pad Adapter to USB/TG16/PCE
*
* Copyright (c) 2020
* Bruno Freitas - bruno@brunofreitas.com - http://www.brunofreitas.com/
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <util/delay.h>

#include "Genesis_In.h"
#include "Util.h"
#include "timer.h"

#define DELAY 14

static uint8_t six_button_controller;

uint8_t Genesis_In_Init(void) {
	// DB9P1
	bit_clear(DDRF, 1 << 6);
	bit_set(PORTF, 1 << 6);

	// DB9P2
	bit_clear(DDRF, 1 << 0);
	bit_set(PORTF, 1 << 0);

	// DB9P3
	bit_clear(DDRF, 1 << 1);
	bit_set(PORTF, 1 << 1);

	// DB9P4
	bit_clear(DDRF, 1 << 4);
	bit_set(PORTF, 1 << 4);

	// DB9P6
	bit_clear(DDRF, 1 << 5);
	bit_set(PORTF, 1 << 5);

	// DB9P7
	bit_set(DDRE, 1 << 6);
	bit_set(PORTE, 1 << 6);

	// DB9P9
	bit_clear(DDRC, 1 << 7);
	bit_set(PORTC, 1 << 7);

	six_button_controller = 0;

	return 1;
}

static uint16_t genesis_read(void) {
	uint16_t retval;

	int extrabuttons = 0;
	int normalbuttons = 0;

	six_button_controller = 0;

	// Get D-PAD, B, C buttons state
	normalbuttons |= (!bit_check(PINF, 6) << 0);
	normalbuttons |= (!bit_check(PINF, 0) << 1);
	normalbuttons |= (!bit_check(PINF, 1) << 2);
	normalbuttons |= (!bit_check(PINF, 4) << 3);
	normalbuttons |= (!bit_check(PINF, 5) << 4);
	normalbuttons |= (!bit_check(PINC, 7) << 5);

	// 1
	bit_clear(PORTE, 1 << 6);
	_delay_us(DELAY);

	// Is using a SEGA Genesis controller, LEFT and RIGHT will be ACTIVE here
	if(!(!bit_check(PINF, 1) && !bit_check(PINF, 4))) {
		bit_set(PORTE, 1 << 6);
		retval = normalbuttons | (extrabuttons << 8);
		return retval;
	}

	// Get A and START buttons state
	normalbuttons |= (!bit_check(PINF, 5) << 6);
	normalbuttons |= (!bit_check(PINC, 7) << 7);

	bit_set(PORTE, 1 << 6);
	_delay_us(DELAY);
	
	// 2
	bit_clear(PORTE, 1 << 6);
	_delay_us(DELAY);
	bit_set(PORTE, 1 << 6);
	_delay_us(DELAY);

	// 3
	bit_clear(PORTE, 1 << 6);
	_delay_us(DELAY);

	// Up, Down, Left and Right are low if 6-button controller
	if(!bit_check(PINF, 6) && !bit_check(PINF, 0) && !bit_check(PINF, 1) && !bit_check(PINF, 4)) {
		bit_set(PORTE, 1 << 6);
		_delay_us(DELAY);

		extrabuttons |= (!bit_check(PINF, 6) << 0);
		extrabuttons |= (!bit_check(PINF, 0) << 1);
		extrabuttons |= (!bit_check(PINF, 1) << 2);
		extrabuttons |= (!bit_check(PINF, 4) << 3);

		// 4
		bit_clear(PORTE, 1 << 6);
		_delay_us(DELAY);

		// 8bitdo sega genesis receiver support - home button might be pressed here
		extrabuttons |= ((!bit_check(PINF, 6)) << 4);

		bit_set(PORTE, 1 << 6);

		six_button_controller = 1;

		// Required delay for settling 6 button controller down
		_delay_ms(2);
	}

	bit_set(PORTE, 1 << 6);

	retval = normalbuttons | (extrabuttons << 8);

	return retval;
}

void Genesis_In_GetPadState(AbstractPad_t *padData) {	
	int button_data = genesis_read();

	padData->d_up = bit_check(button_data, GENESIS_UP);
	padData->d_down = bit_check(button_data, GENESIS_DOWN);
	padData->d_left = bit_check(button_data, GENESIS_LEFT);
	padData->d_right = bit_check(button_data, GENESIS_RIGHT);

	padData->a = bit_check(button_data, GENESIS_B);
	padData->b = bit_check(button_data, GENESIS_C);
	padData->start = bit_check(button_data, GENESIS_START);

	if(six_button_controller) {
		padData->x = bit_check(button_data, GENESIS_A);
		padData->lb = bit_check(button_data, GENESIS_X);
		padData->rb = bit_check(button_data, GENESIS_Z);
		padData->y = bit_check(button_data, GENESIS_Y);
		padData->back = bit_check(button_data, GENESIS_MODE);
	} else {
		padData->back = bit_check(button_data, GENESIS_A);
	}

	padData->menu = ((padData->d_up && padData->start) || bit_check(button_data, GENESIS_8BITDO_HOME));
}