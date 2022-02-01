#include "minimax.hpp"
#include "utils.hpp"
#include "eval.hpp"

#include <iostream>

#include <vector>
#include <array>

#include <algorithm>
#include <deque>


bool	compare_score(const std::pair<int, int>& s1, const std::pair<int, int>& s2)
{
	return (s1.first > s2.first);
}

bool	compare_score_reverse(const std::pair<int, int>& s1, const std::pair<int, int>& s2)
{
	return (s1.first < s2.first);
}

int		minimax(State state, int limit, std::deque<int> past_scores, int depth, int alpha, int beta)
{
	static int node_count = 0;
	static int tactics_pruned = 0;
	static int a_b_pruned = 0;

	if (depth == 0)
	{
		tactics_pruned = 0;
		node_count = 0;
		a_b_pruned = 0;
	}
	node_count += 1;
	// std::cout << "\n\nmove: " << state.last_move / BOARD_WIDTH << ", " << state.last_move % BOARD_WIDTH << std::endl;
	// std::cout << "depth: " << depth << std::endl;
	// state.print();

	bool	maximizer = (state.player == WHITE);

	if (state.free_threes == 2)
	{
		return ILLEGAL;
	}


	past_scores.push_front(state.score);

	int	start_score;
	if (maximizer)
		start_score = INT32_MIN;
	else
		start_score = INT32_MAX;

	if (past_scores.size() > TACTICS_LEN)
	{
	 	start_score = past_scores.back();
		past_scores.pop_back();
	}


	if (state.game_win)
	{
		return state.score;
	}
	if (depth == limit)
		return (state.score);

	int eval;
	int best_move = -12;

	std::pair<int, int>	babies[200]; 		// <Score, state_index>
	State				babie_states[200];

	int counter = 0;

	if (maximizer)
	{
		if (past_scores.size() == TACTICS_LEN and start_score > state.score)
		{
			tactics_pruned += 1;
			return state.score;
		}
		int maxEval = INT32_MIN;
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (state.live_board.test(c))
			{
				babie_states[counter] = state.make_baby_from_coord(c);
				babies[counter] = std::pair<int, int>(babie_states[counter].score, counter);
				counter += 1;
				if (counter == 200)
					break;
			}
			std::sort(babies, babies + counter, compare_score);
		}
		// std::max(10.0, (1.0 - float(depth) / float(limit)) * counter)
		for(int i = 0; i < counter; i++)
		{
			eval = minimax(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				// std::cout << "eval: " << eval << " maxeval: " << maxEval << std::endl;
				if (eval > maxEval)
				{
					// std::cout << "FOUND BETTER MOVE: " << babies[i].second << " eval: " << eval << std::endl;
					best_move = babie_states[babies[i].second].last_move;
					maxEval = eval;
					// std::cout << "best_move: " << best_move << std::endl;
				}
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
				{
					a_b_pruned += 1;
					break;
				}
			}
		}
		if (depth == 0)
		{
			// std::cout << "NODES EXPLORED:   " << node_count << std::endl;
			// std::cout << "TACTICS PRUNED:   " << tactics_pruned << std::endl;
			// std::cout << "A_B PRUNED:       " << a_b_pruned << std::endl;
			return best_move;
		}
		else
			return (maxEval);
	}
	else
	{
		if (past_scores.size() == TACTICS_LEN and start_score < state.score)
		{
			tactics_pruned += 1;
			return state.score;
		}
		int minEval = INT32_MAX;
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (state.live_board.test(c))
			{
				babie_states[counter] = state.make_baby_from_coord(c);
				babies[counter] = std::pair<int, int>(babie_states[counter].score, counter);
				counter += 1;
				if (counter == 200)
					break;
			}
			std::sort(babies, babies + counter, compare_score_reverse); 

		}
		for(int i = 0; i < counter; i++)
		{
			eval = minimax(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				if (eval < minEval)
				{
					// std::cout << "FOUND BETTER MOVE: " << babies[i].second << " eval: " << eval << std::endl;
					best_move = babie_states[babies[i].second].last_move;
					minEval = eval;
				}
				beta = std::min(beta, eval);
				if (beta <= alpha)
				{
					a_b_pruned += 1;
					break;
				}
			}
		}
		if (depth == 0)
		{
			// std::cout << "NODES EXPLORED:   " << node_count << std::endl;
			// std::cout << "TACTICS PRUNED:   " << tactics_pruned << std::endl;
			// std::cout << "A_B PRUNED:       " << a_b_pruned << std::endl;
			return best_move;
		}
		else
			return (minEval);
	}
}