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

`timescale 1ns / 100ps // time-unit = 1 ns, precision = 100 ps
module pcesixbutton_tb;
    // Inputs
    reg sel;
    reg clr;

    reg i;
    reg ii;
    reg select;
    reg start;
    reg up;
    reg right;
    reg down;
    reg left;
    reg iii;
    reg iv;
    reg v;
    reg vi;
    
    reg sys_clk = 1'd0;

    // Outputs
    wire [3:0] d;

    integer j;

    // Instantiate the Unit Under Test (UUT)
    pcesixbutton uut (
        .system_clock(sys_clk),
        .sel(sel), 
        .clr(clr), 
        .i(i),
        .ii(ii),
        .select(select),
        .start(start),
        .up(up),
        .right(right),
        .down(down),
        .left(left),
        .iii(iii),
        .iv(iv),
        .v(v),
        .vi(vi),
        .d(d)
    );

    always #50 sys_clk <= !sys_clk; // 20Mhz

    initial begin
        $timeformat(-3, 2, " ms", 10); 
        $dumpfile("pce.vcd");
        $dumpvars(1, pcesixbutton_tb);
        
        // Initialize Inputs
        sel = 1;
        clr = 1;

        i = 1;
        ii = 0;
        select = 1;
        start = 1;
        up = 1;
        right = 1;
        down = 0;
        left = 1;
        iii = 0;
        iv = 0;
        v = 1;
        vi = 1;

        for(j = 0; j < 5; j=j+1) begin
            #13000 clr = 0;

            #13000 sel = 0;

            #13000 clr = 1; sel = 1;

            #1300 clr = 0;

            #13000 sel = 0;

            #13000 clr = 1; sel = 1;

            #166000 $display("delay");
        end

        $finish();
    end  

    initial begin
        $monitor("d0=%d,d1=%d,d2=%d,d3=%d,sel=%d,clr=%d",d[3],d[2],d[1],d[0],sel,clr);
    end

endmodule