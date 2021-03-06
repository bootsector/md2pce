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

#ifndef ABSTRACTPAD_H_
#define ABSTRACTPAD_H_

#include <stdint.h>

/* Definition of an abstract joypad structure for the adapter */
typedef struct
{
	// Digital Buttons
	uint8_t x;
	uint8_t a;
	uint8_t b;
	uint8_t y;
	uint8_t lb;
	uint8_t rb;
	uint8_t lt;
	uint8_t rt;
	uint8_t back;
	uint8_t start;
	uint8_t l_thumb;
	uint8_t r_thumb;
	uint8_t menu;

	// Digital Pad
	uint8_t d_up;
	uint8_t d_down;
	uint8_t d_left;
	uint8_t d_right;

	// Left and right analog sticks
	uint8_t l_x;
	uint8_t l_y;
	uint8_t r_x;
	uint8_t r_y;

} AbstractPad_t;

void AbstractPad_ResetBuffer(AbstractPad_t *padData);

#endif /* ABSTRACTPAD_H_ */