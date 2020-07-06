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

#include "PCE.h"
#include "Util.h"

static uint8_t _DDRD, _DDRB;

void PCE_Init(void) {
	// I
	bit_clear(DDRD, 1 << 0);
	bit_clear(PORTD, 1 << 0);

	// Up
	bit_clear(DDRD, 1 << 1);
	bit_clear(PORTD, 1 << 1);

	// II
	bit_clear(DDRD, 1 << 2);
	bit_clear(PORTD, 1 << 2);

	// Right
	bit_clear(DDRD, 1 << 3);
	bit_clear(PORTD, 1 << 3);

	// SELECT
	bit_clear(DDRD, 1 << 4);
	bit_clear(PORTD, 1 << 4);

	// DOWN
	bit_clear(DDRD, 1 << 5);
	bit_clear(PORTD, 1 << 5);

	// START
	bit_clear(DDRD, 1 << 6);
	bit_clear(PORTD, 1 << 6);

	// Left
	bit_clear(DDRB, 1 << 0);
	bit_clear(PORTB, 1 << 0);

	// III
	bit_clear(DDRB, 1 << 4);
	bit_clear(PORTB, 1 << 4);						

	// IV
	bit_clear(DDRB, 1 << 5);
	bit_clear(PORTB, 1 << 5);						

	// V
	bit_clear(DDRB, 1 << 6);
	bit_clear(PORTB, 1 << 6);						

	// VI
	bit_clear(DDRB, 1 << 7);
	bit_clear(PORTB, 1 << 7);						
}

void PCE_SetPadData(AbstractPad_t *padData)  {

	_DDRD = DDRD;
	_DDRB = DDRB;

	padData->d_up    ? bit_set(_DDRD, 1 << 1) : bit_clear(_DDRD, 1 << 1);
	padData->d_down  ? bit_set(_DDRD, 1 << 5) : bit_clear(_DDRD, 1 << 5);
	padData->d_left  ? bit_set(_DDRB, 1 << 0) : bit_clear(_DDRB, 1 << 0);
	padData->d_right ? bit_set(_DDRD, 1 << 3) : bit_clear(_DDRD, 1 << 3);

	padData->start ? bit_set(_DDRD, 1 << 6) : bit_clear(_DDRD, 1 << 6);
	padData->back  ? bit_set(_DDRD, 1 << 4) : bit_clear(_DDRD, 1 << 4);

	padData->a ? bit_set(_DDRD, 1 << 2) : bit_clear(_DDRD, 1 << 2);
	padData->b ? bit_set(_DDRD, 1 << 0) : bit_clear(_DDRD, 1 << 0);
	padData->x ? bit_set(_DDRB, 1 << 4) : bit_clear(_DDRB, 1 << 4);
	padData->y ? bit_set(_DDRB, 1 << 6) : bit_clear(_DDRB, 1 << 6);

	padData->lb ? bit_set(_DDRB, 1 << 5) : bit_clear(_DDRB, 1 << 5);
	padData->rb ? bit_set(_DDRB, 1 << 7) : bit_clear(_DDRB, 1 << 7);

	DDRD = _DDRD;
	DDRB = _DDRB;
}