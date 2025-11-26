#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>
#include <vector>

#ifndef N
#define N 7
#endif

using State = std::bitset<N * N>;

std::vector<State> moves;
std::vector<uint> largest_bits;

void print(State state) {
	for (uint i = 0; i < N; i++) {
		for (uint j = 0; j < N; j++) {
			std::cout << (state[N * i + j]? 'O': '_');
		}
		std::cout << '\n';
	}
	std::cout << "-------------------------\n";
}

std::vector<State> gen_moves() {
	std::vector<State> result;
	for (uint len = 2; len <= N; len++) {
		for (uint i = 0; i + len <= N; i++) {
			for (uint j = 0; j + len <= N; j++) {
				State move(0);
				for (uint di = 0; di < len; di++) {
					for (uint dj = 0; dj < len; dj++) {
						move.set(N * (i + di) + (j + dj));
					}
				}
				result.push_back(move);
			}
		}
	}
	return result;
}

bool solve(State state, uint move_ptr, uint moves_left) {
	if (move_ptr + moves_left > moves.size()) {
		return false;
	}
	if (moves_left == 0) {
		// TODO: backtrack
		return state.none();
	}

	if (largest_bits[move_ptr] != largest_bits[move_ptr + 1]) {
		// Forced move
		if (state[largest_bits[move_ptr]]) {
			state ^= moves[move_ptr];
			for (int i = largest_bits[move_ptr] - 1; i > largest_bits[move_ptr + 1]; i--) {
				if (state[i]) {
					return false;
				}
			}
			if (solve(state, move_ptr + 1, moves_left - 1)) {
				print(moves[move_ptr]);
				return true;
			}
			return false;
		}
		else {
			for (int i = largest_bits[move_ptr] - 1; i > largest_bits[move_ptr + 1]; i--) {
				if (state[i]) {
					return false;
				}
			}
			return solve(state, move_ptr + 1, moves_left);
		}
	}

	if (solve(state ^ moves[move_ptr], move_ptr + 1, moves_left - 1)) {
		print(moves[move_ptr]);
		return true;
	}
	return solve(state, move_ptr + 1, moves_left);
}

int main() {
	moves = gen_moves();
	std::sort(moves.begin(), moves.end(), [](State a, State b) {
			return a.to_string() > b.to_string();
			});

	largest_bits.resize(moves.size() + 1);
	for (uint i = 0; i < moves.size(); i++) {
		for (int bit = N * N; bit >= 0; bit --) {
			if (moves[i][bit]) {
				largest_bits[i] = bit;
				break;
			}
		}
	}
	largest_bits[moves.size()] = 0;

	State problem;

	uint n_moves;
	std::cin >> n_moves;

	for (uint i = 0; i < N * N; i++) {
		char ch;
		std::cin >> ch;
		if (ch == 'O') {
			problem.set(i);
		}
	}
	solve(problem, 0, n_moves);
}
