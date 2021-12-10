#include "state.hpp"
#include "utils.hpp"
#include "defines.hpp"
#include "pattern.hpp"


// int 			pair_eval(State &state)
// {
// 	pattern p;
// 	int score = 0;

// 	p.w_bits[0] = true;
// 	p.w_bits[1] = true;
// 	p.width = 2;
// 	p.height = 1;
// 	score += state.count_pattern(p);
// 	swap_colors(p);
// 	score -= state.count_pattern(p);
// 	swap_colors(p);

// 	p.w_bits[1] = false;
// 	p.w_bits[19] = true;
// 	p.width = 1;
// 	p.height = 2;
// 	score += state.count_pattern(p);
// 	swap_colors(p);
// 	score -= state.count_pattern(p);
// 	swap_colors(p);

// 	p.w_bits[19] = false;
// 	p.w_bits[20] = true;
// 	p.width = 2;
// 	p.height = 2;
// 	score += state.count_pattern(p);
// 	swap_colors(p);
// 	score -= state.count_pattern(p);
// 	swap_colors(p);

// 	p.w_bits.reset();
// 	p.w_bits[19] = true;
// 	p.w_bits[1] = true;
// 	p.width = 2;
// 	p.height = 2;
// 	score += state.count_pattern(p);
// 	swap_colors(p);
// 	score -= state.count_pattern(p);
// 	swap_colors(p);

// 	return (score);
// }

// void			update_pair_eval(State &state)
// {
// 	state.score += state.find_pattern_around_last_move(create_pair_pattern, WHITE);
// 	state.score -= state.find_pattern_around_last_move(create_pair_pattern, BLACK);
// }

// int				pairs_at_coord(State &state)
// {
// 	int directions[4] = {DOWN, RIGHT, DOWN_RIGHT, DOWN_LEFT};
// 	int score = 0;
// 	pattern p;
// 	int last_move_r = state.last_move / BOARD_WIDTH;
// 	int last_move_c = state.last_move % BOARD_WIDTH;

// 	for (int dir : directions)
// 	{
// 		p = create_pair_pattern(dir, state.player);
// 		if (shift_pattern_to(p, last_move_r, last_move_c) and (state.contains(p)))
// 		{
// 			score += 1;
// 		}
// 		if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (state.contains(p)))
// 		{
// 			score += 1;
// 		}
// 	}
// 	return (score * PAIR_VALUE);
// }

// int				pairs_at_coord_color(State &state, int coord, int player)
// {
// 	constexpr int directions[4] = {DOWN, RIGHT, DOWN_RIGHT, DOWN_LEFT};
// 	int score = 0;
// 	pattern p;
// 	int last_move_r = coord / BOARD_WIDTH;
// 	int last_move_c = coord % BOARD_WIDTH;

// 	for (int dir : directions)
// 	{
// 		p = create_pair_pattern(dir, player);
// 		if (shift_pattern_to(p, last_move_r, last_move_c) and (state.contains(p)))
// 		{
// 			score += 1;
// 		}
// 		if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (state.contains(p)))
// 		{
// 			score += 1;
// 		}
// 	}
// 	if (player == BLACK)
// 		return (-score * PAIR_VALUE);
// 	else
// 		return (score * PAIR_VALUE);
// }


// int		tuples_eval_at_coord_old(State &state, int coord)
// {
// 	/*
// 		Evaluates the number of points gained by the piece at coord (can be negative if black wins points) 
// 	*/

// 	int score_delta = 0;
// 	int player = state.get_square(coord / BOARD_WIDTH, coord % BOARD_HEIGHT);
// 	score_delta += PAIR_VALUE * state.find_pattern_around_last_move(create_pair_pattern, player);
// 	score_delta += TRIPLET_VALUE* state.find_pattern_around_last_move(create_triplet_pattern, player);
// 	score_delta += QUATOR_VALUE * state.find_pattern_around_last_move(create_quator_pattern, player);
// 	// score_delta += 5000000 * state.find_pattern_around_last_move(create_penta_pattern, player);


// 	if (player == BLACK)
// 	{
// 		return (-score_delta);
// 	}
// 	else
// 	{
// 		return (score_delta);
// 	}
// }

