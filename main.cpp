#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void renderMap(int*);
void setCell(int*, int, int);
void setRandomCell(int*, int);
int hasAnyoneWon(int*);
int possibleWinCell(int*);
int possibleLooseCell(int*);
vector<int> getAllFreeCells(int*);
bool isAnyCellFree(int*);
bool isCellTaken(int*, int);

int main() {
	int map[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int choice, player = 1;

	srand(time(NULL));

	for (;;) {
		system("cls");

		// Display map
		renderMap(map);

		// Player turn
		if (player == 1) {
			cout << "Player turn: ";
			cin >> choice;
			if (!(choice > 9) && !isCellTaken(map, choice - 1))
				map[choice - 1] = player;
			player = 2;
		}

		int playerThatWon = hasAnyoneWon(map);
		if (playerThatWon != -1) { system("cls"); renderMap(map); }
		if (playerThatWon == 0) { cout << "Remis"; }
		else if (playerThatWon == 1) { cout << "Player has won the game!"; }
		else if (playerThatWon == 2) { cout << "Computer has won the game!"; }
		if (playerThatWon != -1) { return 0; }

		// Computer turn
		if (player == 2) {
			int possibleWin = possibleWinCell(map);
			int possibleLoose = possibleLooseCell(map);
			if (possibleWin == -1) {
				if (possibleLoose == -1) setRandomCell(map, 2);
				else setCell(map, possibleLoose, 2);
			} else setCell(map, possibleWin, 2);

			cout << "Computer is thinking...\n";
			Sleep(200);
			player = 1;
		}

		playerThatWon = hasAnyoneWon(map);
		if (playerThatWon != -1) { system("cls"); renderMap(map); }
		if (playerThatWon == 0) { cout << "Remis"; }
		else if (playerThatWon == 1) { cout << "Player has won the game!"; }
		else if (playerThatWon == 2) { cout << "Computer has won the game!"; }
		if (playerThatWon != -1) { return 0; }
	}

	return 0;
}

void renderMap(int map[9]) {
	string linia = "\n --- --- --- \n";
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0) cout << linia << "| ";
		if (map[i] == 0) cout << i + 1;
		else if (map[i] == 1) cout << "X";
		else if (map[i] == 2) cout << "O";
		else cout << "?";
		cout << " | ";
	}
	cout << linia;
}

void setCell(int map[9], int cell, int player) { map[cell] = player; }

void setRandomCell(int map[9], int player) {
	int cell = rand() % 8 + 0;
	if (!isCellTaken(map, cell)) setCell(map, cell, player);
	else if (isAnyCellFree(map)) {
		for (int i = 0; i < 9; i++)
			if (!isCellTaken(map, i)) {
				setCell(map, i, player);
				return;
			}
	}
}

vector<int> getAllFreeCells(int map[9]) {
	vector<int> freeCells;
	for (int i = 0; i < 9; i++) {
		if (!isCellTaken(map, i)) {
			freeCells.push_back(i);
		}
	}
	return freeCells;
}

bool isAnyCellFree(int map[9]) {
	for (int i = 0; i < 9; i++) {
		if (map[i] == 0) return true;
	}
	return false;
}

int hasAnyoneWon(int map[9]) {
	for (int i = 1; i <= 2; i++) {
		if (
			(map[0] == i && map[1] == i && map[2] == i) ||
			(map[3] == i && map[4] == i && map[5] == i) ||
			(map[6] == i && map[7] == i && map[8] == i) ||
			(map[0] == i && map[3] == i && map[6] == i) ||
			(map[1] == i && map[4] == i && map[7] == i) ||
			(map[2] == i && map[5] == i && map[8] == i) ||
			(map[2] == i && map[4] == i && map[6] == i) ||
			(map[0] == i && map[4] == i && map[8] == i)
		) {
			return i;
		}
	}
	if (isAnyCellFree(map)) return -1;
	return 0;
}

int possibleWinCell(int map[9]) {
	vector<int> freeCells = getAllFreeCells(map);
	cout << int(freeCells.size()) << '\n';
	for (int i = 0; i < int(freeCells.size()); i++) {
		int temp[9];
		copy(map, map + 9, begin(temp));
		setCell(temp, freeCells[i], 2);
		if (hasAnyoneWon(temp) == 2) {
			return freeCells[i];
		}
	}
	return -1;
}

int possibleLooseCell(int map[9]) {
	vector<int> freeCells = getAllFreeCells(map);
	for (int i = 0; i < int(freeCells.size()); i++) {
		int temp[9];
		copy(map, map + 9, begin(temp));
		setCell(temp, freeCells[i], 1);
		if (hasAnyoneWon(temp) == 1) {
			return freeCells[i];
		}
	}
	return -1;
}

bool isCellTaken(int map[9], int cell) {
	return map[cell] != 0;
}
