/*
	Joseph Johnson IV
	J3343734
	EEL 4783
*/

`timescale 1ns / 1ps

// Transparent Latch Module
// The output will be the input by default
// When reset is 0, regardless of enable the output will be 0
// When enable is 1, if set is 0, the output will be 1

module transparent_latch(D, E, S, R, Q);
	input D, E, S, R;
	output Q;
	reg Q;
	
	initial
		begin
			Q <= D;
		end
	
	always @ (E or R)
		begin
		
			if ((E == 1) && (S == 0))
				Q <= 1;
		
			if (R == 0)
				Q <= 0;
				
			else
				Q <= D;
		end
				
endmodule

module Stimulus;
	
	reg in, en, set, rst;
	wire out;
	
	transparent_latch a (in , en, set, rst, out);
	
	initial
		begin
			in = 0;
			en = 0;
			set = 0;
			rst = 0;
		end
	
	initial
		begin
	
		// Going to toggle inputs for simulation
		// in, en, set, rst -> 0000
	
			#100 rst = 1; // 0001
		
			#100 rst = 0;
			#0 set = 1; // 0010
		
			#100 rst = 1; // 0011
			
			#100 en = 1; // 0100
			#0 set = 0;
			#0 rst = 0;
		
			#100 rst = 1; // 0101
		
			#100 rst = 0; // 0110
			#0 set = 1;
		
			#100 rst = 1; // 0111
		
			#100 rst = 0; // 1000
			#0 set = 0;
			#0 en = 0;
			#0 in = 1;
		
			#100 rst = 1; // 1001
		
			#100 rst = 0; // 1010
			#0 set = 1;
		
			#100 rst = 1; // 1011
			
			#100 rst = 0; // 1100
			#0 set = 0;
			#0 en = 1; 
			
			#100 rst = 1; // 1101
			
			#100 rst = 0; // 1110
			#0 set = 1;
			
			#100 rst = 1; // 1111
		end
	
endmodule 