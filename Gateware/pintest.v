module pintest 
(
	input wire			CLK100_P,
	output wire[8:0]	D2IO_n,
	output wire[8:0]	D2IO_p,
	output wire[4:0]	D2I_n,
	output wire[4:0]	D2I_p,
	output wire[5:0]	D3IO_n,
	input wire			TestClock,
	output wire			D3IO_n7, //Since we cannot split an array and testclock used D3IO_n[6], we write this like this to still know which pin it is
	output wire[7:0]	D3IO_p,
	output wire[7:0]	D3I_n,
	output wire[7:0]	D3I_p,
	output wire[7:0]	D6IO_n,
	output wire[7:0]	D6IO_p,
	output wire[7:0]	D6I_n,
	output wire[7:0]	D6I_p,
	output wire[3:0]	LED,
	output wire[7:0]	S0,
	output wire[11:0]	S1,
	output wire[6:0]	S8,
	output wire[0:0]	S6
);

localparam PINCOUNT = 128;
localparam PINMAX = PINCOUNT - 1;

reg [PINMAX:0] shiftreg;
reg [PINMAX:0] shiftreg_r;
wire clk;
reg [5:0] porcount = 6'b0;
wire por_reset;
wire reset;
reg last_testclk;
reg [2:0] sync_testclk = 'b0;

always @(posedge CLK100_P)
begin
	if (~&porcount)
	begin
		porcount <= porcount + 1'b1;
	end
end
assign por_reset = ~&porcount;

//CLKDIVF # (.DIV("2.0") ) div ( .RST(por_reset), .CLKI(CLK100_P), .ALIGNWD(1'b0), .CDIVX(clk));
assign clk = CLK100_P;

