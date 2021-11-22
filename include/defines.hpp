#ifndef DEF_H
#define DEF_H

#include <bitset>

#define BOARD_WIDTH		19
#define BOARD_HEIGHT	19
#define BOARD_SIZE		BOARD_WIDTH * BOARD_HEIGHT

#define WHITE			0
#define BLACK			1
#define EMPTY			2

#define PATTERN_MISSING	-1

#define UP				8
#define DOWN			1
#define LEFT			2
#define RIGHT			4
#define UP_RIGHT		(UP | RIGHT)
#define UP_LEFT			(UP | LEFT)
#define DOWN_RIGHT		(DOWN | RIGHT)
#define DOWN_LEFT		(DOWN | LEFT)



typedef std::bitset<BOARD_SIZE> bitboard;

typedef struct	s_pattern{
	bitboard 	b_bits;
	bitboard 	w_bits;
	int			height;
	int			width;
}				pattern;

#endif
