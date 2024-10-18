`timescale 1ns / 1ps

module ad9235(
    input wire sys_clk,
    input wire rst_n,
    output reg CLK,
    input wire [11:0]D,
    output reg [11:0]data
    );
    always@(posedge sys_clk) begin
        if(!rst_n) CLK<=0;
        else CLK<=~CLK;
    end
    
    always@(posedge sys_clk) begin
    if(!rst_n) data<=0;
    else if(~CLK) begin
        data<=D;
        end
    end

endmodule
