#ifndef EVAL_H
#define EVAL_H

#include "defines.hpp"
#include "state.hpp"

int count_pairs(State &state, int player);
int	pair_eval(State &state, int player);


typedef int (*evaluation_function)(State&);


#endif