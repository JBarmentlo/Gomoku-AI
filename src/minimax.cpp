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

int		init_past_score(std::deque<int> &past_scores, int state_score, bool maximizer)
{
	past_scores.push_front(state_score);
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
	return start_score;
}

void	fill_baby_tables(std::pair<int, int>* babies , State* babie_states, State &state, int &counter)
{
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
	}
}

int		minimax(State state, int limit, std::deque<int> past_scores, int depth, int alpha, int beta)
{
	bool				maximizer = (state.player == WHITE);
	int 				best_move = -12;
	int					counter   = 0;
	int 				eval;
	int					start_score;
	std::pair<int, int>	babies[200]; 		// <Score, state_index>
	State				babie_states[200];
	int					bestEval;

	if (state.free_threes == 2)
		return ILLEGAL;
	if (state.game_win)
		return state.score;
	if (depth == limit)
		return (state.score);

	start_score = init_past_score(past_scores, state.score, maximizer);
	if (past_scores.size() == TACTICS_LEN and ((maximizer && (start_score > state.score)) || ((!maximizer) && (start_score < state.score))))
		return state.score;

	fill_baby_tables(babies, babie_states, state, counter);

	if (maximizer)
	{
		bestEval = INT32_MIN;
		std::sort(babies, babies + counter, compare_score);
		for(int i = 0; i < counter; i++)
		{
			eval = minimax(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				if (eval > bestEval)
				{
					best_move = babie_states[babies[i].second].last_move;
					bestEval = eval;
				}
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		if (depth == 0)
		{
			return best_move;
		}
		else
			return (bestEval);
	}
	else
	{
		bestEval = INT32_MAX;

		std::sort(babies, babies + counter, compare_score_reverse); 
		for(int i = 0; i < counter; i++)
		{
			eval = minimax(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				if (eval < bestEval)
				{
					best_move = babie_states[babies[i].second].last_move;
					bestEval = eval;
				}
				beta = std::min(beta, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
	}
	if (depth == 0)
	{
		return best_move;
	}
	else
		return (bestEval);
}

#define BEAM_K 7
int		minimax_beam(State state, int limit, int depth, int alpha, int beta)
{
	bool	maximizer = (state.player == WHITE);

	if (state.free_threes == 2)
	{
		return ILLEGAL;
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
	// int	skipper = 0;
	if (maximizer)
	{
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
		for(int i = 0; i < BEAM_K; i++)
		{
			eval = minimax_beam(babie_states[babies[i].second], limit, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				if (eval > maxEval)
				{
					best_move = babie_states[babies[i].second].last_move;
					maxEval = eval;
				}
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		if (depth == 0)
		{
			return best_move;
		}
		else
			return (maxEval);
	}
	else
	{
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
		for(int i = 0; i < BEAM_K; i++)
		{
			eval = minimax_beam(babie_states[babies[i].second], limit, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				if (eval < minEval)
				{
					best_move = babie_states[babies[i].second].last_move;
					minEval = eval;
				}
				beta = std::min(beta, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		if (depth == 0)
		{
			return best_move;
		}
		else
			return (minEval);
	}
}







#include "thread_pool.hpp"


template<typename R>
  bool is_ready(std::future<R> const& f)
  { return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }


int		minimax_fred(State state, int limit, std::deque<int> past_scores, int depth, int alpha, int beta)
{
	bool				maximizer		= (state.player == WHITE);
	int 				best_move 		= -12;
	int 				counter  		= 0;
	int 				eval;
	int 				start_score 	= init_past_score(past_scores, state.score, maximizer);
	int					bestEval;
	std::pair<int, int>	babies[200]; 		// <Score, state_index>
	State				babie_states[200];


	if (state.free_threes == 2)
		return ILLEGAL;
	if (state.game_win)
		return state.score;
	if (depth == limit)
		return (state.score);
	if (past_scores.size() == TACTICS_LEN and ((maximizer && (start_score > state.score)) || ((!maximizer) && (start_score < state.score))))
		return state.score;

	fill_baby_tables(babies, babie_states, state, counter);


	if (maximizer)
	{
		bestEval = INT32_MIN;
		std::sort(babies, babies + counter, compare_score);
		for(int i = 0; i < counter; i++)
		{
			eval = minimax_fred(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				if (eval > bestEval)
				{
					best_move = babie_states[babies[i].second].last_move;
					bestEval = eval;
				}
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
	}
	else
	{
		bestEval = INT32_MAX;
		std::sort(babies, babies + counter, compare_score_reverse); 
		for(int i = 0; i < counter; i++)
		{
			eval = minimax_fred(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
			if (eval != ILLEGAL)
			{
				if (eval < bestEval)
				{
					best_move = babie_states[babies[i].second].last_move;
					bestEval = eval;
				}
				beta = std::min(beta, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
	}
	if (depth == 0)
	{
		return best_move;
	}
	else
	{
		return (bestEval);
	}
}

int		minimax_fred_start(State state, int limit)
{
	int 							depth 	= 0;
	int 							alpha 	= BLACK_WIN;
	int 							beta 	= WHITE_WIN;
	bool							maximizer = (state.player == WHITE);
	int 							eval;
	int 							best_move = -12;
	int								counter = 0;
	bool							first 	= true;
	int								bestEval;
	thread_pool 					pool(std::thread::hardware_concurrency() - 1);
	std::queue<std::future<int>> 	fut_queue;
	std::queue<int>				 	move_queue;
	std::deque<int> 				past_scores;
	State							babie_states[200];
	std::pair<int, int>				babies[200]; 	// <Score, state_index>
	int								start_score = init_past_score(past_scores, state.score, maximizer);


	// std::cout << "Started thread pool with: " << pool.get_thread_count() << " threads." << std::endl;
	fill_baby_tables(babies, babie_states, state, counter);


	if (maximizer)
	{
		bestEval = INT32_MIN;
		std::sort(babies, babies + counter, compare_score);
		for(int i = 0; i < counter; i++)
		{
			if (first)
			{
				eval = minimax_fred(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
				if (eval != ILLEGAL)
				{
					first = false;
					if (eval > bestEval)
					{
						best_move = babie_states[babies[i].second].last_move;
						bestEval = eval;
					}
					alpha = std::max(alpha, eval);
					if (beta <= alpha)
					{
						break;
					}
				}
			}
			else
			{
				fut_queue.push(pool.submit(minimax_fred, babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta));
				move_queue.push(babie_states[babies[i].second].last_move);
			}
		}
		pool.wait_for_tasks();
		while(! fut_queue.empty())
		{
			eval = fut_queue.front().get();
			int tmp_move = move_queue.front();
			move_queue.pop();
			fut_queue.pop();
			if (eval != ILLEGAL)
			{
				if (eval > bestEval)
				{
					best_move = tmp_move;
					bestEval = eval;
				}
			}
		}
	}
	else
	{
		bestEval = INT32_MAX;
		std::sort(babies, babies + counter, compare_score_reverse); 
		for(int i = 0; i < counter; i++)
		{
			if (first)
			{
				eval = minimax_fred(babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta);
				if (eval != ILLEGAL)
				{
					first = false;
					if (eval < bestEval)
					{
						best_move = babie_states[babies[i].second].last_move;
						bestEval = eval;
					}
					beta = std::min(beta, eval);
					if (beta <= alpha)
					{
						break;
					}
				}
			}
			else
			{
				fut_queue.push(pool.submit(minimax_fred, babie_states[babies[i].second], limit, past_scores, depth + 1, alpha, beta));
				move_queue.push(babie_states[babies[i].second].last_move);
			}
		}
		pool.wait_for_tasks();
		while(!fut_queue.empty())
		{
			eval = fut_queue.front().get();
			int tmp_move = move_queue.front();
			move_queue.pop();
			fut_queue.pop();
			if (eval != ILLEGAL)
			{
				if (eval < bestEval)
				{
					best_move = tmp_move;
					bestEval = eval;
				}
			}
		}
	}
	if (depth == 0)
	{
		return (best_move);
	}
	else
	{
		return (bestEval);
	}
}