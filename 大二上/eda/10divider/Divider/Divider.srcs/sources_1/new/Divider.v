`timescale 1ns / 1ps

module counter8(
    input CLK,
    input rst_n,
    input sw0,
    input sw1,
    input sw2,
    input sw3,
    output [2:0] oQ,
    output [6:0] oDisplay
    );
    wire Q0,Q1,Q2;//JK触发器的输出
    wire [3:0] display_in;  //Jk触发器的输入
    reg [24:0] cnt;    //降频所需要的24位2进制数
    wire f1;     //保存降频之后的时钟
    
    //使用分频器调整频率
    Divider D1(CLK,ret_n,sw0,sw1,sw2,sw3,f1);
    
    //调用JK触发器进行状态的改变
    JK U1(f1,1,1,rst_n,Q0);
    JK U2(f1,Q0,Q0,rst_n,Q1);
    JK U3(f1,Q0&&Q1,Q0&&Q1,rst_n,Q2);
    
    //将触发器得出的状态当作数字管的输入，模8所以最高位放1,
    assign display_in[0]=Q0;
    assign display_in[1]=Q1;
    assign display_in[2]=Q2;
    assign display_in[3]=1'b0;
    assign oQ=display_in;
    
    display7 Di1(.iData(display_in), .oData(oDisplay));
    
endmodule


//JK触发器
module JK(
    input CLK,
    input J,
    input K,
    input rst_n,
    output reg Q
);

always @(posedge CLK or negedge rst_n)
    begin
        if(rst_n)
            begin
                Q<=1'b0;
            end
        else
            begin
                case({J,K})
                    2'b00:
                        begin
                            Q<=Q;
                        end 
                    2'b01:
                        begin
                            Q<=1'b0;
                        end
                    2'b10:
                        begin
                            Q<=1'b1;
                        end
                    2'b11:
                        begin
                            Q<=~Q;
                        end
                endcase
            end
        end
                        
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

module Divider(
    input I_CLK,
    input rst,
    input sw0,
    input sw1,
    input sw2,
    input sw3,
    output O_CLK
);
    reg O_CLK_1=1'b0;
    assign O_CLK=O_CLK_1;
    reg [24:0] cnt;
    
    always @(posedge I_CLK)
        begin
            if(rst) 
                cnt<=0;
            else
                cnt<=cnt+1;
            if(sw0==1)
                begin
                    O_CLK_1 <= cnt[24];
                end
            else if (sw1==1)
                begin
                    O_CLK_1<= cnt[23];
                end
            else if(sw2==1)
                begin
                    O_CLK_1<=cnt[22];
                end
            else if(sw3==1)
                begin
                    O_CLK_1<=cnt[21];
                end
         end

endmodule
