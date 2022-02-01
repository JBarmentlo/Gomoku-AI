#ifndef MINIMAX_H
#define MINIMAX_H

#include "defines.hpp"
#include "pattern.hpp"
#include "state.hpp"
#include "eval.hpp"

#include <deque>

int		minimax(State state, int limit, std::deque<int> past_scores = std::deque<int>(),  int depth = 0, int alpha = BLACK_WIN, int beta =  WHITE_WIN);
int		minimax_beam(State state, int limit, int depth = 0, int alpha = BLACK_WIN, int beta =  WHITE_WIN);

// int		minimax_no_len(State state, int limit,  int depth = 0, int alpha = BLACK_WIN, int beta =  WHITE_WIN);

int		minimax_fred_start(State state, int limit);
int		minimax_fred_start_brother(State state, int limit);


#endif // !MINIMAX_H