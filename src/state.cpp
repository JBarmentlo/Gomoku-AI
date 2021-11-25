#include "defines.hpp"
#include "state.hpp"
#include "eval.hpp"

#include "utils.hpp"
#include "pattern.hpp"


#include <string>
#include <iostream>
#include <iomanip>

State::State(/* args */)
{
	this->player = WHITE;
	this->w_captures = 0;
	this->b_captures = 0;
}

State::~State()
{
}


void			State::set_piece(int row, int col)
{
	/*
	Sets a piece at the given position.
	*/
	if (this->player == WHITE)
	{
		if (not this->w_board[row * BOARD_WIDTH + col])
		{
			this->w_board.set(row * BOARD_WIDTH + col, true);
		}
	}
	else
	{
		if (not this->b_board[row * BOARD_WIDTH + col])
		{
			this->b_board.set(row * BOARD_WIDTH + col, true);
		}		
	}
	this->last_move = row * BOARD_WIDTH + col;
}

void			State::set_piece(int coord)
{
	/*
	Sets a piece at the given position.
	*/
	if (this->player == WHITE)
	{
		if (not this->w_board.test(coord))
		{
			this->w_board.set(coord, true);
		}
	}
	else
	{
		if (not this->b_board.test(coord))
		{
			this->b_board.set(coord, true);
		}		
	}
	this->last_move = coord;
}

int				State::get_square(int row, int col)
{
	if (this->b_board[row * BOARD_WIDTH + col])
	{
		return  (BLACK);
	}
	if (this->w_board[row * BOARD_WIDTH + col])
	{
		return  (WHITE);
	}
	return  (EMPTY);
}

void			State::print(bool print_empty)
{
	std::string symbols[4] = {"O", "X", " ", "-"};
	int sym;

	for (int c = 0; c < BOARD_WIDTH; c++)
	{
		std::cout << " " << std::setw(2) << c << " ";
	}
	std::cout << std::endl;

	for (int r = 0; r <= BOARD_HEIGHT; r++)
	{
		for (int c = 0; c <= BOARD_WIDTH; c++)
		{
			std::cout << "+   ";
		}
		std::cout << std::endl;
		if (r != BOARD_HEIGHT)
		{
			for (int c = 0; c < BOARD_WIDTH; c++)
			{
				sym = this->get_square(r, c);
				if (print_empty and sym == EMPTY)
				{
					if (this->live_board.test(r * BOARD_WIDTH + c))
						sym = LIVE - 2;
				}
				std::cout << "  " << symbols[sym / 2] << " ";
			}
			std::cout << std::setw(4) << r << std::endl;			
		}
	}
	std::cout << std::endl;
}

// int				State::find_pattern(pattern pat)
// {
// 	int last_r = 0;
// 	int last_c = 0;
// 	for (int r = 0; r <= BOARD_HEIGHT - pat.height; r++)
// 	{
// 		for (int c = 0; c <= BOARD_WIDTH - pat.width; c++)
// 		{
// 			shift_pattern(pat, r -  last_r, c - last_c);
// 			last_r = r;
// 			last_c = c;
// 			if (((pat.b_bits & this->b_board) == pat.b_bits) and ((pat.w_bits & this->w_board) == pat.w_bits))
// 			{
// 				return (r * BOARD_WIDTH + c);
// 			}
// 		}
// 	}
// 	return (PATTERN_MISSING);
// }

// int				State::count_pattern(pattern pat)
// {
// 	int last_r = 0;
// 	int last_c = 0;
// 	int out    = 0;
// 	for (int r = 0; r <= BOARD_HEIGHT - pat.height; r++)
// 	{
// 		for (int c = 0; c <= BOARD_WIDTH - pat.width; c++)
// 		{
// 			shift_pattern(pat, r -  last_r, c - last_c);
// 			last_r = r;
// 			last_c = c;
// 			if (((pat.b_bits & this->b_board) == pat.b_bits) and ((pat.w_bits & this->w_board) == pat.w_bits))
// 			{
// 				out = out + 1;
// 			}
// 		}
// 	}
// 	return (out);
// }

bitboard&		State::get_player_board(void)
{
	if (this->player == WHITE)
	{
		return this->w_board;
	}
	return this->b_board;
}

bitboard&		State::get_enemy_board(void)
{
	if (this->player == WHITE)
	{
		return this->b_board;
	}
	return this->w_board;
}

int&			State::get_player_captures(void)
{
	if (this->player == WHITE)
	{
		return this->w_captures;
	}
	return this->b_captures;
}

int&			State::get_enemy_captures(void)
{
	if (this->player == WHITE)
	{
		return this->b_captures;
	}
	return this->w_captures;
}

