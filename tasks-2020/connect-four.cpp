#include <iostream>

const int MAXLEN = 40;
const int MAXHEIGHT = 20;
const char _DEFCHAR = ' ';

bool wrongSwitch = false;

void printBoard(char matrix[][MAXLEN], int length, int height) {
	std::cout << "Board:\n";
	if (length < 10) {
		std::cout << " ";
		for (int i = 0; i < length; i++)
			if (i < 9)
				std::cout << i + 1 << " ";

		std::cout << std::endl;
	}

	for (int i = 0; i < height; i++) {
		for (int g = 0; g < length; g++) {
			std::cout << "|" << matrix[i][g];
		}
		std::cout << "|" << std::endl;
	}
}

void initGameboard(char matrix[][MAXLEN], int length, int height) {
	for (int i = 0; i < height; i++) {
		for (int g = 0; g < length; g++) {
			matrix[i][g] = _DEFCHAR;
		}
	}
}

void makeMove(char matrix[][MAXLEN], int length, int height, bool xTurn) {
	int table = 0;
	bool iRight = false;
	int iterate = height;

	do {
		if (iRight)
			std::cout << "Wrong move... Are you blind?" << std::endl;

		std::cout << "Enter your move: ";
		std::cin >> table;
		bool validation = !((bool)(std::cin));
		if (validation) {
			system("title = I've spent an solid hour trying to restrict symbol input.. Just because of people like you. No symbols allowed!!!");
			std::cin.clear();
			std::cin.ignore(255, '\n');
			wrongSwitch = true;
		}
		else
			system("title = Four in a row!");

		iRight = true;
	} while (table > length || table < 0);


	while (matrix[iterate][table - 1] != _DEFCHAR) {
		iterate--;

		if (iterate < 0) {
			wrongSwitch = true;
			break;
		}
	}

	if (xTurn)
		matrix[iterate][table - 1] = 'X';
	else
		matrix[iterate][table - 1] = 'O';
}

bool checkForWinner(char matrix[][MAXLEN], int length, int height) {
	//main diagonal
	for (int i = height - 1; i >= 3; i--) {
		for (int j = 0; j <= length - 3; j++) {
			bool eq = (matrix[i][j] == matrix[i - 1][j + 1]) &&
				(matrix[i - 2][j + 2] == matrix[i - 3][j + 3]) &&
				(matrix[i][j] == matrix[i - 3][j + 3]) &&
				(matrix[i][j] != _DEFCHAR);

			if (eq)
				return eq;
		}
	}

	//secondary diagonal:
	for (int i = height - 1; i >= 3; i--) {
		for (int j = length - 1; j >= 3; j--) {
			bool eq = (matrix[i][j] == matrix[i - 1][j - 1]) &&
				(matrix[i - 2][j - 2] == matrix[i - 3][j - 3]) &&
				(matrix[i][j] == matrix[i - 3][j - 3]) &&
				matrix[i][j] != _DEFCHAR;

			if (eq)
				return eq;
		}
	}

	//row:
	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= length - 4; ++j) {
			bool eq = (matrix[i][j] == matrix[i][j + 1]) &&
				(matrix[i][j + 2] == matrix[i][j + 3]) &&
				(matrix[i][j] == matrix[i][j + 3]) &&
				matrix[i][j] != _DEFCHAR;

			if (eq)
				return eq;
		}
	}
	//col:
	for (int i = 0; i <= height - 4; i++) {
		for (int j = 0; j < length; j++) {
			bool eq = (matrix[i][j] == matrix[i + 1][j]) &&
				(matrix[i + 2][j] == matrix[i + 3][j]) &&
				(matrix[i][j] == matrix[i + 3][j]) &&
				matrix[i][j] != _DEFCHAR;

			if (eq)
				return eq;
		}
	}

	return false;
}

bool checkForRemi(char matrix[][MAXLEN], int length, int height) {
	for (int i = 0; i < height; i++) {
		for (int g = 0; g < length; g++) {
			if (matrix[i][g] == _DEFCHAR)
				return false;
		}
	}
	return true;
}

int main() {
	system("title = Four in a row!");

	char gameboard[MAXHEIGHT][MAXLEN];
	int length = 0; int height = 0;
	bool xTurn = true;
	bool fInput = false;

	do {
		if (fInput)
			std::cout << std::endl
			<< "Wrong input! Please try again, buddy" << std::endl
			<< "and bear in mind that you have interval, going like" << std::endl <<
			"4 <= length <= 40 and 4 <= heigth <= 20!" << std::endl << std::endl;

		std::cout << "Enter length: ";
		std::cin >> length;
		bool validate = !((bool)(std::cin));
		if (!validate) {
			std::cout << "Enter heigth: ";
			std::cin >> height;
			bool secondValidatin = !((bool)(std::cin));
			if (secondValidatin) {
				std::cout << std::endl << "NO SYMBOLS ALLOWED!\n";
				std::cin.clear();
				std::cin.ignore(255, '\n');
				fInput = false;
			}
		}
		else {
			std::cout << std::endl << "No symbols allowed!";
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
		fInput = true;
	} while (length < 4 || height < 4 || length >MAXLEN || height > MAXHEIGHT);


	initGameboard(gameboard, length, height);
	printBoard(gameboard, length, height);

	while (!checkForWinner(gameboard, length, height) && !checkForRemi(gameboard, length, height)) {
		system("CLS");
		printBoard(gameboard, length, height);
		makeMove(gameboard, length, height, xTurn);

		if (!wrongSwitch)
			xTurn = !xTurn;
		else
			wrongSwitch = false;
	}

	system("CLS");
	printBoard(gameboard, length, height);
	std::cout << "Winner: ";

	if (checkForRemi(gameboard, length, height))
		std::cout << "Remi!";
	else if (xTurn)
		std::cout << 'O';
	else
		std::cout << 'X';

	return 0;
}