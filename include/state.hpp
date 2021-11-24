
#ifndef STATE_H
#define STATE_H

#include "defines.hpp"
#include <set>

class State
{
	private:
	public:

		bitboard 	b_board;
		bitboard 	w_board;
		bitboard	live_board;
		int			w_captures = 0;
		int			last_move;

		int			player = WHITE;
		int			b_captures = 0;
		int			score = 0;

		int			(*value_coord_fun)(State&, int, int);
		State(/* args */);
		~State();

		void				set_piece(int row, int col);
		void				set_piece(int coord);
		void				update_live_board(void);
		// bool				DOUBLE_THREE				
		int					compute_captures(void);
		void				print(void);
		int					get_square(int row, int col);
		int					find_pattern(pattern pat);
		int					find_pattern_around_last_move(pattern_generator gen, int player) const;
		int					count_pattern(pattern pat);

		bitboard&			get_player_board(void);
		bitboard&			get_enemy_board(void);
		int&				get_enemy_captures(void);
		int&				get_player_captures(void);

		bool				contains(pattern& pat) const;
		inline bool 		operator==(const pattern& rhs) const;
		inline bool 		operator<(const State& rhs) const;

		State				make_baby_from_coord(int coord);
		std::multiset<State> make_ordered_babies();

		int					compute_black_captures(void);
		int 				compute_white_captures(void);


};


#endif