module trigger_fsm(
	input wire clk,//200Mhz
	input wire rst_n,
	input wire trigger,
	output logic sp_en
);
	logic [7:0]sp_cnt,
    logic delay_done;
    localparam SP_NUM=6;//256 points
    localparam DELAY_TIME=8'd200;//delay 1us

    localparam IDLE=3'b000;
    localparam SAMPLE=3'b001;
    localparam DELAY=3'b010;
    localparam WAIT=3'b011;
    localparam SP_5U_DELAY=3'b100;
    logic [2:0]state=IDLE;
    logic [2:0]next_state=IDLE;
    logic [7:0]delay_cnt;
    logic [7:0]sp_5u_cnt;
    logic sp_5u_done;

    //state
    always_ff @(posedge clk) begin
    if(!rst_n)
        state <= IDLE;
    else
        state <= next_state;
    end

    //state trans
    always_comb begin
        case(state)
        IDLE: begin
            if(trigger) next_state <= SAMPLE;
            else next_state <= IDLE;
        end
        SAMPLE: begin
            if(sp_cnt==SP_NUM-1) next_state <= IDLE;
            else next_state <= DELAY;
        end
        DELAY: begin
            if(delay_done) next_state <= WAIT;
            else next_state <= DELAY;
        end
        WAIT: begin
            if(trigger) next_state <= SP_5U_DELAY;
            else next_state <= WAIT;
        end
        SP_5U_DELAY: begin
            if(sp_5u_done) next_state <= SAMPLE;
            else next_state <= SP_5U_DELAY;
        end
        endcase
    end

    //sp_en
    always_comb begin
        case(state)
        SAMPLE: sp_en<=1;
        default: sp_en<=0;
        endcase
    end

    //sp_cnt
    always_ff@ (posedge clk) begin
        if(!rst_n) sp_cnt <= 0;
        else if(sp_en ) begin
            sp_cnt <= sp_cnt+1;
        end
        else if(sp_cnt==SP_NUM) sp_cnt<=0;
    end

    //delay
    always_ff@ (posedge clk) begin
        if(!rst_n) begin
            delay_cnt <= 0;
            delay_done <= 0;
        end
        else if(state==DELAY) begin
            if(delay_cnt<DELAY_TIME) begin
                delay_cnt <= delay_cnt+1;
                delay_done <= 0;
            end
            else if(delay_cnt==DELAY_TIME) begin
            delay_done <= 1;
            delay_cnt <= 0;
            end
        end
        else begin
            delay_cnt <= 0;
            delay_done <= 0;
        end
    end

    //sp_5us delay
    always_ff@ (posedge clk) begin
        if(!rst_n) begin
            sp_5u_cnt <= 0;
            sp_5u_done <= 0;
        end
        else if(state==SP_5U_DELAY) begin
            if(sp_5u_cnt < sp_cnt) begin
            sp_5u_done <= 0;
            sp_5u_cnt <= sp_5u_cnt+1;
            end
            else if(sp_5u_cnt == sp_cnt) begin
            sp_5u_done <= 1;
            sp_5u_cnt <= 0;
            end
        end
        else begin
            sp_5u_cnt <= 0;
            sp_5u_done <= 0;
        end
    end

endmodule