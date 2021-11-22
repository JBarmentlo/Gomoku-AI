#ifndef EVAL_H
#define EVAL_H

#include "defines.hpp"
#include "state.hpp"

int	pair_eval(State &state);


typedef int (*evaluation_function)(State&);


#endif