// 19012018.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h> 
#include "iostream"
#include "math.h"
#include <time.h>
#include "vector"

using namespace std;
const int boardSize = 9;
int board[boardSize][boardSize];
int hold;
int quadSize = pow(boardSize, 0.5);

void print_board(int board[][boardSize]) {
	for (int y = 0; y < boardSize; y++) {
		if (y % quadSize == 0) {
			cout << "---------------------------" << endl;
		}
		cout << "|";
		for (int x = 0; x < boardSize; x++) {
			if (x % quadSize == 0) {
				cout << "|";
			}
			if (board[y][x] == 0) {
				cout << " " << "|";
			}
			else {
				cout << board[y][x] << "|";
			}


		}
		cout << "|" << endl;

	}
	cout << "---------------------------" << endl;
}

bool valid_move(int board[][boardSize], int _x, int _y, int num) {
	for (int y = 0; y < boardSize; y++) {
		if (board[y][_x] == num) {
			return false;
		}
	}
	for (int x = 0; x < boardSize; x++) {
		if (board[_y][x] == num) {
			return false;
		}
	}

	int quadX = _x / quadSize;
	int quadY = _y / quadSize;
	for (int y = quadY * quadSize; y < (quadY + 1) * quadSize; y++) {
		for (int x = quadX * quadSize; x < (quadX + 1) * quadSize; x++) {
			if (board[y][x] == num) {
				return false;
			}
		}
	}
	return true;
}

void setup_board(int board[][boardSize]) {
	int placed = 0;
	while (placed < 65) {
		int x = rand() % boardSize;
		int y = rand() % boardSize;
		int num = (rand() % boardSize) + 1;
		if (board[y][x] == 0 && valid_move(board, x, y, num) == 1) {
			board[y][x] = num;
			placed++;
		}
	}
}
bool finished(int board[][boardSize]) {
	for (int y = 0; y < boardSize; y++) {
		for (int x = 0; x < boardSize; x++) {
			if (board[y][x] == 0) {
				return false;
			}
		}
	}
	return true;
}

void solve(int board[][boardSize]) {
	bool done;
	vector<int> avalible;
	vector<int> valid;
	
	while (!finished(board)) {
		valid.clear();
		done = false;
		//print_board(board);
		//cin >> done;
		for (int y = 0; y < boardSize; y++) {
			for (int x = 0; x < boardSize; x++) {
				if (board[y][x] == 0) {
					avalible.clear();
					for (int i = 0; i < boardSize; i++)
					{
						if (valid_move(board, x, y, i + 1)) {
							avalible.push_back(i + 1);
						}
					}
					if (avalible.size() == 1) {
						board[y][x] = avalible.at(0);
						valid.push_back(board[y][x]);
					}
				}
			}
		}
		for (int i = 0; i < valid.size(); i++) {
			if (valid.at(i) == 1) {
				cout << valid.at(i) << endl;
				done = true;
			}
		}
		if (!done) {
			break;
		}
	}
}


int main()
{
	srand(time(NULL));
	int count = 0;
	while (!finished(board)) {
		setup_board(board);
		//print_board(board);
		solve(board);
		//print_board(board);
		cout << ++count << endl;
	}
	print_board(board);
	cout << "finished" << endl;
	cin >> hold;
	return 0;
}

