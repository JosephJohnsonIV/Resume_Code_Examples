/*
	Joseph Johnson IV
	J3343723
	EEL 4783
*/

`timescale 1ns / 1ps

// The module we are designing
module Combo_str(Y, A, B, C, D);

	// Defining inputs and the output
	input A, B, C, D;
	output Y;
	
	// Wires connecting different gate elements
	wire w1, w2;
	
	// Or gate that takes A and D as inputs and w1 as output
	or (w1, A, D);
	
	// And gate that takes B, C, and ~D as inputs and w2 as output
	and (w2, B, C, ~D);
	
	// And gate that takes ~w1 and w2 as inputs and Y as output
	and (Y, ~w1, w2);

endmodule 

// Simulation module
module t_Combo_str;

	// A, B, C, and D will be changed so I will make them registers
	reg A, B, C, D;
	
	// Wire for output
	wire Y;
	
	// Creating an instance of the design
	Combo_str a (Y, A, B, C, D);
	
	// initializing the registers to 0
	initial
		begin
			A = 0;
			B = 0;
			C = 0;
			D = 0;
		end
		
	// I'm going to hardcode the changing inputs to show all possible cases in the truth table for this circuit
	initial 
		begin
		
			#100 D = 1; // ABCD = 0001
			
			#100 D = 0; // ABCD = 0010
			#0 C = 1;
			
			#100	D = 1; // ABCD = 0011
			
			#100 B = 1; // ABCD = 0100
			#0 C = 0;
			#0 D = 0;
			
			#100 D = 1; // ABCD = 0101
			
			#100 C = 1; // ABCD = 0110
			#0 D = 0;
			
			#100 D = 1; // ABCD = 0111
			
			#100 A = 1; // ABCD = 1000
			#0 B = 0;
			#0 C = 0;
			#0 D = 0;
			
			#100 D = 1; // ABCD = 1001
			
			#100 C = 1; // ABCD = 1010
			#0 D = 0;
			
			#100 D = 1; // ABCD = 1011
			
			#100 B = 1; // ABCD = 1100
			#0 C = 0;
			#0 D = 0;
			
			#100 D = 1; // ABCD = 1101
			
			#100 C = 1; // ABCD = 1110
			#0 D = 0;
			
			#100 D = 1; // ABCD = 1111
			
		end
		
endmodule
	