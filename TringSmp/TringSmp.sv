module TringSmp(
    output logic busy,
	input wire clk,//200Mhz
	input wire rst_n,
	input wire trigger,
	output logic sp_en,
	output logic hold
);

	localparam POINT_NUM=256;
	logic [7:0]point_cnt;
	logic sp_done;
	logic [9:0]delay_cnt;
	logic [9:0]delay_time;

	//busy 
	always_ff@(posedge clk) begin
	if(!rst_n) busy<=0;
		else if(trigger&&~busy) busy<=1;
		else if(sp_done) busy<=0;
	end

	//sp point counter
	always_ff@(posedge clk) begin
		if(~rst_n) point_cnt <= '0;
		else if(sp_en) begin
			if(point_cnt < POINT_NUM - 1) point_cnt <= point_cnt + 1'b1;
			else if(point_cnt== POINT_NUM-1) begin
				sp_done=1;
				point_cnt <= '0;
			end
		end
		else sp_done<=0;
	end
	
	//sp delay counter
	assign delay_time=10'd200+point_cnt;
	always_ff@(posedge clk)begin
	if(!rst_n) delay_cnt<=0;
	else if(busy) begin
		if(delay_cnt<delay_time-1) delay_cnt<=delay_cnt+1;
		else if(delay_cnt==delay_time-1) delay_cnt<=0;
	end
	else
		delay_cnt<=0;
	end
	
	assign sp_en=(delay_cnt==0)&&busy;

endmodule