inline int	count_full_then_empty(const State &state, int row, int col, int r_delta, int c_delta, int player)
{
	int square;
	int	count				= 1;

	for (int delta = 1; delta <= 5; delta++)
	{
		if (not is_in_bounds(row + delta * r_delta, col + delta * c_delta))
			break;

		square = state.get_square(row + delta * r_delta, col + delta * c_delta);

		if (square == NEXT_PLAYER(player))
			break;
		
		if (square == EMPTY)
			break;

		count += 1;
	}

	for (int delta = 1; delta <= 5; delta++)
	{
		if (not is_in_bounds(row - delta * r_delta, col - delta * c_delta))
			break;

		square = state.get_square(row - delta * r_delta, col - delta * c_delta);

		if (square == NEXT_PLAYER(player))
			break;
		
		if (square == EMPTY)
			break;

		count += 1;
	}
	if (count == 1)
		return (0);
	if (count == 5)
		return (123456789);
	return (1 << (2 * count));
}

inline int	count_full_and_empty(const State &state, int row, int col, int r_delta, int c_delta, int player)
{
	int square;
	int	count		= 0;
	int empties 	= 0;
	int enemy 		= NEXT_PLAYER(player);

	for (int delta = 0; delta <= 2; delta++)
	{
		if (not is_in_bounds(row + delta * r_delta, col + delta * c_delta))
			break;

		square = state.get_square(row + delta * r_delta, col + delta * c_delta);

		if (square == enemy)
			break;

		if (square == EMPTY)
			empties += 1;

		if (square == player)
			count += 1;
	}

	for (int delta = 1; delta <= 2; delta++)
	{
		if (not is_in_bounds(row - delta * r_delta, col - delta * c_delta))
			break;

		square = state.get_square(row - delta * r_delta, col - delta * c_delta);

		if (square == enemy)
			break;

		if (square == EMPTY)
			empties += 1;

		if (square == player)
			count += 1;
	}
	
	if (count + empties < 5)
		return 0;

	// return (count); // ! DEBUGGIN PURPOSES
	return (1 << (count - 1));
}

int			tuples_eval_at_coord(const State &state, int coord)
{
	/*
		Evaluates the number of points gained by the piece at coord (can be negative if black wins points) 
	*/

	// * does not take into account score lost because of empty squares being filled 
	int player 		= state.get_square(coord / BOARD_WIDTH, coord % BOARD_HEIGHT);
	if (player == EMPTY)
		return 0;
	int score		= 0;
	
	int	row = coord / BOARD_WIDTH;
	int	col = coord % BOARD_WIDTH;

	score += count_full_then_empty(state, row, col, 0, 1, player);
	score += count_full_then_empty(state, row, col, 1, 0, player);
	score += count_full_then_empty(state, row, col, 1, 1, player);
	score += count_full_then_empty(state, row, col, 1, -1, player);

	if (player == BLACK)
	{
		return (-score);
	}
	else
	{
		return (score);
	}
}

int			tuples_eval_at_coord_potential(State &state, int coord, int player)
{
	int score		= 0;
	
	int	row = coord / BOARD_WIDTH;
	int	col = coord % BOARD_WIDTH;

	score += count_full_then_empty(state, row, col, 0, 1, player);
	score += count_full_then_empty(state, row, col, 1, 0, player);
	score += count_full_then_empty(state, row, col, 1, 1, player);
	score += count_full_then_empty(state, row, col, 1, -1, player);

	if (player == BLACK)
	{
		return (-score);
	}
	else
	{
		return (score);
	}
}

int			new_eval(State &state, int row, int col)
{
	int score		= 0;
	int player		= state.get_square(row, col);

	if (player == EMPTY) // ! MAYBE DONT DO THIS
	{
		return (0);
	}
	score += count_full_and_empty(state, row, col, 0, 1, player);
	score += count_full_and_empty(state, row, col, 1, 0, player);
	score += count_full_and_empty(state, row, col, 1, 1, player);
	score += count_full_and_empty(state, row, col, 1, -1, player);

	if (player == BLACK)
	{
		return (-score);
	}
	else
	{
		return (score);
	}
}

