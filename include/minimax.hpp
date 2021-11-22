#ifndef MINIMAX_H
#define MINIMAX_H

#include "defines.hpp"
#include "state.hpp"
#include "eval.hpp"

int	minimax(State state, int coord, bool maximizer, int depth, int alpha = INT32_MIN, int beta =  INT32_MAX);

#endif // !MINIMAX_H