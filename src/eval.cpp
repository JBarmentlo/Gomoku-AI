#include "state.hpp"
#include "utils.hpp"
#include "defines.hpp"
#include "pattern.hpp"



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

inline int	count_full_and_empty(State &state, int row, int col, int r_delta, int c_delta, int player)
{
	int square;
	int	count		= 0;
	int empties 	= 0;
	int	top_space	= 0;
	int	bot_space	= 0;
	int	gap			= 0;
	bool started	= false;
	int	delta;

	int enemy 		= NEXT_PLAYER(player);

	for (delta = -SURROUND_SIZE; delta <= SURROUND_SIZE; delta++)
	{
		if (not is_in_bounds(row + delta * r_delta, col + delta * c_delta))
			continue;

		square = state.get_square(row + delta * r_delta, col + delta * c_delta);

		if (square == enemy) // ! BOLD ASSUMPTION HERE BASED ON SURROUND SIZE == 2
			break;
		
		if (square == EMPTY)
		{
			empties += 1;
			if (not started)
				bot_space += 1;
			else
				top_space += 1;
		}

		if (square == player)
		{
			count += 1;
			started = true;
			gap += top_space;
			top_space = 0;
		}
	}

	
	if (count + empties < 5)
		return 0;

	if (count ==  3 and empties == 2)
	{
		if (bot_space == 0)
			delta = -SURROUND_SIZE - 1;
		if (top_space == 0)
			delta = SURROUND_SIZE + 1;

		if (is_in_bounds(row + delta * r_delta, col + delta * c_delta))
			if (state.get_square(row + delta * r_delta, col + delta * c_delta) == EMPTY)
			{
				state.free_threes += 1;
			}
		
	}
	// return (count); // ! DEBUGGIN PURPOSES
	return (1 << (2 * count));
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
		score += count_full_and_empty(state, row, col, 0, 1, BLACK);
		score += count_full_and_empty(state, row, col, 1, 0, BLACK);
		score += count_full_and_empty(state, row, col, 1, 1, BLACK);
		score += count_full_and_empty(state, row, col, 1, -1, BLACK);
		score += count_full_and_empty(state, row, col, 0, 1, WHITE);
		score += count_full_and_empty(state, row, col, 1, 0, WHITE);
		score += count_full_and_empty(state, row, col, 1, 1, WHITE);
		score += count_full_and_empty(state, row, col, 1, -1, WHITE);
	}
	else
	{
		score += count_full_and_empty(state, row, col, 0, 1, player);
		score += count_full_and_empty(state, row, col, 1, 0, player);
		score += count_full_and_empty(state, row, col, 1, 1, player);
		score += count_full_and_empty(state, row, col, 1, -1, player);	
	}

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

	for (int delta = -SURROUND_SIZE; delta <= SURROUND_SIZE; delta++) // * CAN BE OPTIMIZED TO AVOID vicinity of EDGES + - SURROUND_SIZE WHERE SCORE IS 0
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

	for (int delta = -SURROUND_SIZE; delta <= SURROUND_SIZE; delta++) // * CAN BE OPTIMIZED TO AVOID vicinity of EDGES + - SURROUND_SIZE WHERE SCORE IS 0
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