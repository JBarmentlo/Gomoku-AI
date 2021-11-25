#ifndef DEF_H
#define DEF_H

#include <bitset>

#define BOARD_WIDTH		19
#define BOARD_HEIGHT	19
#define BOARD_SIZE		BOARD_WIDTH * BOARD_HEIGHT

#define WHITE			1
#define BLACK			2
#define EMPTY			4
#define LIVE			8

#define NEXT_PLAYER(p)	((p) & (BLACK) ? (WHITE) : (BLACK))

#define PATTERN_MISSING	-1

// #define UP				8
#define DOWN			BOARD_WIDTH
// #define LEFT			-1
#define RIGHT			1
// #define UP_RIGHT		(UP | RIGHT)
// #define UP_LEFT			(UP | LEFT)
#define DOWN_RIGHT		(DOWN + RIGHT)
#define DOWN_LEFT		(DOWN - RIGHT)

#define PAIR_VALUE		2
#define CAPTURE_VALUE	2



typedef std::bitset<BOARD_SIZE> bitboard;






#endif
