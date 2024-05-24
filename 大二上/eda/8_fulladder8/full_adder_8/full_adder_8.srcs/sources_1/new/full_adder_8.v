`timescale 1ns / 1ps

module full_adder(
input iA,
input iB,
input iC,
output oS,
output oC
);
assign {oC,oS}=iA+iB+iC;
endmodule


module full_adder_8(
input [7:0] iData_a,
input [7:0] iData_b,
input iC,
output [7:0] oData,
output oC
);

wire [7:0]temp;
    full_adder U1(iData_a[0],iData_b[0],iC,oData[0],temp[0]);
    full_adder U2(iData_a[1],iData_b[1],temp[0],oData[1],temp[1]);
    full_adder U3(iData_a[2],iData_b[2],temp[1],oData[2],temp[2]);
    full_adder U4(iData_a[3],iData_b[3],temp[2],oData[3],temp[3]);
    full_adder U5(iData_a[4],iData_b[4],temp[3],oData[4],temp[4]);
    full_adder U6(iData_a[5],iData_b[5],temp[4],oData[5],temp[5]);
    full_adder U7(iData_a[6],iData_b[6],temp[5],oData[6],temp[6]);
    full_adder U8(iData_a[7],iData_b[7],temp[6],oData[7],oC);

endmodule
