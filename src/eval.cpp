#include "state.hpp"
#include "utils.hpp"
#include "defines.hpp"


int 			pair_eval(State &state)
{
	pattern p;
	int score = 0;

	p.w_bits[0] = true;
	p.w_bits[1] = true;
	p.width = 2;
	p.height = 1;
	score += state.count_pattern(p);
	swap_colors(p);
	score -= state.count_pattern(p);
	swap_colors(p);

	p.w_bits[1] = false;
	p.w_bits[19] = true;
	p.width = 1;
	p.height = 2;
	score += state.count_pattern(p);
	swap_colors(p);
	score -= state.count_pattern(p);
	swap_colors(p);

	p.w_bits[19] = false;
	p.w_bits[20] = true;
	p.width = 2;
	p.height = 2;
	score += state.count_pattern(p);
	swap_colors(p);
	score -= state.count_pattern(p);
	swap_colors(p);

	p.w_bits.reset();
	p.w_bits[19] = true;
	p.w_bits[1] = true;
	p.width = 2;
	p.height = 2;
	score += state.count_pattern(p);
	swap_colors(p);
	score -= state.count_pattern(p);
	swap_colors(p);

	return (score);
}

void			update_pair_eval(State &state)
{
	state.score += state.find_pattern_around_last_move(create_pair_pattern, WHITE);
	state.score -= state.find_pattern_around_last_move(create_pair_pattern, BLACK);
}

int				pairs_at_coord(State &state)
{
	int directions[4] = {DOWN, RIGHT, DOWN_RIGHT, DOWN_LEFT};
	int score = 0;
	pattern p;
	int last_move_r = state.last_move / BOARD_WIDTH;
	int last_move_c = state.last_move % BOARD_WIDTH;

	for (int dir : directions)
	{
		p = create_pair_pattern(dir, state.player);
		if (shift_pattern_to(p, last_move_r, last_move_c) and (state.contains(p)))
		{
			score += 1;
		}
		if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (state.contains(p)))
		{
			score += 1;
		}
	}
	return (score * PAIR_VALUE);
}

int				pairs_at_coord_color(State &state, int coord, int player)
{
	int directions[4] = {DOWN, RIGHT, DOWN_RIGHT, DOWN_LEFT};
	int score = 0;
	pattern p;
	int last_move_r = coord / BOARD_WIDTH;
	int last_move_c = coord % BOARD_WIDTH;

	for (int dir : directions)
	{
		p = create_pair_pattern(dir, player);
		if (shift_pattern_to(p, last_move_r, last_move_c) and (state.contains(p)))
		{
			score += 1;
		}
		if (shift_pattern_to_other_end(p, last_move_r, last_move_c) and (state.contains(p)))
		{
			score += 1;
		}
	}
	if (player == BLACK)
		return (-score * PAIR_VALUE);
	else
		return (score * PAIR_VALUE);
}
