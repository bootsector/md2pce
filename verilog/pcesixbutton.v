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
    mux <= ~mux;
end

always @(*) begin
    case ({mux, sync_sel})
        2'b00: d = {i, ii, select, start};
        2'b01: d = {up, right, down, left};
        2'b10: d = {iii, iv, v, vi};
        2'b11: d = {1'b0, 1'b0, 1'b0, 1'b0};
    endcase
end 

endmodule