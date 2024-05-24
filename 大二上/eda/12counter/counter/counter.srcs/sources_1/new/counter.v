`timescale 1ns / 1ps

module counter(
input CLK,
input rst,
input sw0,
input sw1,
output [6:0] oDisplay,
output  [7:0]seg_sel,
output L0,
output L1
);

reg  [30:0]cnt;

//½µÆµ
    always @(posedge CLK or negedge rst)
        begin
            if(rst)
                cnt<=0;
            else
                cnt<=cnt+1;
        end   
    reg CLK_1=1'b1;
    always @(posedge CLK )
        begin
            if(sw0==1)
                  CLK_1=cnt[21];
            else if(sw1==1)
                  CLK_1=cnt[20];
            else
                 CLK_1=cnt[22];
        end

    assign CLK_A=cnt[15];
    assign CLK_B=cnt[16];
    assign CLK_C=cnt[17];
     
    wire [3:0] Q0;
    wire [3:0] Q1;
    wire [3:0] Q2;
    wire [3:0] Q3;
    wire [3:0] Q4;
    wire [3:0] Q5;
    wire [3:0] Q6;
    wire [3:0] Q7;

    wire [7:0]cout;
    
    BCD_counter U1(CLK1,rst,1,Q0[3:0],cout[0]);
    BCD_counter U2(CLK1,rst,cout[0],Q1[3:0],cout[1]);
    BCD_counter U3(CLK1,rst,cout[1],Q2[3:0],cout[2]);
    BCD_counter U4(CLK1,rst,cout[2],Q3[3:0],cout[3]);
    BCD_counter U5(CLK1,rst,cout[3],Q4[3:0],cout[4]);
    BCD_counter U6(CLK1,rst,cout[4],Q5[3:0],cout[5]);
    BCD_counter U7(CLK1,rst,cout[5],Q6[3:0],cout[6]);
    BCD_counter U8(CLK1,rst,cout[6],Q7[3:0],cout[7]);
    
    wire [0:3]result;
    MUX8_1 M1(Q0[0],Q1[0],Q2[0],Q3[0],Q4[0],Q5[0],Q6[0],Q7[0],CLK_A,CLK_B,CLK_C,result[0]);
    MUX8_1 M2(Q0[1],Q1[1],Q2[1],Q3[1],Q4[1],Q5[1],Q6[1],Q7[1],CLK_A,CLK_B,CLK_C,result[1]);
    MUX8_1 M3(Q0[2],Q1[2],Q2[2],Q3[2],Q4[2],Q5[2],Q6[2],Q7[2],CLK_A,CLK_B,CLK_C,result[2]);
    MUX8_1 M4(Q0[3],Q1[3],Q2[3],Q3[3],Q4[3],Q5[3],Q6[3],Q7[3],CLK_A,CLK_B,CLK_C,result[3]);
    
    DEC3_8(CLK_A,CLK_B,CLK_C,seg_sel);
    
    DEC_BCD_7 D6(result[0],result[1],result[2],result[3],oDisplay[0],oDisplay[1],oDisplay[2],oDisplay[3],oDisplay[4],oDisplay[5],oDisplay[6]);
    
    assign L0=result[0];
    assign L1=result[1];
    
endmodule

module DEC_BCD_7(
input A,
input B,
input C,
input D,
output reg OA,
output reg OB,
output reg OC,
output reg OD,
output reg OE,
output reg OF,
output reg OG
);

always @(A,B,C,D)
    begin
        case({A,B,C,D})
            4'b0000: {OA,OB,OC,OD,OE,OF,OG}=7'b1000000;
            4'b0001: {OA,OB,OC,OD,OE,OF,OG}=7'b1111001;
            4'b0010: {OA,OB,OC,OD,OE,OF,OG}=7'b0100100;
            4'b0011: {OA,OB,OC,OD,OE,OF,OG}=7'b0110000;
            4'b0100: {OA,OB,OC,OD,OE,OF,OG}=7'b0011001;
            4'b0101: {OA,OB,OC,OD,OE,OF,OG}=7'b0010010;
            4'b0110: {OA,OB,OC,OD,OE,OF,OG}=7'b0000010;
            4'b0111: {OA,OB,OC,OD,OE,OF,OG}=7'b1111000;
            4'b1000: {OA,OB,OC,OD,OE,OF,OG}=7'b0000000;
            4'b1001: {OA,OB,OC,OD,OE,OF,OG}=7'b0010000;
            default: {OA,OB,OC,OD,OE,OF,OG}=7'b1111111;
        endcase
     end

endmodule

module  DEC3_8(
input  A,
input  B,
input  C,
output reg [7:0]result
);

always @(A,B,C)
    begin
        case({A,B,C})
            3'b000: result=8'b00000001;
            3'b001: result=8'b00000010;
            3'b010: result=8'b00000100;
            3'b011: result=8'b00001000;
            3'b100: result=8'b00010000;
            3'b101: result=8'b00100000;
            3'b110: result=8'b01000000;
            3'b111: result=8'b10000000;
        endcase
    end
    
endmodule
            

module BCD_counter(
 input clk, 
 input rst_n,
 input cin,
 output [3:0] q ,
 output   cout
);
 reg [3:0] cnt;
 always@(posedge clk or negedge rst_n)
  if(!rst_n)
   cnt <= 4'd0;
  else if(cin == 1)begin
   if(cnt == 4'd9)
    cnt <= 4'd0;
   else
    cnt <= cnt + 4'd1;
  end else
   cnt <= cnt;
   
    assign cout = (cin ==1 && cnt == 4'd9)? 1'b1:1'b0; 
    assign q = cnt;

endmodule


module MUX8_1(
input D0,
input D1,
input D2,
input D3,
input D4,
input D5,
input D6,
input D7,
input A,
input B,
input C,
output reg result
);

    always@(*)
        begin
            case({A,B,C})
                3'b000:result=D0;
                3'b001:result=D1;
                3'b010:result=D2;
                3'b011:result=D3;
                3'b100:result=D4;
                3'b101:result=D5;
                3'b110:result=D6;
                3'b111:result=D7;
            endcase
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