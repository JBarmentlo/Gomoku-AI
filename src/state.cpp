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

int				State::get_square(int row, int col) const
{
	if (this->b_board.test(row * BOARD_WIDTH + col))
	{
		return  (BLACK);
	}
	if (this->w_board.test(row * BOARD_WIDTH + col))
	{
		return  (WHITE);
	}
	return  (EMPTY);
}

void			State::print(bool print_empty)
{
	std::string symbols[4] = {"O", "X", " ", "-"};
	int sym;

	if (this->player == BLACK)
		std::cout << "Next player: BLACK"  << std::endl;
	else
		std::cout << "Next player: WHITE"  << std::endl;

	std::cout << "Score: " << this->score << std::endl;

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
	int last_coord  = this->last_move;

	bitboard& player_board = this->get_player_board();
	bitboard& enemy_board  = this->get_enemy_board();
	int& player_captures   = this->get_player_captures();

	p = create_capture_pattern(RIGHT, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord + 1);
		enemy_board.set(last_coord + 1, false);
		this->score += tuples_eval_at_coord(*this, last_coord + 2);
		enemy_board.set(last_coord + 2, false);
		score += 1;
	}
	p = create_capture_pattern(RIGHT, this->player, 3);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord - 1);
		enemy_board.set(last_coord - 1, false);
		this->score += tuples_eval_at_coord(*this, last_coord - 2);
		enemy_board.set(last_coord - 2, false);
		score += 1;
	}
	
	p = create_capture_pattern(DOWN_RIGHT, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord + BOARD_WIDTH + 1);
		enemy_board.set(last_coord + BOARD_WIDTH + 1, false);
		this->score += tuples_eval_at_coord(*this, last_coord + 2 * BOARD_WIDTH + 2);
		enemy_board.set(last_coord + 2 * BOARD_WIDTH + 2, false);
		score += 1;
	}
	p = create_capture_pattern(DOWN_RIGHT, this->player, 3);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord - BOARD_WIDTH - 1);
		enemy_board.set(last_coord - BOARD_WIDTH - 1, false);
		this->score += tuples_eval_at_coord(*this, last_coord - 2 * BOARD_WIDTH - 2);
		enemy_board.set(last_coord - 2 * BOARD_WIDTH - 2, false);
		score += 1;
	}

	p = create_capture_pattern(DOWN, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord + BOARD_WIDTH);
		enemy_board.set(last_coord + BOARD_WIDTH, false);
		this->score += tuples_eval_at_coord(*this, last_coord + 2 * BOARD_WIDTH);
		enemy_board.set(last_coord + 2 * BOARD_WIDTH, false);
		score += 1;
	}
	p = create_capture_pattern(DOWN, this->player, 3);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord - BOARD_WIDTH);
		enemy_board.set(last_coord - BOARD_WIDTH, false);
		this->score += tuples_eval_at_coord(*this, last_coord - 2 * BOARD_WIDTH);
		enemy_board.set(last_coord - 2 * BOARD_WIDTH, false);
		score += 1;
	}

	p = create_capture_pattern(DOWN_LEFT, this->player);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord + BOARD_WIDTH);
		enemy_board.set(last_coord + BOARD_WIDTH, false);
		this->score += tuples_eval_at_coord(*this, last_coord + 2 * BOARD_WIDTH);
		enemy_board.set(last_coord + 2 * BOARD_WIDTH, false);
		score += 1;
	}
	p = create_capture_pattern(DOWN_LEFT, this->player, 3);
	if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
	{
		this->score += tuples_eval_at_coord(*this, last_coord - BOARD_WIDTH);
		enemy_board.set(last_coord - BOARD_WIDTH, false);
		this->score += tuples_eval_at_coord(*this, last_coord - 2 * BOARD_WIDTH);
		enemy_board.set(last_coord - 2 * BOARD_WIDTH, false);
		score += 1;
	}
	std::cout << "pre: " << this->score << std::endl;
	if (player == WHITE)
		this->score += score * CAPTURE_VALUE * 2;
	else
		this->score -= score * CAPTURE_VALUE * 2;
	std::cout << "post: " << this->score << std::endl;
	return (score);
}

// int				State::find_pattern_around_last_move(pattern_generator gen, int player) const
// {
// 	// ! UNTESTED !!
// 	int directions[4] = {DOWN, RIGHT, DOWN_RIGHT, DOWN_LEFT};
// 	int score = 0;
// 	pattern p;
// 	int last_move_r = this->last_move / BOARD_WIDTH;
// 	int last_move_c = this->last_move % BOARD_WIDTH;
// 	for (int dir : directions)
// 	{
// 		p = gen(dir, player, 0);
// 		// print_pattern(p);
// 		if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
// 		{
// 			score += 1;
// 		}
// 		for (int variant = 1; variant < p.size; variant++)
// 		{
// 			p = gen(dir, player, variant);
// 			if (shift_pattern_to(p, last_move_r, last_move_c) and (*this == p))
// 			{
// 				score += 1;
// 			}
// 		}
// 	}
// 	return (score);
// }

inline bool 	State::operator==(const pattern& rhs) const
{
	return (((not rhs.color & WHITE) or ((this->w_board & rhs.w_bits) == rhs.w_bits)) 
		and ((not rhs.color & BLACK) or ((this->b_board & rhs.b_bits) == rhs.b_bits))) 
		and ((not rhs.color & EMPTY) or ((this->b_board | this->w_board) & rhs.e_bits).count() == 0);
}

bool 			State::operator<(const State& rhs) const
{
	return (this->score < rhs.score);
}


bool 			State::operator>(const State& rhs) const
{
	return (this->score > rhs.score);
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
	if (s.is_win())
	{
		s.game_win = true;
	}
	else
	{
		s.score += tuples_eval_at_coord(s, s.last_move);
	}
	// std::cout << "Player and live board" << std::endl;
	s.player = NEXT_PLAYER(this->player);
	s.update_live_board();

	// std::cout << "baby done" << std::endl;
	// std::cout  << std::endl;
	return (s);
}

bool	State::count_to_5(int row, int col, int r_delta, int c_delta)
{
	int square;
	int score				= 0;
	int	count				= 1;

	for (int delta = 1; delta <= 5; delta++)
	{
		if (not is_in_bounds(row + delta * r_delta, col + delta * c_delta))
			break;

		square = this->get_square(row + delta * r_delta, col + delta * c_delta);

		if (square == NEXT_PLAYER(this->player) or square == EMPTY)
			break;

		count += 1;
	}

	for (int delta = 1; delta <= 5; delta++)
	{
		if (not is_in_bounds(row - delta * r_delta, col - delta * c_delta))
			break;

		square = this->get_square(row - delta * r_delta, col - delta * c_delta);

		if (square == NEXT_PLAYER(this->player) or square == EMPTY)
			break;
			
		count += 1;
	}	
	return (count >= 5);
}



bool			State::is_win(void)
{
	if (this->b_captures == 5 or this->w_captures == 5)
		return true;
	const int row = this->last_move / BOARD_WIDTH;
	const int col = this->last_move % BOARD_WIDTH;

	if (count_to_5(row, col, 0, 1) or count_to_5(row, col, 1, 0) or count_to_5(row, col, 1, 1) or count_to_5(row, col, 1, -1))
		return true;

	return false;
}

