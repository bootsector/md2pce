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

#include "Output.h"
#include "PCE.h"
#include "XInputPad.h"
#include "Util.h"

void Output_Init(void) {
	xbox_init(true);
	PCE_Init();
}

static void Output_SetUSBData(AbstractPad_t *padData) {

	padData->d_up    ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_UP)    : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_UP);
	padData->d_down  ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_DOWN)  : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_DOWN);
	padData->d_left  ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_LEFT)  : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_LEFT);
	padData->d_right ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_RIGHT) : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_RIGHT);

	padData->start ? bit_set(gamepad_state.digital_buttons_1, XBOX_START)       : bit_clear(gamepad_state.digital_buttons_1, XBOX_START);
	padData->back  ? bit_set(gamepad_state.digital_buttons_1, XBOX_BACK)        : bit_clear(gamepad_state.digital_buttons_1, XBOX_BACK);

	padData->a ? bit_set(gamepad_state.digital_buttons_2, XBOX_A)    : bit_clear(gamepad_state.digital_buttons_2, XBOX_A);
	padData->b ? bit_set(gamepad_state.digital_buttons_2, XBOX_B)  : bit_clear(gamepad_state.digital_buttons_2, XBOX_B);
	padData->x ? bit_set(gamepad_state.digital_buttons_2, XBOX_X)  : bit_clear(gamepad_state.digital_buttons_2, XBOX_X);
	padData->y ? bit_set(gamepad_state.digital_buttons_2, XBOX_Y) : bit_clear(gamepad_state.digital_buttons_2, XBOX_Y);

	padData->lb ? bit_set(gamepad_state.digital_buttons_2, XBOX_LB)  : bit_clear(gamepad_state.digital_buttons_2, XBOX_LB);
	padData->rb ? bit_set(gamepad_state.digital_buttons_2, XBOX_RB) : bit_clear(gamepad_state.digital_buttons_2, XBOX_RB);

	padData->menu ? bit_set(gamepad_state.digital_buttons_2, XBOX_HOME) : bit_clear(gamepad_state.digital_buttons_2, XBOX_HOME);

	padData->l_thumb ? bit_set(gamepad_state.digital_buttons_1, XBOX_LEFT_STICK)  : bit_clear(gamepad_state.digital_buttons_1, XBOX_LEFT_STICK);
	padData->r_thumb ? bit_set(gamepad_state.digital_buttons_1, XBOX_RIGHT_STICK) : bit_clear(gamepad_state.digital_buttons_1, XBOX_RIGHT_STICK);

	gamepad_state.lt = padData->lt;
	gamepad_state.rt = padData->rt;
}

void Output_SetPadState(AbstractPad_t *padData) {

	xbox_reset_watchdog();

	PCE_SetPadData(padData);

	Output_SetUSBData(padData);

	xbox_send_pad_state();
}