//reset the whole system if testclock is 0 for more than 2 seconds
reg[27:0] resetcount;
always @(posedge clk or posedge por_reset)
begin
	if (por_reset) begin
		resetcount <= 'b0;
		sync_testclk <= 'b0;
		shiftreg <= 'b0;
	end else begin
		shiftreg <= shiftreg_r;
		sync_testclk <= {TestClock, sync_testclk[2:1]};
		if (sync_testclk[0] == 1'b1 ) begin
			resetcount <= 'b0;
		end else begin
			if (~&resetcount) begin
				resetcount <= resetcount + 1'b1;
			end 
		end
	end
end

assign reset = por_reset | &resetcount;

reg[26:0] ledCount;
always @(posedge clk)
begin
	ledCount <= ledCount + 1'b1;
end

reg flip;
assign LED[0] = por_reset;
assign LED[1] = ledCount[26];
assign LED[2] = ~reset;
assign LED[3] = flip;

//shift register
always @(posedge clk or posedge reset)
begin
	if (reset) begin
		shiftreg_r[PINMAX:1] <= {PINMAX{1'b0}};
		shiftreg_r[0] <= 1'b1;
		flip <= 1'b0;
	end else begin
		last_testclk <= sync_testclk[0];
		if (sync_testclk[0] == 1'b1 && last_testclk == 1'b0) begin
			shiftreg_r <={shiftreg_r[PINMAX-1:0], shiftreg_r[PINMAX]};
			flip <= ~flip;
		end
	end
end

//long list of pin assignments

//Test 0
assign S0[5]    = shiftreg[0]; //0
assign S1[3]    = shiftreg[1]; //1
assign S8[6]    = shiftreg[2]; //2
assign D6I_n[0]    = shiftreg[3]; //3
assign S1[4]    = shiftreg[4]; //4
assign S8[4]    = shiftreg[5]; //5
assign S6[0]    = shiftreg[6]; //6
assign D6I_p[3]    = shiftreg[7]; //7
assign D6I_p[2]    = shiftreg[8]; //8
assign D6I_p[5]    = shiftreg[9]; //9
assign D6I_p[0]    = shiftreg[10]; //10
assign D6I_n[3]    = shiftreg[11]; //11
assign D6I_n[5]    = shiftreg[12]; //12
assign D6I_n[2]    = shiftreg[13]; //13
assign D6I_n[1]    = shiftreg[14]; //14
assign D6I_p[1]    = shiftreg[15]; //15

//Test 1
assign S8[3]    = shiftreg[16]; //0
assign S1[5]    = shiftreg[17]; //1
assign S1[9]    = shiftreg[18]; //2
assign S1[0]    = shiftreg[19]; //3
assign S1[11]    = shiftreg[20]; //4
assign S8[5]    = shiftreg[21]; //5
assign S8[1]    = shiftreg[22]; //6
//assign GND    = shiftreg[23]; //7
assign S0[7]    = shiftreg[24]; //8
assign S0[2]    = shiftreg[25]; //9
assign S0[0]    = shiftreg[26]; //10
assign S1[7]    = shiftreg[27]; //11
assign S0[1]    = shiftreg[28]; //12
assign S0[4]    = shiftreg[29]; //13
assign S0[6]    = shiftreg[30]; //14
assign S0[3]    = shiftreg[31]; //15

//Test 2
assign D6IO_n[6]    = shiftreg[32]; //0
assign D6IO_p[7]    = shiftreg[33]; //1
assign D6IO_n[7]    = shiftreg[34]; //2
assign D6I_n[6]    = shiftreg[35]; //3
assign D6I_p[6]    = shiftreg[36]; //4
assign D6I_p[7]    = shiftreg[37]; //5
assign D6I_p[4]    = shiftreg[38]; //6
assign D6I_n[7]    = shiftreg[39]; //7
assign S1[1]    = shiftreg[40]; //8
assign S1[2]    = shiftreg[41]; //9
assign D6I_n[4]    = shiftreg[42]; //10
assign S1[8]    = shiftreg[43]; //11
assign S8[0]    = shiftreg[44]; //12
assign S1[6]    = shiftreg[45]; //13
assign S1[10]    = shiftreg[46]; //14
assign S8[2]    = shiftreg[47]; //15

//Test 3
//assign GND    = shiftreg[48]; //0
//assign GND    = shiftreg[49]; //1
assign D6IO_n[3]    = shiftreg[50]; //2
assign D6IO_p[3]    = shiftreg[51]; //3
assign D6IO_p[0]    = shiftreg[52]; //4
assign D6IO_n[0]    = shiftreg[53]; //5
assign D6IO_p[1]    = shiftreg[54]; //6
assign D6IO_n[1]    = shiftreg[55]; //7
assign D6IO_p[4]    = shiftreg[56]; //8
assign D6IO_n[5]    = shiftreg[57]; //9
assign D6IO_p[5]    = shiftreg[58]; //10
//assign GND    = shiftreg[59]; //11
assign D6IO_n[4]    = shiftreg[60]; //12
assign D6IO_p[2]    = shiftreg[61]; //13
assign D6IO_n[2]    = shiftreg[62]; //14
assign D6IO_p[6]    = shiftreg[63]; //15

//Test 4
assign D3IO_n[0]    = shiftreg[64]; //0
assign D3IO_p[0]    = shiftreg[65]; //1
assign D3I_n[3]    = shiftreg[66]; //2
assign D3I_p[3]    = shiftreg[67]; //3
assign D3I_n[4]    = shiftreg[68]; //4
assign D3I_p[4]    = shiftreg[69]; //5
assign D2IO_p[7]    = shiftreg[70]; //6
assign D2IO_n[7]    = shiftreg[71]; //7
assign D2IO_n[6]    = shiftreg[72]; //8
assign D2IO_p[6]    = shiftreg[73]; //9
assign D2IO_n[4]    = shiftreg[74]; //10
assign D2IO_p[4]    = shiftreg[75]; //11
assign D2I_n[1]    = shiftreg[76]; //12
assign D2I_p[1]    = shiftreg[77]; //13
assign D2I_n[0]    = shiftreg[78]; //14
assign D2I_p[0]    = shiftreg[79]; //15

//Test 5
assign D3IO_p[6]    = shiftreg[80]; //0
assign D3IO_n7    = shiftreg[81]; //1
assign D3IO_n[2]    = shiftreg[82]; //2
assign D3IO_p[2]    = shiftreg[83]; //3
assign D2IO_n[8]    = shiftreg[84]; //4
assign D2IO_p[8]    = shiftreg[85]; //5
assign D2IO_n[1]    = shiftreg[86]; //6
assign D2IO_n[2]    = shiftreg[87]; //7
assign D2IO_p[2]    = shiftreg[88]; //8
assign D2IO_n[0]    = shiftreg[89]; //9
assign D2IO_p[1]    = shiftreg[90]; //10
assign D3IO_n[4]    = shiftreg[91]; //11
assign D2IO_p[0]    = shiftreg[92]; //12
assign D3IO_p[4]    = shiftreg[93]; //13
//assign GND    = shiftreg[94]; //14
//assign GND    = shiftreg[95]; //15

//Test 6
//assign GND    = shiftreg[96]; //0
//assign GND    = shiftreg[97]; //1
assign D3IO_p[5]    = shiftreg[98]; //2
assign D3IO_n[5]    = shiftreg[99]; //3
assign D2IO_p[3]    = shiftreg[100]; //4
assign D2IO_n[3]    = shiftreg[101]; //5
assign D2IO_p[5]    = shiftreg[102]; //6
//assign GND    = shiftreg[103]; //7
assign D3IO_p[1]    = shiftreg[104]; //8
assign D2IO_n[5]    = shiftreg[105]; //9
assign D3IO_n[1]    = shiftreg[106]; //10
assign D3IO_p[3]    = shiftreg[107]; //11
assign D3I_p[7]    = shiftreg[108]; //12
assign D3IO_p[7]    = shiftreg[109]; //13
assign D3IO_n[3]    = shiftreg[110]; //14
assign D3I_n[7]    = shiftreg[111]; //15

//Test 7
assign D2I_p[2]    = shiftreg[112]; //0
assign D2I_p[3]    = shiftreg[113]; //1
assign D3I_p[1]    = shiftreg[114]; //2
assign D2I_p[4]    = shiftreg[115]; //3
assign D2I_n[2]    = shiftreg[116]; //4
assign D2I_n[3]    = shiftreg[117]; //5
assign D3I_n[1]    = shiftreg[118]; //6
assign D2I_n[4]    = shiftreg[119]; //7
assign D3I_p[0]    = shiftreg[120]; //8
assign D3I_p[2]    = shiftreg[121]; //9
assign D3I_p[5]    = shiftreg[122]; //10
assign D3I_p[6]    = shiftreg[123]; //11
assign D3I_n[6]    = shiftreg[124]; //12
assign D3I_n[5]    = shiftreg[125]; //13
assign D3I_n[2]    = shiftreg[126]; //14
assign D3I_n[0]    = shiftreg[127]; //15


endmodule