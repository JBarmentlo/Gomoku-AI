
#ifndef STATE_H
#define STATE_H

#include "defines.hpp"


class State
{
	private:
		bitboard 	b_board;
		bitboard 	w_board;
		int			w_captures = 0;
		int			b_captures = 0;
		int			last_move;

	public:
		int			player = WHITE;
		State(/* args */);
		~State();

		void				set_piece(int row, int col);
		void				set_piece(int coord);
		// bool				DOUBLE_THREE				
		int					compute_captures(void);
		void				print(void);
		int					get_square(int row, int col);
		int					find_pattern(pattern pat);
		int					count_pattern(pattern pat);
		bitboard&			get_player_board(void);
		bitboard&			get_enemy_board(void);

		inline bool operator==(const pattern& rhs) const;

};


#endif