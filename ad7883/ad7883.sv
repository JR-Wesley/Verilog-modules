
module ad7883
(
    input wire clk, rst_n,
    input wire start,
    //==== ads7883 ====
    output wire cs_n,
    output logic  sclk,
    input  wire sdo,
    output logic valid,
    input wire ready,
    output logic [11:0] data
);
//  cs_n    ^^^^\__________________ // _______________/^^^^
//  sclk    ^^^^^^\_/^\_/^\_/^\_/^\ // _/^\_/^\_/^\_/^^^^^^
//  start   ____|__________________________________________
//  buty    ____/^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\____
//  br_co   ______|_|_|_|_|_|_|_|_ // |_|_|_|_|_|_|_|_|____
//  hb_cnt  xxxx 0 1 2 3 4 5 6 7 8       25  27      32
//  sdo     ======X   XD11X   X    //   XD0 X   X   X
//  hb_co   __________________________________________|____
    logic busy;
    logic br_co, hb_co;
    logic [5:0] hb_cnt;
    Counter #(1)  brCnt(clk, ~rst_n, busy, , br_co);
    Counter #(33) hbCnt(clk, ~rst_n, br_co, hb_cnt, hb_co);
    always @(posedge clk) begin : proc_busy
        if(!rst_n) busy <= 1'b0;
        else if(hb_co) busy <= 1'b0;
        else if(start) busy <= 1'b1;
    end
    
    logic [11:0] sr;
    always @(posedge clk) begin : proc_sr
        if(!rst_n) sr <= 12'b0;
        else if(br_co & ~hb_cnt[0])
            sr <= (sr << 1) | sdo;
    end
    always @(posedge clk) begin : proc_tdata
        if(!rst_n) data <= 12'b0;
        else if(br_co & hb_cnt == 6'd28)
            data <= sr;
    end
    
    // === ads7883 ===
    assign cs_n = ~busy;
    // assign ads7883_sclk = ~hb_cnt[0] | ads7883_cs_n;
    always @(posedge clk) begin : proc_ads7883_sclk
        if(!rst_n) sclk <= 1'b1;
        else if(br_co) begin
            if(hb_cnt[0] | hb_co)
                sclk <= 1'b1;
            else if(~hb_cnt[0])
                sclk <= 1'b0;
        end
    end
    
    always @(posedge clk) begin : proc_tvalid
        if(~rst_n) begin
            valid <= 1'b0;
        end else begin
            if(hb_co)
                valid <= 1'b1;
            else if(valid & ready)
                valid <= 1'b0;
        end
    end
endmodule
