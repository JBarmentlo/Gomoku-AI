#include <bitset>
#include <iostream>

#include "defines.hpp"
#include "utils.hpp"
#include "state.hpp"

int main()
{
	State s;

	s.set_piece(18,16);
	s.set_piece(18,18);
	s.set_piece(18,17);
	s.set_piece(18, 14);
	s.set_piece(18, 15);

	s.print();

	std::cout << "" << std::endl;


	pattern p;
	p.w_bits.set(0);
	p.w_bits.set(1);
	// p.b_bits.set(0);
	// p.b_bits.set(3);
	p.width = 2;
	p.height = 1;
	print_pattern(p);

	std::cout << s.count_pattern(p) << std::endl;



	// state.board.white = state.board.white >> 4;
	// state.board.black = state.board.black >> 4;

	// print_state(state);

}