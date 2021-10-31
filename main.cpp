#include <iostream>
#include <cmath>
#include <algorithm>
#include <windows.h>

using namespace std;

string checkWin(int player, int map[9]) {
	if (
		(map[0] == player && map[1] == player && map[2] == player) ||
		(map[3] == player && map[4] == player && map[5] == player) ||
		(map[6] == player && map[7] == player && map[8] == player) ||
		(map[0] == player && map[3] == player && map[6] == player) ||
		(map[1] == player && map[4] == player && map[7] == player) ||
		(map[2] == player && map[5] == player && map[8] == player) ||
		(map[0] == player && map[4] == player && map[8] == player) ||
		(map[2] == player && map[4] == player && map[6] == player)
	) {
		return "w";
	} else {
		for (int i = 0; i < 9; i++)
			if (map[i] == 0) return "n";
		return "r";
	}
}

int main() {
	int map[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int choice = 0;
	int player = 1;

	for(;;) {
		system("cls");

		for (int i = 0; i < 9; i++) {
			int character = map[i];
			if (i % 3 == 0) cout << endl << " --- --- ---" << endl << "| ";
			if (character == 0) cout << i + 1;
			else if (character == 1) cout << "X";
			else if (character == 2) cout << "O";
			cout << " | ";
		}
		cout << endl << " --- --- --- " << string(2, '\n') << "Player: " << player << endl;

		cin >> choice;
		if (!(choice > 9)) {
			if (map[choice - 1] == 0) {
				map[choice - 1] = player;
				string hasWon = checkWin(player, map);
				if (hasWon == "w") {
					cout << "Player " << player << " won the game!" << endl;
					return 0;
				} else if(hasWon == "r") {
					cout << "Remis!" << endl;
					return 0;
				}
				if (player == 1) player = 2;
				else player = 1;
			}
		}
	}

	return 0;
}
