module EEE_IMGPROC(
	// global clock & reset
	clk,
	reset_n,
	
	// mm slave
	s_chipselect,
	s_read,
	s_write,
	s_readdata,
	s_writedata,
	s_address,

	// stream sink
	sink_data,
	sink_valid,
	sink_ready,
	sink_sop,
	sink_eop,
	
	// streaming source
	source_data,
	source_valid,
	source_ready,
	source_sop,
	source_eop,
	
	// conduit
	mode
	
);


// global clock & reset
input	clk;
input	reset_n;

// mm slave
input							s_chipselect;
input							s_read;
input							s_write;
output	reg	[31:0]	s_readdata;
input	[31:0]				s_writedata;
input	[2:0]					s_address;


// streaming sink
input	[23:0]            	sink_data;
input								sink_valid;
output							sink_ready;
input								sink_sop;
input								sink_eop;

// streaming source
output	[23:0]			  	   source_data;
output								source_valid;
input									source_ready;
output								source_sop;
output								source_eop;

// conduit export
input                         mode;

////////////////////////////////////////////////////////////////////////
//
parameter IMAGE_W = 11'd640;
parameter IMAGE_H = 11'd480;
parameter MESSAGE_BUF_MAX = 256;
parameter MSG_INTERVAL = 6;
parameter BB_COL_DEFAULT = 24'h00ff00;


wire [7:0]   red, green, blue, grey, greier;
wire [7:0]   red_out, green_out, blue_out;

wire         sop, eop, in_valid, out_ready;
////////////////////////////////////////////////////////////////////////

// Detect areas
wire red_detect;
wire blue_detect;
wire yellow_detect;
wire green_detect;
wire d_green_detect;
wire pink_detect;
assign red_detect = (hsv_h >= 8'd0) && (hsv_h <= 8'd20) && (hsv_s >= 8'd135) && (hsv_s <= 8'd255) && (hsv_v >= 8'd120) && (hsv_v <= 8'd185);
assign pink_detect =  (hsv_h >= 8'd0) && (hsv_h <= 8'd13) && (hsv_s >= 8'd125) && (hsv_s <= 8'd185) && (hsv_v >= 8'd175) && (hsv_v <= 8'd255);
assign blue_detect = (hsv_h >= 8'd180) && (hsv_h <= 8'd240) && (hsv_s >= 8'd85) && (hsv_s <= 8'd180) && (hsv_v >= 8'd25) && (hsv_v <= 8'd110);
assign yellow_detect =  (hsv_h >= 8'd50) && (hsv_h <= 8'd70) && (hsv_s >= 8'd125) && (hsv_s <= 8'd225) && (hsv_v >= 8'd225) && (hsv_v <= 8'd255);
assign green_detect =  (hsv_h >= 8'd90) && (hsv_h <= 8'd120) && (hsv_s >= 8'd110) && (hsv_s <= 8'd180) && (hsv_v >= 8'd135) && (hsv_v <= 8'd255);
assign d_green_detect = (hsv_h >= 8'd100) && (hsv_h <= 8'd170) && (hsv_s >= 8'd80) && (hsv_s <= 8'd130) && (hsv_v >= 8'd40) && (hsv_v <= 8'd120);
// Find boundary of cursor box

