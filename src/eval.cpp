#include "state.hpp"
#include "utils.hpp"
#include "defines.hpp"


int count_pairs(State &state, int player)
{
	pattern p;
	int score = 0;
	bitboard *b;
	if (player == WHITE)
		b = &p.w_bits;

	if (player == BLACK)
		b = &p.b_bits;

	b[0] = true;
	(*b)[1] = true;
	p.width = 2;
	p.height = 1;
	score += state.count_pattern(p);

	(*b)[1] = false;
	(*b)[19] = true;
	p.width = 1;
	p.height = 2;
	score += state.count_pattern(p);

	(*b)[19] = false;
	(*b)[20] = true;
	p.width = 2;
	p.height = 2;
	score += state.count_pattern(p);

	(*b).reset();
	(*b)[19] = true;
	(*b)[1] = true;
	p.width = 2;
	p.height = 2;
	score += state.count_pattern(p);

	return (score);
}

int	pair_eval(State &state, int player)
{
	if (player == WHITE)
	{
		return (count_pairs(state, WHITE) - count_pairs(state, BLACK));
	}
	else
	{
		return (count_pairs(state, BLACK) - count_pairs(state, WHITE));
	}
}
