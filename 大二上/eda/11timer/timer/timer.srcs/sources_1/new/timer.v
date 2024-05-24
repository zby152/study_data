`timescale 1ns / 1ps

module timer(
    input CLK,
    input rst_n,
    output reg [7:0]seg_sel,//数码管显示信号，选择使用哪一个数码管
    output [6:0] oDisplay
    );
    
    reg  [20:0]cnt;

    always @(posedge CLK or negedge rst_n)
        begin
            if(rst_n)
                cnt<=0;
            else
                cnt<=cnt+1;
        end
     assign CLK_1=cnt[19];
     assign CLK_2=cnt[16];
        
        reg [5:0] hour;
        reg [5:0] minute;
        reg [5:0] second;
        reg [5:0] msecond;
        reg [3:0] hour_high;
        reg [3:0] hour_low;
        reg [3:0] minute_high;
        reg [3:0] minute_low;
        reg [3:0] second_high;
        reg [3:0] second_low;
        reg [3:0] msecond_high;
        reg [3:0] msecond_low;
        
    //确定毫秒数跟随时钟跳动
    always@(posedge CLK_1 or negedge rst_n)
        begin
            if(rst_n)
                msecond<=0;
            else
                begin
                    if(msecond==59)
                        msecond<=0;
                    else 
                        msecond=msecond+1'b1;
                end
            msecond_high<=msecond/10;//毫秒的高位
            msecond_low<=msecond%10; //毫秒的低位
        end   
    
    //确定秒跟随时钟跳动
    always@(posedge CLK_1 or negedge rst_n)
        begin
            if(rst_n)
                second<=0;
            else
                begin
                    if(second==59 && msecond==59)
                        second<=0;
                    else if(msecond==59)
                        second<=second+1'b1;
                end
            second_high<=second/10;//秒的高位
            second_low<=second%10;//秒的低位
        end
            
    //确定分随时钟跳动
    always@(posedge CLK_1 or negedge rst_n)
        begin
            if(rst_n)
                minute<=0;
            else
                begin
                    if(minute==59 && second==59 && msecond==59)
                        minute<=0;
                    else if(second==59 && msecond==59)
                        minute<=minute+1'b1;
                end
            minute_high<=minute/10;//分的高位
            minute_low<=minute%10;//分的低位
        end
        
        //确定时随时钟跳动
        always@(posedge CLK_1 or negedge rst_n)
                begin
                    if(rst_n)
                        hour<=0;
                    else
                        begin
                            if(hour==23 && minute==59 && second==59 && msecond==59)
                                hour<=0;
                            else if(minute==59 && second==59 && msecond==59)
                                hour<=hour+1'b1;
                        end
                    hour_high<=hour/10;//时的高位
                    hour_low<=hour%10;//时的低位
                end
            
    reg [2:0] cnt_sel;
            
    //选择使用哪一个晶体管
    always@(posedge CLK_2 or negedge rst_n)
        begin
            if(rst_n)
                cnt_sel<=3'b000;
            else
                begin
                    if(cnt_sel<3'd7)
                        cnt_sel<=cnt_sel+1'b1;
                    else
                        cnt_sel<=3'b0;
                end
        end
                
    reg [3:0] temp;
    
    //对每一个晶体管进行刷新
    always @(posedge CLK or negedge rst_n)
        begin
            if(rst_n)
                seg_sel<=8'b11111111;
            else
                begin
                    case(cnt_sel)
                        3'b000:{seg_sel,temp}<={8'b11111110,msecond_low};
                        3'b001:{seg_sel,temp}<={8'b11111101,msecond_high};
                        3'b010:{seg_sel,temp}<={8'b11111011,second_low};
                        3'b011:{seg_sel,temp}<={8'b11110111,second_high};
                        3'b100:{seg_sel,temp}<={8'b11101111,minute_low};
                        3'b101:{seg_sel,temp}<={8'b11011111,minute_high};
                        3'b110:{seg_sel,temp}<={8'b10111111,hour_low};
                        3'b111:{seg_sel,temp}<={8'b01111111,hour_high};
                    endcase
                 end
         end
                 
     display7 U1(.iData(temp), .oData(oDisplay));
     
 endmodule
         
                                
module display7(
 input [3:0] iData,
 output [6:0] oData
 );
 
 reg [6:0]tData;
 assign oData=tData;
 
 always @(*)
     begin
         case(iData)
             4'b0000: tData=7'b1000000;
             4'b0001: tData=7'b1111001;
             4'b0010: tData=7'b0100100;
             4'b0011: tData=7'b0110000;
             4'b0100: tData=7'b0011001;
             4'b0101: tData=7'b0010010;
             4'b0110: tData=7'b0000010;
             4'b0111: tData=7'b1111000;
             4'b1000: tData=7'b0000000;
             4'b1001: tData=7'b0010000;
             default: tData=7'b1111111;
         endcase
     end
 endmodule
