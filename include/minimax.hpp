#ifndef MINIMAX_H
#define MINIMAX_H

#include "defines.hpp"
#include "pattern.hpp"
#include "state.hpp"
#include "eval.hpp"

#include <deque>

int		minimax(State state, int limit, std::deque<int> past_scores = std::deque<int>(),  int depth = 0, int alpha = INT32_MIN, int beta =  INT32_MAX);
int		minimax_multifred(State state, int limit);

#endif // !MINIMAX_H