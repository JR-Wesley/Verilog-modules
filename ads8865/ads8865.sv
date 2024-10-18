module ads8865(
	input wire clk,//sys_clk 100MHz
	input wire rst_n, start,
//interface to ad chip
	output logic sclk,
	output logic convst,
	output logic din,
	input wire data,
//data to ps,
	output logic [15:0] ad_data
);

//  sclk     ^^^^^^\_/^\_/^\_/^\_/^\ ... _/^\_/^\_/^\_/^^^^^
//  start    ____|__________________________________________
//  busy     ____/^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\____
//  cs_n     ____/^^^^^^^^^^^^^^^\__________________________
//  hbr_co   ____|_|_|_|_|_|_|_|_ ... |_|_|_|_|_|_|_|_|_____
//  bit_cnt  xxxx 0 1 2 3 4 5 6 7 8       30  27      45 xxx
//  sp_en    _______________________|_|_|_|_|_|_|_|_|_|_|___
//  bit_co   _________________________________________|_____
//  acq	     ____________________/^^^^^^^^^^^^^^^^^^^^\_____
//  data     =========================X   XD11X   X ========

logic busy;
logic hbr_co, bit_co;
logic [1:0] hbr_cnt;
logic [6:0] bit_cnt;
Counter #(4) brCnt(clk,~rst_n,busy,hbr_cnt,hbr_co);//40ns half sclk period
Counter #(70) bCnt(clk,~rst_n,hbr_co&busy,bit_cnt,bit_co);//sample period 70*40=2800ns

//busy
always_ff@(posedge clk) begin
	if(!rst_n) busy<=0;
	else if(start) busy<=1;
	else if(bit_co) busy<=0;
end

//sclk 80ns
always_ff@(posedge clk) begin
	if(!rst_n) sclk<='0;
	else sclk<=bit_cnt[0];
end
 
logic acq;

//convst 35*40=1600ns
always_ff@(posedge clk) begin
    if(!rst_n) acq<=0;
    else if(bit_cnt==35) acq<='1;
    else if(bit_co) acq<='0;
end

//start,15conv_max 35*40=1600ns
always_ff@(posedge clk) begin
	if(!rst_n) convst<=0;
	else if(start) convst<=1;
	else if(bit_cnt==35) convst<=0;
end

//acq
logic sp_en;
always_ff@(posedge clk)begin
	if(!rst_n) sp_en<='0;
	else if((hbr_cnt==2'b11)&sclk) sp_en<='1;
	else sp_en<='0;
end

//data_cnt
logic [15:0]reg_data;
logic [4:0]data_cnt=4'b0;
logic data_co='0;
always_ff@(posedge clk)begin
	if(!rst_n) data_co<='0;
	else if(data_cnt==16) data_co<='1;
	else if(bit_co) data_co<='0;
end

//data_trans
always_ff@(posedge clk)begin
	if(!rst_n) begin
		reg_data<='0;
		data_cnt<='0;
	end
	else if(acq&sp_en)begin
            if((data_cnt!=16)&(~data_co)) begin
				reg_data<={reg_data[14:0],data};
				data_cnt=data_cnt+1'b1;
            end
			else data_cnt<='0;
	end
	else if(bit_co) data_cnt<='0;
end

always_ff@(posedge clk)begin
	if(!rst_n) ad_data<=reg_data;
	else if(bit_co) ad_data<=reg_data;
end

assign din=1;
endmodule