int			new_eval_dir(State &state, int row, int col, int r_d, int c_d, int player)
{
	int score		= 0;

	score += count_full_and_empty(state, row, col, r_d, c_d, player);
	std::cout << "s: " << score << " r_c: " << r_d << " c_d: " << c_d << std::endl;
	if (player == BLACK)
	{
		return (-score);
	}
	else
	{
		return (score);
	}
}

int			eval_surround_square(State &state, int coord)
{
	int	row			= coord / BOARD_WIDTH;
	int	col			= coord % BOARD_WIDTH;
	int score_diff	= 0;
	int tmp_score;
	int	r_d;
	int	c_d;

	tmp_score = new_eval(state, row, col);
	score_diff += tmp_score - state.score_board[flat_coord(row, col)];
	state.score_board[flat_coord(row, col)] = tmp_score;

	for (int delta = -2; delta <= 2; delta++) // * CAN BE OPTIMIZED TO AVOID vicinity of EDGES + - 2 WHERE SCORE IS 0
	{
		if (delta == 0)
			continue;

		if (is_in_bounds(row, col + 1 * delta))
		{
			tmp_score = new_eval(state, row, col + 1 * delta);
			// tmp_score = new_eval_dir(state, row, col + 1 * delta, 0, 1);
			score_diff += tmp_score - state.score_board[flat_coord(row, col + 1 * delta)];
			state.score_board[flat_coord(row, col + 1 * delta)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col))
		{
			tmp_score = new_eval(state, row + 1 * delta, col);
			// tmp_score = new_eval_dir(state, row + 1 * delta, col, 1, 0);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col)];
			state.score_board[flat_coord(row + 1 * delta, col)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col + 1 * delta))
		{
			tmp_score = new_eval(state, row + 1 * delta, col + 1 * delta);
			// tmp_score = new_eval_dir(state, row + 1 * delta, col + 1 * delta, 1, 1);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col + 1 * delta)];
			state.score_board[flat_coord(row + 1 * delta, col + 1 * delta)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col - 1 * delta))
		{
			// tmp_score = new_eval_dir(state, row + 1 * delta, col - 1 * delta, 1, -1);
			tmp_score = new_eval(state, row + 1 * delta, col - 1 * delta);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col - 1 * delta)];
			state.score_board[flat_coord(row + 1 * delta, col - 1 * delta)] = tmp_score;
		}
	}
	return (score_diff);
}

int			eval_surround_square_potential(State &state, int coord)
{
	int	row			= coord / BOARD_WIDTH;
	int	col			= coord % BOARD_WIDTH;
	int score_diff	= 0;
	int tmp_score;
	int	r_d;
	int	c_d;
	state.set_piece(coord);
	tmp_score = new_eval(state, row, col);
	score_diff += tmp_score - state.score_board[flat_coord(row, col)];
	state.score_board[flat_coord(row, col)] = tmp_score;

	for (int delta = -2; delta <= 2; delta++) // * CAN BE OPTIMIZED TO AVOID vicinity of EDGES + - 2 WHERE SCORE IS 0
	{
		if (delta == 0)
			continue;

		if (is_in_bounds(row, col + 1 * delta))
		{
			tmp_score = new_eval(state, row, col + 1 * delta);
			// tmp_score = new_eval_dir(state, row, col + 1 * delta, 0, 1);
			score_diff += tmp_score - state.score_board[flat_coord(row, col + 1 * delta)];
			state.score_board[flat_coord(row, col + 1 * delta)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col))
		{
			tmp_score = new_eval(state, row + 1 * delta, col);
			// tmp_score = new_eval_dir(state, row + 1 * delta, col, 1, 0);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col)];
			state.score_board[flat_coord(row + 1 * delta, col)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col + 1 * delta))
		{
			tmp_score = new_eval(state, row + 1 * delta, col + 1 * delta);
			// tmp_score = new_eval_dir(state, row + 1 * delta, col + 1 * delta, 1, 1);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col + 1 * delta)];
			state.score_board[flat_coord(row + 1 * delta, col + 1 * delta)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col - 1 * delta))
		{
			// tmp_score = new_eval_dir(state, row + 1 * delta, col - 1 * delta, 1, -1);
			tmp_score = new_eval(state, row + 1 * delta, col - 1 * delta);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col - 1 * delta)];
			state.score_board[flat_coord(row + 1 * delta, col - 1 * delta)] = tmp_score;
		}
	}
	return (score_diff);
}