// Highlight detected areasxxd                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        xxcggg                                                                                                                                                                                                                                                                                                                                                                                                                            b
wire [23:0] red_high;
assign grey = green[7:1] + red[7:2] + blue[7:2]; //Grey = green/2 + red/4 + blue/4
assign greier = green[7:2] + red[7:3] + blue[7:4]; //Grey = green/2 + red/4 + blue/4
assign red_high  =  red_detect ? {8'hff, 8'h0, 8'h0} :
					blue_detect ? {8'h0, 8'h0, 8'hff} : 
					yellow_detect ? {8'hff, 8'hff, 8'h0} :
					green_detect ? {8'h0, 8'hff, 8'h0} :
					d_green_detect ? {8'h0, 8'hff, 8'hff} :
					pink_detect ? {8'hff, 8'h40, 8'hc0} : 
					{grey, grey, grey};

// Show bounding box
wire [23:0] new_image;

wire red_active;
wire green_active;
wire blue_active;
wire yellow_active;
wire d_green_active;
wire pink_active;
parameter red_col = 24'hff0000;
parameter blue_col = 24'h0000ff;
parameter yellow_col = 24'hffff00;
parameter green_col = 24'h00ff00;
parameter d_green_col = 24'h00ffff;//teal
parameter pink_col = 24'hff40c0;
assign red_active = (x == red_left) | (x == red_right);// | (y == red_top) | (y == red_bottom);
assign blue_active =  (x == blue_left) | (x == blue_right);// | (y == blue_top) | (y == blue_bottom);
assign yellow_active = (x == yellow_left) | (x == yellow_right);// | (y == yellow_top) | (y == yellow_bottom);
assign green_active =  (x == green_left) | (x == green_right);// | (y == green_top) | (y == green_bottom);
assign d_green_active =  (x == d_green_left) | (x == d_green_right);// | (y == d_green_top) | (y == d_green_bottom);
assign pink_active =  (x == pink_left) | (x == pink_right);// | (y == pink_top) | (y == pink_bottom);
wire force_w_line = (y == 11'd70) | (y == 11'd69);
wire force_r_line = (y == 11'd68) | (y == 11'd67);
wire force_b_line = (y == 11'd65) | (y == 11'd64);
assign new_image = force_w_line ? 24'hffffff :
				   force_r_line ? red_col :
				   force_b_line ? blue_col :
				   red_active ? red_col :
				   blue_active ? blue_col :
				   yellow_active ? yellow_col :
				   green_active? green_col : 
				   d_green_active ? d_green_col:
				   pink_active ? pink_col:
				   red_high;

// Switch output pixels depending on mode switch
// Don't modify the start-of-packet word - it's a packet discriptor
// Don't modify data in non-video packets
assign {red_out, green_out, blue_out} = (mode & ~sop & packet_video) ? new_image : {red,green,blue};

//Count valid pixels to tget the image coordinates. Reset and detect packet type on Start of Packet.
reg [10:0] x, y;
reg packet_video;
always@(posedge clk) begin
	if (sop) begin
		x <= 11'h0;
		y <= 11'h0;
		packet_video <= (blue[3:0] == 3'h0);
	end
	else if (in_valid) begin
		if (x == IMAGE_W-1) begin
			x <= 11'h0;
			y <= y + 11'h1;
		end
		else begin
			x <= x + 11'h1;
		end
	end
end

//Find first and last red pixels
reg [10:0] red_x_min, red_y_min, red_x_max, red_y_max;
reg red_detect_1, red_detect_2,red_detect_3, red_detect_4;
always@(posedge clk) begin
	red_detect_1 <= red_detect;
	red_detect_2 <= red_detect_1;
	red_detect_3 <= red_detect_2;
	red_detect_4 <= red_detect_3;
	if (((red_detect && red_detect_1 && red_detect_2 && red_detect_3 && red_detect_4) & in_valid) && y > 11'd70) begin	//Update bounds when the pixel is red
		if (x < red_x_min) red_x_min <= x;
		if (x > red_x_max) red_x_max <= x;
		if (y < red_y_min) red_y_min <= y;
		red_y_max <= y;
	end
	if (sop & in_valid) begin	//Reset bounds on start of packet
		red_x_min <= IMAGE_W-11'h1;
		red_x_max <= 0;
		red_y_min <= IMAGE_H-11'h1;
		red_y_max <= 0;
	end
end

reg [10:0] pink_x_min, pink_y_min, pink_x_max, pink_y_max;
reg pink_detect_1, pink_detect_2, pink_detect_3, pink_detect_4;
always@(posedge clk) begin
	pink_detect_1 <= pink_detect;
	pink_detect_2 <= pink_detect_1;
	pink_detect_3 <= pink_detect_2;
	pink_detect_4 <= pink_detect_3;
	if (((pink_detect && pink_detect_1 && pink_detect_2 && pink_detect_3 && pink_detect_4) & in_valid) && y > 11'd70) begin	//Update bounds when the pixel is pink
		if (x < pink_x_min) pink_x_min <= x;
		if (x > pink_x_max) pink_x_max <= x;
		if (y < pink_y_min) pink_y_min <= y;
		pink_y_max <= y;
	end
	if (sop & in_valid) begin	//Reset bounds on start of packet
		pink_x_min <= IMAGE_W-11'h1;
		pink_x_max <= 0;
		pink_y_min <= 0;
		pink_y_max <= 0;
	end
end

reg [10:0] yellow_x_min, yellow_y_min, yellow_x_max, yellow_y_max;
reg yellow_detect_1, yellow_detect_2, yellow_detect_3, yellow_detect_4;
always@(posedge clk) begin
	yellow_detect_1 <= yellow_detect;
	yellow_detect_2 <= yellow_detect_1;
	yellow_detect_3 <= yellow_detect_2;
	yellow_detect_4 <= yellow_detect_3;
	if (((yellow_detect && yellow_detect_1 && yellow_detect_2 &&  yellow_detect_3 && yellow_detect_4) & in_valid) && y > 11'd70) begin	//Update bounds when the pixel is pink
		if (x < yellow_x_min) yellow_x_min <= x;
		if (x > yellow_x_max) yellow_x_max <= x;
		if (y < yellow_y_min) yellow_y_min <= y;
		yellow_y_max <= y;
	end
	if (sop & in_valid) begin	//Reset bounds on start of packet
		yellow_x_min <= IMAGE_W-11'h1;
		yellow_x_max <= 0;
		yellow_y_min <= 0;
		yellow_y_max <= 0;
	end
end


reg [10:0] blue_x_min, blue_y_min, blue_x_max, blue_y_max;
reg blue_detect_1, blue_detect_2, blue_detect_3, blue_detect_4;
always@(posedge clk) begin
	blue_detect_1 <= blue_detect;
	blue_detect_2 <= blue_detect_1;
	blue_detect_3 <= blue_detect_2;
	blue_detect_4 <= blue_detect_3;
	if (((blue_detect && blue_detect_1 && blue_detect_2 && blue_detect_3 && blue_detect_4) & in_valid) && y > 11'd70) begin	//Update bounds when the pixel is pink
		if (x < blue_x_min) blue_x_min <= x;
		if (x > blue_x_max) blue_x_max <= x;
		if (y < blue_y_min) blue_y_min <= y;
		blue_y_max <= y;
	end
	if (sop & in_valid) begin	//Reset bounds on start of packet
		blue_x_min <= IMAGE_W-11'h1;
		blue_x_max <= 0;
		blue_y_min <= 0;
		blue_y_max <= 0;
	end
end


reg [10:0] green_x_min, green_y_min, green_x_max, green_y_max;
reg green_detect_1, green_detect_2, green_detect_3, green_detect_4;
always@(posedge clk) begin
	green_detect_1 <= green_detect;
	green_detect_2 <= green_detect_1;
	green_detect_3 <= green_detect_2;
	green_detect_4 <= green_detect_3;
	if (((green_detect && green_detect_1 && green_detect_2 && green_detect_3 && green_detect_4) & in_valid) && y > 11'd70) begin	//Update bounds when the pixel is pink
		if (x < green_x_min) green_x_min <= x;
		if (x > green_x_max) green_x_max <= x;
		if (y < green_y_min) green_y_min <= y;
		green_y_max <= y;
	end
	if (sop & in_valid) begin	//Reset bounds on start of packet
		green_x_min <= IMAGE_W-11'h1;
		green_x_max <= 0;
		green_y_min <= 0;
		green_y_max <= 0;
	end
end


reg [10:0] d_green_x_min, d_green_y_min, d_green_x_max, d_green_y_max;
reg d_green_detect_1, d_green_detect_2, d_green_detect_3, d_green_detect_4;
always@(posedge clk) begin
	d_green_detect_1 <= d_green_detect;
	d_green_detect_2 <= d_green_detect_1;
	d_green_detect_3 <= d_green_detect_2;
	d_green_detect_4 <= d_green_detect_3;
	if (((d_green_detect && d_green_detect_1 && d_green_detect_2 && d_green_detect_3 && d_green_detect_4) & in_valid) && y > 11'd70) begin	//Update bounds when the pixel is pink
		if (x < d_green_x_min) d_green_x_min <= x;
		if (x > d_green_x_max) d_green_x_max <= x;
		if (y < d_green_y_min) d_green_y_min <= y;
		d_green_y_max <= y;
	end
	if (sop & in_valid) begin	//Reset bounds on start of packet
		d_green_x_min <= IMAGE_W-11'h1;
		d_green_x_max <= 0;
		d_green_y_min <= 0;
		d_green_y_max <= 0;
	end
end

//Process bounding box at the end of the frame.
reg [2:0] msg_state;
reg [10:0] red_left, red_right, red_top, red_bottom;
reg [10:0] green_left, green_right, green_top, green_bottom;
reg [10:0] yellow_left, yellow_right, yellow_top, yellow_bottom;
reg [10:0] blue_left, blue_right, blue_top, blue_bottom;
reg [10:0] d_green_left, d_green_right, d_green_top, d_green_bottom;
reg [10:0] pink_left, pink_right, pink_top, pink_bottom;
reg [7:0] frame_count;
always@(posedge clk) begin
	if (eop & in_valid & packet_video) begin  //Ignore non-video packets
		
		//Latch edges for display overlay on next frame
		red_left <= red_x_min;
		red_right <= red_x_max;
		red_top <= red_y_min;
		red_bottom <= red_y_max;

		// blue_left <= blue_x_min;
		// blue_right <= blue_x_max;
		// blue_top <= blue_y_min;
		// blue_bottom <= blue_y_max;

		// yellow_left <= yellow_x_min;
		// yellow_right <= yellow_x_max;
		// yellow_top <= yellow_y_min;
		// yellow_bottom <= yellow_y_max;

		// green_left <= green_x_min;
		// green_right <= green_x_max;
		// green_top <= green_y_min;
		// green_bottom <= green_y_max;
		
		// d_green_left <= d_green_x_min;
		// d_green_right <= d_green_x_max;
		// d_green_top <= d_green_y_min;
		// d_green_bottom <= d_green_y_max;

		// pink_left <= pink_x_min;
		// pink_right <= pink_x_max;
		// pink_top <= pink_y_min;
		// pink_bottom <= pink_y_max;
		//Start message writer FSM once every MSG_INTERVAL frames, if there is room in the FIFO
		frame_count <= frame_count - 1;
		
		if (frame_count == 0 && msg_buf_size < MESSAGE_BUF_MAX - 3) begin
			msg_state <= 3'b001;
			frame_count <= MSG_INTERVAL-1;
		end
	end
	
	//Cycle through message writer states once started
	if (msg_state != 3'b000) msg_state <= msg_state + 3'b001;

end
	
//Generate output messages for CPU
reg [31:0] msg_buf_in; 
wire [31:0] msg_buf_out;
reg msg_buf_wr;
wire msg_buf_rd, msg_buf_flush;
wire [7:0] msg_buf_size;
wire msg_buf_empty;

`define RED_BOX_MSG_ID "RBB"

wire [10:0] ini_red_size, red_mid, red_tmp;
wire [10:0] ini_blue_size, blue_mid, blue_tmp;
wire [10:0] ini_yellow_size, yellow_mid, yellow_tmp;
wire [10:0] ini_green_size, green_mid, green_tmp;
wire [10:0] ini_pink_size, pink_mid,pink_tmp;
wire [10:0] ini_d_green_size, d_green_mid,d_green_tmp;
assign ini_red_size = red_x_max - red_x_min;
assign ini_blue_size = blue_x_max - blue_x_min;
assign ini_yellow_size = yellow_x_max - yellow_x_min;
assign ini_green_size = green_x_max - green_x_min;
assign ini_d_green_size = d_green_x_max - d_green_x_min;
assign ini_pink_size = pink_x_max - pink_x_min;
assign red_tmp = (red_x_max + red_x_min);
assign blue_tmp = (blue_x_max + blue_x_min);
assign yellow_tmp = (yellow_x_max + yellow_x_min);
assign green_tmp = (green_x_max + green_x_min);
assign d_green_tmp = (d_green_x_max + d_green_x_min);
assign pink_tmp = (pink_x_max + pink_x_min);
assign red_mid = red_tmp[10:1];
assign blue_mid = blue_tmp[10:1];
assign yellow_mid = yellow_tmp[10:1];
assign green_mid = green_tmp[10:1];
assign d_green_mid = d_green_tmp[10:1];
assign pink_mid = pink_tmp[10:1];

always@(*) begin	//Write words to FIFO as state machine advances
	case(msg_state)
		3'b000: begin
			msg_buf_in = 32'b0;
			msg_buf_wr = 1'b0;
		end
		3'b001: begin
			msg_buf_in = `RED_BOX_MSG_ID;	//Message ID
			msg_buf_wr = 1'b1;
		end
		3'b010: begin
			msg_buf_in = {"R", 1'b0, ini_red_size, 1'b0, red_mid};	//Top left coordinate
			msg_buf_wr = 1'b1;
		end
		3'b011: begin
			msg_buf_in = {"B", 1'b0, ini_blue_size, 1'b0, blue_mid}; //Bottom right coordinate
			msg_buf_wr = 1'b1;
		end
		3'b100: begin
			msg_buf_in = {"Y", 1'b0, ini_yellow_size, 1'b0, yellow_mid};	//Top left coordinate
			msg_buf_wr = 1'b1;
		end
		3'b101: begin
			msg_buf_in = {"G", 1'b0, ini_green_size, 1'b0, green_mid}; //Bottom right coordinate
			msg_buf_wr = 1'b1;
		end
		3'b110: begin
			msg_buf_in = {"D", 1'b0, ini_d_green_size, 1'b0, d_green_mid}; //Bottom right coordinate
			msg_buf_wr = 1'b1;
		end
		3'b111: begin
			msg_buf_in = {"P", 1'b0, ini_pink_size, 1'b0, pink_mid}; //Bottom right coordinate
			msg_buf_wr = 1'b1;
		end
	endcase
end

wire [7:0]hsv_h;
wire [7:0]hsv_s;
wire [7:0]hsv_v;

rgb2hsv rgb2hsv(
	.clk(clk),
	.rgb_r(red),
	.rgb_g(green),
	.rgb_b(blue),
	.hsv_h(hsv_h),
	.hsv_s(hsv_s),
	.hsv_v(hsv_v)
);

//Output message FIFO
MSG_FIFO	MSG_FIFO_inst (
	.clock (clk),
	.data (msg_buf_in),
	.rdreq (msg_buf_rd),
	.sclr (~reset_n | msg_buf_flush),
	.wrreq (msg_buf_wr),
	.q (msg_buf_out),
	.usedw (msg_buf_size),
	.empty (msg_buf_empty)
	);


//Streaming registers to buffer video signal
STREAM_REG #(.DATA_WIDTH(26)) in_reg (
	.clk(clk),
	.rst_n(reset_n),
	.ready_out(sink_ready),
	.valid_out(in_valid),
	.data_out({red,green,blue,sop,eop}),
	.ready_in(out_ready),
	.valid_in(sink_valid),
	.data_in({sink_data,sink_sop,sink_eop})
);

STREAM_REG #(.DATA_WIDTH(26)) out_reg (
	.clk(clk),
	.rst_n(reset_n),
	.ready_out(out_ready),
	.valid_out(source_valid),
	.data_out({source_data,source_sop,source_eop}),
	.ready_in(source_ready),
	.valid_in(in_valid),
	.data_in({red_out, green_out, blue_out, sop, eop})
);


/////////////////////////////////
/// Memory-mapped port		 /////
/////////////////////////////////

// Addresses
`define REG_STATUS    			0
`define READ_MSG    				1
`define READ_ID    				2
`define REG_BBCOL					3

//Status register bits
// 31:16 - unimplemented
// 15:8 - number of words in message buffer (read only)
// 7:5 - unused
// 4 - flush message buffer (write only - read as 0)
// 3:0 - unused


// Process write

reg  [7:0]   reg_status;
reg	[23:0]	bb_col;

always @ (posedge clk)
begin
	if (~reset_n)
	begin
		reg_status <= 8'b0;
		bb_col <= BB_COL_DEFAULT;
	end
	else begin
		if(s_chipselect & s_write) begin
		   if      (s_address == `REG_STATUS)	reg_status <= s_writedata[7:0];
		   if      (s_address == `REG_BBCOL)	bb_col <= s_writedata[23:0];
		end
	end
end


//Flush the message buffer if 1 is written to status register bit 4
assign msg_buf_flush = (s_chipselect & s_write & (s_address == `REG_STATUS) & s_writedata[4]);


// Process reads
reg read_d; //Store the read signal for correct updating of the message buffer

// Copy the requested word to the output port when there is a read.
always @ (posedge clk)
begin
   if (~reset_n) begin
	   s_readdata <= {32'b0};
		read_d <= 1'b0;
	end
	
	else if (s_chipselect & s_read) begin
		if   (s_address == `REG_STATUS) s_readdata <= {16'b0,msg_buf_size,reg_status};
		if   (s_address == `READ_MSG) s_readdata <= {msg_buf_out};
		if   (s_address == `READ_ID) s_readdata <= 32'h1234EEE2;
		if   (s_address == `REG_BBCOL) s_readdata <= {8'h0, bb_col};
	end
	
	read_d <= s_read;
end

//Fetch next word from message buffer after read from READ_MSG
assign msg_buf_rd = s_chipselect & s_read & ~read_d & ~msg_buf_empty & (s_address == `READ_MSG);
						


endmodule

