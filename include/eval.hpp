#ifndef EVAL_H
#define EVAL_H

#include "defines.hpp"
#include "pattern.hpp"
#include "state.hpp"

int		pair_eval(State &state);
void	update_pair_eval(State &state);
int		pairs_at_coord(State &state);
int		pairs_at_coord_color(State &state, int coord, int player);


int		tuples_eval_at_coord(State &state, int coord);

typedef int (*evaluation_function)(State&);
typedef int (*cood_evaluation_function)(State&, int coord);



#endif