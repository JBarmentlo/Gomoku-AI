#ifndef MINIMAX_H
#define MINIMAX_H

#include "defines.hpp"
#include "pattern.hpp"
#include "state.hpp"
#include "eval.hpp"

int	minimax(State state, bool maximizer, int limit, int depth = 0, int alpha = INT32_MIN, int beta =  INT32_MAX);

#endif // !MINIMAX_H