
#ifndef STATE_H
#define STATE_H

#include "defines.hpp"


class State
{
	private:
		bitboard 	b_board;
		bitboard 	w_board;
		int			w_captures;
		int			b_captures;
		int			player;

	public:
		State(/* args */);
		~State();

		void				set_piece(int row, int col);
		void				print(void);
		int					get_square(int row, int col);
		int					find_pattern(pattern pat);
		int					count_pattern(pattern pat);
};


#endif