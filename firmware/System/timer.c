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
#include <avr/interrupt.h>

#include "timer.h"

static volatile uint32_t msTicks;

void timer_init(void) {
	msTicks = 0;

	// Timer0 overflow interrupt setup: Prescaler = FCPU/64
	TCCR0A = 0;
	TCCR0B |= (1 << CS01) | (1 << CS00);

	TCNT0 = 6;

	// Enable Timer0 overflow interrupt:
	TIMSK0 = (1 << TOIE0);

	sei();
}

uint32_t timer_millis(void) {
	return msTicks;
}

// 1ms timer for a 16Mhz Clock
ISR(TIMER0_OVF_vect) {
	TCNT0 += 6;

	msTicks++;
}