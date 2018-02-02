// 19012018.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h> 
#include "iostream"
#include "math.h"
#include <time.h>
#include "vector"
#include <fstream>

using namespace std;
const int boardSize = 9;
int board[boardSize][boardSize];
int partialBoard[boardSize][boardSize];
int hold;
int quadSize = pow(boardSize, 0.5);
int difficulty;

void print_board(int board[][boardSize]) {
	for (int y = 0; y < boardSize; y++) {
		if (y % quadSize == 0) {
			for (int i = 0; i < (boardSize*2)+(boardSize/quadSize)+2; i++)
				cout << "-";
			cout << endl;
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
	for (int i = 0; i < (boardSize * 2) + (boardSize / quadSize) + 2; i++)
		cout << "-";
	cout << endl;
}

void board_clear(int board[][boardSize]) {
	for (int y = 0; y < boardSize; y++) {
		for (int x = 0; x < boardSize; x++) {
			board[y][x] = 0;
		}
	}
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
	while (placed < difficulty) {
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

bool findUnassingnedLocation(int board[][boardSize], int &x, int &y) {
	for (x = 0; x < boardSize; x++) {
		for (y = 0; y < boardSize; y++) {
			if (board[y][x] == 0) {
				return true;
			}
		}
	}
	return false;
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
				done = true;
			}
		}
		if (!done) {
			break;
		}

	}
}

bool backtrack(int board[][boardSize]) {
	int x = 0;
	int y = 0;
	int temp;
	if (!findUnassingnedLocation(board, x, y)) {
		return true;
	}
	for (int i = 1; i <= 9; i++) {
		if (valid_move(board, x, y, i)) {
			board[y][x] = i;
			//print_board(board);
			//cin >> temp;


			if (backtrack(board)) {
				return true;
			}
			board[y][x] = 0;
		}
	}
	return false;
}

void to_file(int board[][boardSize]) {
	ofstream myfile;
	myfile.open("Valid-Boards-9.txt", ios_base::app);
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			myfile << board[y][x];
		}
		//myfile << endl;
	}
	//myfile << "," << x << "," << y << "," << value << endl;
	myfile << endl;
	myfile.close();
}

void generate_training_data(int board[][boardSize]) {
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
						//to_file(board, x, y, avalible.at(0));
						board[y][x] = avalible.at(0);
						valid.push_back(board[y][x]);
						
					}
				}
			}
		}
		for (int i = 0; i < valid.size(); i++) {
			if (valid.at(i) == 1) {
				done = true;
			}
		}
		if (!done) {
			break;
		}

	}
}

void copy_board(int board[][boardSize], int partialBoard[][boardSize]) {
	for (int y = 0; y < boardSize; y++) {
		for (int x = 0; x < boardSize; x++) {
			partialBoard[y][x] = board[y][x];
		}
	}
}

int main(){
	int temp;
	srand(time(NULL));
	difficulty = 30;
	for (int i = 0; i < 1000; i++){
		int count = 1;
		do{	
			board_clear(board);
			board_clear(partialBoard);
			setup_board(board);
			copy_board(board, partialBoard);
			backtrack(board);
			//solve(board);
			count++;
		} while (!finished(board));
		cout << count << ", " << i << endl;
		//print_board(partialBoard);
		//print_board(board);
		//solve(partialBoard);
		//generate_training_data(partialBoard);
		to_file(partialBoard);
		
	}
	cout << "finished" << endl;
	cin >> hold;
	return 0;
}