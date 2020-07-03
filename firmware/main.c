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

#include "Input.h"
#include "Output.h"
#include "Util.h"

AbstractPad_t PadData_DB9;

int main(void) {

	// Set clock @ 16Mhz
	CPU_PRESCALE(0);

	// Disable JTAG
	bit_set(MCUCR, 1 << JTD);
	bit_set(MCUCR, 1 << JTD);

	// Reset pad data buffers
	AbstractPad_ResetBuffer(&PadData_DB9);

	// Initialize TG16/PCE and USB interfaces
	Output_Init();

	// Initialize DB9 interface
	Input_Init();

	// Main loop
	for (;;) {
		Input_GetPadState(&PadData_DB9);

		Output_SetPadState(&PadData_DB9);
	}
}