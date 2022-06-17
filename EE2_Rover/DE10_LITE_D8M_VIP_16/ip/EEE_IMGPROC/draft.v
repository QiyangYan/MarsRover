/*
reg [10:0] pink_x_min, pink_y_min, pink_x_max, pink_y_max;
always@(posedge clk) begin
	if (pink_detect & in_valid) begin	//Update bounds when the pixel is pink
		if (x < pink_x_min) pink_x_min <= x;
		if (x > pink_x_max) pink_x_max <= x;
		if (y < pink_y_min) pink_y_min <= y;
		pink_y_max <= y;
	end
	if (sop & in_valid) begin	//Reset bounds on start of packet
		pink_x_min <= IMAGE_W-11'h1;
		pink_x_max <= 0;
		pink_y_min <= IMAGE_H-11'h1;
		pink_y_max <= 0;
	end
end*/