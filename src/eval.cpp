#include "state.hpp"
#include "utils.hpp"
#include "defines.hpp"


int pair_eval(State &state)
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
	print_pattern(p);

	return (score);
}

void	update_pair_eval(State &state)
{
	state.score += state.find_pattern_around_last_move(create_pair_pattern, WHITE);
	state.score -= state.find_pattern_around_last_move(create_pair_pattern, BLACK);
}
