/*
	Joseph Johnson IV
	J3343723
	EEL 4783
*/

`timescale 1ns / 1ps

module compare_4_32_CA(A, B, C, D, Lrg, Sml);

	input [31:0] A, B, C, D;
	output Lrg, Sml;
	
	reg [3:0] Lrg, Sml;
	
	initial
	begin
		Lrg = 4'b0000;
		Sml = 4'b0000;
	end

	// Will update whenever an input changes
	always @ (A or B or C or D)
	begin	
		// Reset before each update
		Lrg = 4'b0000;
		Sml = 4'b0000;
	
		// Each bit in Lrg represents whether the corresponding input has the largest value
		// EX: If A >= the rest, we know A is one of the inputs holding the largest value so we add 1 to the corresponding bit
		if ((A >= B) && (A >= C) && (A >= D)) Lrg = Lrg + 4'b1000;
		if ((B >= A) && (B >= C) && (B >= D)) Lrg = Lrg + 4'b0100;
		if ((C >= A) && (C >= B) && (C >= D)) Lrg = Lrg + 4'b0010;
		if ((D >= A) && (D >= B) && (D >= C)) Lrg = Lrg + 4'b0001;
		
		// Each bit in Sml represents whether the corresponding input has the smallest value
		if ((A <= B) && (A <= C) && (A <= D)) Sml = Sml + 4'b1000;
		if ((B <= A) && (B <= C) && (B <= D)) Sml = Sml + 4'b0100;
		if ((C <= A) && (C <= B) && (C <= D)) Sml = Sml + 4'b0010;
		if ((D <= A) && (D <= B) && (D <= C)) Sml = Sml + 4'b0001;
	end

endmodule

module t_compare_4_32_CA;

	reg [31:0] A, B, C, D;
	wire [3:0] Largest;
	wire [3:0] Smallest;
	
	compare_4_32_CA a (A,B,C,D,Largest,Smallest);
	
	initial
	begin
		A = 0;
		B = 0;
		C = 0;
		D = 0;
	end
	
	initial
	begin
		#100 A = 5; // A and B are the largest, C and D are the smallest
		#0 B = 5;
		
		#100 A = 3; // B is the largest, D is the smallest
		#0 B = 10;
		#0 C = 2;
		
		#100 A = D; // C is the largest, A and D are the smallest
		#0 C = 15;
		
		#100 A = C; // All 4 are equal 
		#0 B = C;
		#0 D = C;		
	end

endmodule
