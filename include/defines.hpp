#ifndef DEF_H
#define DEF_H

#include <bitset>

#define BOARD_WIDTH		19
#define BOARD_HEIGHT	19
#define BOARD_SIZE		BOARD_WIDTH * BOARD_HEIGHT

#define WHITE			0
#define BLACK			1
#define EMPTY			2




typedef std::bitset<BOARD_SIZE> bitboard;

#endif
