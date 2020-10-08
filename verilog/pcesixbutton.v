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

module pcesixbutton(
    input system_clock,
    input sel,
    input clr,
    input i,
    input ii,
    input select,
    input start,
    input up,
    input right,
    input down,
    input left,
    input iii,
    input iv,
    input v,
    input vi,
    output reg [3:0] d = 4'b1111
);

reg sync_clr, xfer_pipe_clr;
reg sync_sel, xfer_pipe_sel;

reg mux = 1'b0;

always @(posedge system_clock) begin
    { sync_clr, xfer_pipe_clr } <= { xfer_pipe_clr, clr };
    { sync_sel, xfer_pipe_sel } <= { xfer_pipe_sel, sel };
end

always @(posedge sync_clr) begin
    mux <= !mux;
end

always @(*) begin
    case ({mux, sync_sel})
        2'b00: d = {start, select, ii, i};
        2'b01: d = {left, down, right, up};
        2'b10: d = {vi, v, iv, iii};
        2'b11: d = {1'b0, 1'b0, 1'b0, 1'b0};
    endcase        
end 

endmodule