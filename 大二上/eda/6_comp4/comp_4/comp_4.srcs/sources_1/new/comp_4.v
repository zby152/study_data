`timescale 1ns / 1ps
module comp_4(
input [3:0] iData_a,
input [3:0] iData_b,
input [2:0] iData,
output [2:0] oData
    );
    reg eq,gt,lt;
    assign oData[2]=gt;
    assign oData[1]=lt;
    assign oData[0]=eq;
    
    always@(*)
    begin 
        eq=(iData_a==iData_b)?1:0;
        gt=(iData_a>iData_b)?1:0;
        lt=(iData_a<iData_b)?1:0;
        
        if(eq)
        begin
            eq=0;
            case(iData)
                3'b100:gt=1;
                3'b010:lt=1;
                3'b001:eq=1;
                default:eq=1;
            endcase
        end
    end
endmodule