int				State::compute_captures(void)
{
	/*
	Finds and removes the captured pieces
	updates this -< captures
	*/
	pattern p;
	int score = 0;

	int last_move_r = this->last_move / BOARD_WIDTH;
	int last_move_c = this->last_move % BOARD_WIDTH;
	int last_coord = this->last_move;

	bitboard& player_board = this->get_player_board();
	bitboard& enemy_board = this->get_enemy_board();
	int& player_captures = this->get_player_captures();

	p = create_capture_pattern(RIGHT, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		// this->score += this->value_coord_fun(*this, last_coord + 1, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + 1, false);
		// this->score += this->value_coord_fun(*this, last_coord + 2, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + 2, false);
		score += 1;
	}
	if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (*this == p))
	{
		// print_pattern(oldp);
		// this->score += this->value_coord_fun(*this, last_coord - 1, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - 1, false);
		// this->score += this->value_coord_fun(*this, last_coord - 2, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - 2, false);
		score += 1;
	}
	
	p = create_capture_pattern(DOWN_RIGHT, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		// this->score += this->value_coord_fun(*this, last_coord + BOARD_WIDTH + 1, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + BOARD_WIDTH + 1, false);
		// this->score += this->value_coord_fun(*this, last_coord + 2 * BOARD_WIDTH + 2, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + 2 * BOARD_WIDTH + 2, false);
		score += 1;
	}
	if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (*this == p))
	{
		// this->score += this->value_coord_fun(*this, last_coord - BOARD_WIDTH - 1, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - BOARD_WIDTH - 1)= false;
		// this->score += this->value_coord_fun(*this, last_coord - 2 * BOARD_WIDTH - 2, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - 2 * BOARD_WIDTH - 2, false);
		score += 1;
	}

	p = create_capture_pattern(DOWN, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		// this->score += this->value_coord_fun(*this, last_coord + BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + BOARD_WIDTH, false);
		// this->score += this->value_coord_fun(*this, last_coord + 2 * BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + 2 * BOARD_WIDTH, false);
		score += 1;
	}
	if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (*this == p))
	{
		// this->score += this->value_coord_fun(*this, last_coord - BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - BOARD_WIDTH)= false;
		// this->score += this->value_coord_fun(*this, last_coord - 2 * BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - 2 * BOARD_WIDTH, false);
		score += 1;
	}

	p = create_capture_pattern(DOWN_LEFT, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		// this->score += this->value_coord_fun(*this, last_coord + BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + BOARD_WIDTH, false);
		// this->score += this->value_coord_fun(*this, last_coord + 2 * BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord + 2 * BOARD_WIDTH, false);
		score += 1;
	}
	if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (*this == p))
	{
		// this->score += this->value_coord_fun(*this, last_coord - BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - BOARD_WIDTH)= false;
		// this->score += this->value_coord_fun(*this, last_coord - 2 * BOARD_WIDTH, NEXT_PLAYER(this->player));
		enemy_board.set(last_coord - 2 * BOARD_WIDTH, false);
		score += 1;
	}
	if (player == WHITE)
		this->score += score * CAPTURE_VALUE * 2;
	else
		this->score -= score * CAPTURE_VALUE * 2;
	return (score);
}

int				State::find_pattern_around_last_move(pattern_generator gen, int player) const
{
	int directions[4] = {DOWN, RIGHT, DOWN_RIGHT, DOWN_LEFT};
	int score = 0;
	pattern p;
	int last_move_r = this->last_move / BOARD_WIDTH;
	int last_move_c = this->last_move % BOARD_WIDTH;

	for (int dir : directions)
	{
		p = gen(dir, player);
		if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
		{
			score += 1;
		}
		if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (*this == p))
		{
			score += 1;
		}
	}
	return (score);
}

inline bool 	State::operator==(const pattern& rhs) const
{
	return (((this->w_board & rhs.w_bits) == rhs.w_bits) and ((this->b_board & rhs.b_bits) == rhs.b_bits));
}

inline bool 	State::operator<(const State& rhs) const
{
	return (this->score < rhs.score);
}

// bool			State::contains(pattern& pat) const
// {
// 	return (*this == pat);
// }

void			State::update_live_board(void)
{
	this->live_board = ((this->b_board << 1) | ((this->b_board << 1) << BOARD_WIDTH) | ((this->b_board << 1) >> BOARD_WIDTH) | (this->b_board >> 1) | ((this->b_board >> 1) << BOARD_WIDTH) | ((this->b_board >> 1) >> BOARD_WIDTH) | (this->b_board >> BOARD_WIDTH) | (this->b_board << BOARD_WIDTH) | (this->w_board << 1) | ((this->w_board << 1) >> BOARD_WIDTH) | ((this->w_board << 1) << BOARD_WIDTH) | (this->w_board >> 1) | ((this->w_board >> 1) >> BOARD_WIDTH) | ((this->w_board >> 1) << BOARD_WIDTH) | (this->w_board >> BOARD_WIDTH) | (this->w_board << BOARD_WIDTH)) & ~(this->w_board | this->b_board);
}

State			State::make_baby_from_coord(int coord)
{
	State s = *this;
	// std::cout << "Set piece: " << coord << std::endl;
	s.set_piece(coord);
	// std::cout << "Captures" << std::endl;
	s.compute_captures();
	// std::cout << "Update eval" << std::endl;
	// update_pair_eval(s);
	// std::cout << "Player and live board" << std::endl;
	s.player = (s.player + 1) % 2;
	// std::cout << "player is: " << s.player << std::endl;
	// s.update_live_board();
	// std::cout << "baby done" << std::endl;
	// std::cout  << std::endl;
	return (s);
}
#include <set>

std::multiset<State> State::make_ordered_babies()
{
	std::multiset<State> out;

	for (int coord = 0; coord < BOARD_SIZE; coord++)
	{
		if (this->live_board[coord])
		{
			out.insert(this->make_baby_from_coord(coord));
		}
	}
	return out;
}
