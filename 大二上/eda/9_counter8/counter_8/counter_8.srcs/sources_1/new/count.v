`timescale 1ns / 1ps

module counter8(
    input CLK,
    input rst_n,
    output [2:0] oQ,
    output [6:0] oDisplay
    );
    wire Q0,Q1,Q2;//JK�����������
    wire [3:0] display_in;  //Jk������������
    reg [24:0] cnt;    //��Ƶ����Ҫ��24λ2������
    wire f1;     //���潵Ƶ֮���ʱ��
    
    //��ʱ�ӽ��н�Ƶ��ÿ��һ��ʱ���ź�cnt�ͼ�һ��rst_n����λָ��
    always@(posedge CLK or negedge rst_n)
        if(rst_n)
            cnt<=0;
        else
            cnt<=cnt+1;
    assign f1=cnt[24];//f1ѡȡ���������λ�Դﵽ��Ƶ�Ĺ���
    
    //����JK����������״̬�ĸı�
    JK U1(f1,1,1,rst_n,Q0);
    JK U2(f1,Q0,Q0,rst_n,Q1);
    JK U3(f1,Q0&&Q1,Q0&&Q1,rst_n,Q2);
    
    //���������ó���״̬�������ֹܵ����룬ģ8�������λ��1,
    assign display_in[0]=Q0;
    assign display_in[1]=Q1;
    assign display_in[2]=Q2;
    assign display_in[3]=1'b0;
    assign oQ=display_in;
    
    display7 D1(.iData(display_in), .oData(oDisplay));
    
endmodule


//JK������
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
