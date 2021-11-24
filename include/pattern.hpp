#ifndef PATTERN_H
#define PATTERN_H

#include "defines.hpp"


class Pattern
{
private:
	/* data */
public:
	bitboard 	b_bits;
	bitboard 	w_bits;
	bitboard 	e_bits;

	int			colors;

	int			height;
	int			width;

	int			r_shift = 0;
	int			c_shift = 0;
	
	int			start_r;
	int			start_c;
	int			end_r;
	int			end_c;

	Pattern(/* args */);
	~Pattern();
};




// typedef struct	s_pattern{

// }				pattern;

typedef Pattern (*pattern_generator)(int, int);

#endif // DEBUG