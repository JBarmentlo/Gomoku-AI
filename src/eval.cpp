#include "state.hpp"
#include "utils.hpp"
#include "defines.hpp"
#include "pattern.hpp"


inline int	count_full_and_empty(State &state, int row, int col, int r_delta, int c_delta, int player, bool check_free)
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

	std::cout << "EVAL at: " << row << ", " << col << std::endl;
	for (delta = -SURROUND_SIZE; delta <= SURROUND_SIZE; delta++)
	{
		if (not is_in_bounds(row + delta * r_delta, col + delta * c_delta))
			continue;

		square = state.get_square(row + delta * r_delta, col + delta * c_delta);

		if (square == enemy and started)
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
		std::cout << "r: " << row + delta * r_delta << " ,c: " << col + delta * c_delta << std::endl;
		std::cout << "count_: " << count << " empties: " << empties << " b_s: " << bot_space << " t_s: " << top_space << " gap: " << gap << std::endl;
	}


	if (check_free and count ==  3 and gap <= 1 and state.get_square(row , col) != EMPTY) // ! The last condition != EMPTY is useless now because we do not run eval on empty squares, it is there for resilience in case that behaviour is changed later
	{
		delta = 0;
		if (empties == 2)
		{		
			if (bot_space == 0)
				delta = -SURROUND_SIZE - 1;
			if (top_space == 0)
				delta = SURROUND_SIZE + 1;
		}
		else if (empties == 1 and gap == 0)
		{
			if (bot_space == 1)
				delta = SURROUND_SIZE + 1;
			if (top_space == 1)
				delta = -SURROUND_SIZE - 1;
		}
		if (delta != 0 and is_in_bounds(row + delta * r_delta, col + delta * c_delta))
			if (state.get_square(row + delta * r_delta, col + delta * c_delta) == EMPTY)
			{
				std::cout << "free: " << row << ", " << col << std::endl;
				std::cout << "empties: " << empties << " gap: " << gap << " t_s:" << top_space << " b_s: " << bot_space << std::endl;
				std::cout << "r_d: " << r_delta << " c_d: " << c_delta << std::endl;
				state.free_threes += 1;
			}
	}
		
	std::cout << "\n" << std::endl;
	if (count + empties < 5)
		return 0;
	return (1 << (2 * count));
}

int			new_eval(State &state, int row, int col, int r_d_free, int r_c_free)
{
	int score		= 0;
	int player		= state.get_square(row, col);

	if (player == EMPTY) // ! MAYBE DONT DO THIS
	{
		return (0);
	}
	else
	{
		score += count_full_and_empty(state, row, col, 0, 1, player, ((0 == r_d_free) and (1 == r_c_free)));
		score += count_full_and_empty(state, row, col, 1, 0, player, ((1 == r_d_free) and (0 == r_c_free)));
		score += count_full_and_empty(state, row, col, 1, 1, player, ((1 == r_d_free) and (1 == r_c_free)));
		score += count_full_and_empty(state, row, col, 1, -1, player, ((1 == r_d_free) and (-1 == r_c_free)));
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

int			new_eval(State &state, int row, int col)
{
	int score		= 0;
	int player		= state.get_square(row, col);

	if (player == EMPTY) // ! MAYBE DONT DO THIS
	{
		return (0);
	}
	else
	{
		score += count_full_and_empty(state, row, col, 0, 1, player, true);
		score += count_full_and_empty(state, row, col, 1, 0, player, true);
		score += count_full_and_empty(state, row, col, 1, 1, player, true);
		score += count_full_and_empty(state, row, col, 1, -1, player, true);
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
			tmp_score = new_eval(state, row, col + 1 * delta, 0, 1);
			// tmp_score = new_eval_dir(state, row, col + 1 * delta, 0, 1);
			score_diff += tmp_score - state.score_board[flat_coord(row, col + 1 * delta)];
			state.score_board[flat_coord(row, col + 1 * delta)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col))
		{
			tmp_score = new_eval(state, row + 1 * delta, col, 1, 0);
			// tmp_score = new_eval_dir(state, row + 1 * delta, col, 1, 0);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col)];
			state.score_board[flat_coord(row + 1 * delta, col)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col + 1 * delta))
		{
			tmp_score = new_eval(state, row + 1 * delta, col + 1 * delta, 1, 1);
			// tmp_score = new_eval_dir(state, row + 1 * delta, col + 1 * delta, 1, 1);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col + 1 * delta)];
			state.score_board[flat_coord(row + 1 * delta, col + 1 * delta)] = tmp_score;
		}

		if (is_in_bounds(row + 1 * delta, col - 1 * delta))
		{
			// tmp_score = new_eval_dir(state, row + 1 * delta, col - 1 * delta, 1, -1);
			tmp_score = new_eval(state, row + 1 * delta, col - 1 * delta, 1, -1);
			score_diff += tmp_score - state.score_board[flat_coord(row + 1 * delta, col - 1 * delta)];
			state.score_board[flat_coord(row + 1 * delta, col - 1 * delta)] = tmp_score;
		}
	}
	return (score_diff);
}
