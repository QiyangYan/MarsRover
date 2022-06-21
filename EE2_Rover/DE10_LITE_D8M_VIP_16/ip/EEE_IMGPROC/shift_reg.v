module shift_reg_640(
    input d,
    input clk,
    input en,
    input rst,
    output [639:0] out
);
always@(posedge clk)begin
    if(!rst)begin
        out<=0;
    end
    else begin
        if(en) begin
            out <= {out[638:0],d};
        end
        else begin
            out <= out;
        end
    end
end

endmodule

module shift_reg_3(
    input d,
    input clk,
    input en,
    input rst,
    output [2:0] out
);
always@(posedge clk)begin
    if(!rst)begin
        out<=0;
    end
    else begin
        if(en) begin
            out <= {out[1:0],d};
        end
        else begin
            out <= out;
        end
    end
end

endmodule