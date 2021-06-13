#include <iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>

const char DEF_FILL = '#';
const char DEF_MINE = '@';
const char DEF_MASK = '-';

const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;
const int CUST = 4;

bool winner(char**, int**, int, const int&, const int&);
bool gameover = false;

void goAgain();

void onStartUp() {
	system("title = MINE SWEEPER");

	std::cout << "Choose level:" << std::endl <<
		"1-Easy" << std::endl <<
		"2-Medium" << std::endl <<
		"3-Hard" << std::endl <<
		"4-Customize the field and the number of mines" << std::endl;
}

void validateNumber(int& userInput, int lowerBound, int higherBound) {
	bool err = false;

	std::cin >> userInput;
	
	while (userInput <= lowerBound || userInput >= higherBound) {
		std::cout << "Invalid Input!" << std::endl;

		bool textErr = ((bool)(std::cin));
		if (!textErr) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
			userInput = -1;
		}
		std::cin >> userInput;
	}
}

bool isMemberOfMinesArray(int** databaseMines, int x, int y, const int& heightOfDatabase) {
	for (int i = 0; i < heightOfDatabase; i++)
		if (databaseMines[i][0] == x && databaseMines[i][1] == y)
			return true;

	return false;
}

void initDatabaseForLocationOfMines(int** databaseMines, const int& amountOfMines) {
	for (int i = 0; i < amountOfMines; i++)
		for (int j = 0; j < 2; j++)
			databaseMines[i][j] = -1;
}

void getCoordinatesOfMines(int** minesLocationData, const int& amountOfMines, const int& length, const int& height) {
	for (int i = 0; i < amountOfMines; i++) {
		srand(time(NULL));
		int indexOne = rand() % length;
		int indexTwo = rand() % height;

		while (isMemberOfMinesArray(minesLocationData, indexOne, indexTwo, amountOfMines)) {
			indexOne = rand() % length;
			indexTwo = rand() % height;
		}
		minesLocationData[i][0] = indexOne;
		minesLocationData[i][1] = indexTwo;
	}
}

void initWithMines(char** gameboard, int** databaseOfMines, const int& minesCount, const int& length, const int& height) {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < length; j++) {
			if (isMemberOfMinesArray(databaseOfMines, i, j, minesCount))
				gameboard[i][j] = DEF_MINE;
			else
				gameboard[i][j] = DEF_MASK;
		}
}

void printBoard(char** gameboard, const int& length, const int& height, int locationOfFoundMineX = -1, int locationOfFoundMineY = -1) {
	system("CLS");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << " ";
	for (int n = 0; n < length; n++) {
		SetConsoleTextAttribute(hConsole, rand() % 14 + 1);
		if (n < 10)
			std::cout << "  " << n << " ";
		else
			std::cout << " " << n << " ";
	}
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << std::endl;

	for (int i = 0; i < height; i++) {
		std::cout.width(2);
		SetConsoleTextAttribute(hConsole, rand() % 14 + 1);
		std::cout << i << " ";
		SetConsoleTextAttribute(hConsole, 7);

		for (int j = 0; j < length; j++) {
			if (i == locationOfFoundMineX && j == locationOfFoundMineY) {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "@";
				SetConsoleTextAttribute(hConsole, 7);
				std::cout << " | ";
			}
			else if (gameboard[i][j] == DEF_MASK || gameboard[i][j] == DEF_MINE)
				std::cout << DEF_FILL << " | ";
			else if (gameboard[i][j] == '0')
				std::cout << " " << " | ";
			else {
				SetConsoleTextAttribute(hConsole, 6);
				std::cout << gameboard[i][j];
				SetConsoleTextAttribute(hConsole, 7);
				std::cout << " | ";
			}
		}
		std::cout << std::endl;
	}
}

bool isOpen(const char com[5]) {
	char open[5] = { 'o', 'p', 'e', 'n', '\0' };

	bool isFirst = strcmp(open, com);

	return !(isFirst);
}

bool isMark(const char com[5]) {
	char mask[5] = { 'm', 'a', 'r', 'k', '\0' };

	bool isSec = strcmp(mask, com);

	return !(isSec);
}

bool isValidMove(char** gameboard, char com[5], int X, int Y, const int len, const int height) {
	return !((X < 0) || (X >= height)) && !((Y < 0) || (Y >= len)) &&
		(isOpen(com) || isMark(com));
}

bool isMoveInBoundOfArray(const int& X, const int& Y, const int& len, const int& height) {
	return X >= 0 && X < height&& Y >= 0 && Y < len;
}

int cellWorth(char** gameboard, int** databaseOfMinesLocations, const int& amountOfMines, int x, int y, int len, int height) {
	int cellWorth = 0;

	if (gameboard[x][y] == DEF_MINE)
		return -1;

	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0)
				continue;

			if (isMoveInBoundOfArray(x + i, y + j, len, height) && isMemberOfMinesArray(databaseOfMinesLocations, x + i, y + j, amountOfMines))
				cellWorth++;
		}

	return cellWorth;
}

void getMove(char** gameboard, char com[5], int& x, int& y, const int len, const int height) {
	char open[5] = { 'o', 'p', 'e', 'n', '\0' };
	char mark[5] = { 'm', 'a', 'r', 'k', '\0' };

	int ind = 0;

	do {
		char c;
		std::cin.get(c);
		if (c == open[ind] || c == mark[ind]) {
			com[ind] = c;
			++ind;
		}
		else if ((int)c == 10 && ind != 4) {
			ind = 0;
			com[0] = '\0';
		}

		if (ind == 4) {
			com[ind] = '\0';
			if (isOpen(com) || isMark(com))
				break;
			else {
				ind = 0;
				com[0] = '\0';
			}
		}
	} while (true);

	std::cin >> x >> y;

	if (!isValidMove(gameboard, com, x, y, len, height)) {
		std::cout << "Invalid Input" << std::endl;
		x = -1; y = -1; com[0] = '\n';
		getMove(gameboard, com, x, y, len, height);
		return;
	}
}

void openCell(char** gameboard, int** databaseOfMinesLocations, int amountOfMines, int worth, int x, int y, int len, int heigth, bool alreadyMarked) {

	//try removing already marked later
	if (gameboard[x][y] == 'X' && alreadyMarked) {
		gameboard[x][y] = DEF_MASK;
		return;
	}

	//end of recursion:
	if (gameboard[x][y] != DEF_MASK && gameboard[x][y] != DEF_MINE)
		return;

	gameboard[x][y] = worth + '0';

	//start of recursion:
	if (worth == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (j == 1 && i == 1)
					continue;

				int newX = x + i - 1; int newY = y + j - 1;
				if (isMoveInBoundOfArray(newX, newY, len, heigth)) {
					int newWorth = cellWorth(gameboard, databaseOfMinesLocations, amountOfMines, newX, newY, len, heigth);
					openCell(gameboard, databaseOfMinesLocations, amountOfMines, newWorth, newX, newY, len, heigth, false);
				}
			}
		}
	}
}

void markCell(char** gameboard, int x, int y) {
	if (gameboard[x][y] == DEF_MASK || gameboard[x][y] == DEF_MINE)
		gameboard[x][y] = 'X';
}

void makeMove(char** gameboard, int** dataMines, int amountOfMines, const int len, const int height) {
	char com[5];

	int x; int y;

	std::cout << "Please enter a comand: open or mark!" << std::endl <<
		"Comand: ";


	//making move:
	getMove(gameboard, com, x, y, len, height);

	//getting value of cell:
	int val = cellWorth(gameboard, dataMines, amountOfMines, x, y, len, height);

	if (isOpen(com) && val != -1) {
		//try removing true!
		openCell(gameboard, dataMines, amountOfMines, val, x, y, len, height, true);
	}
	else if (isOpen(com) && cellWorth(gameboard, dataMines, amountOfMines, x, y, len, height) == -1) {
		printBoard(gameboard, len, height, x, y);
		gameover = true;
	}
	else if (isMark(com)) {
		markCell(gameboard, x, y);
	}
	else {
		std::cout << "Fatal error!";
	}

}

bool winner(char** gameboard, int** databaseOfMines, int amountOfMines, const int& len, const int& height) {
	for (int i = 0; i < amountOfMines; i++)
		if (gameboard[databaseOfMines[i][0]][databaseOfMines[i][1]] != 'X')
			return false;

	return true;
}

void play(int level) {
	int length = 0; int height = 0; int minesCount = 0;

	switch (level) {
	case EASY:
		length = 7; height = 7; minesCount = 6;
		break;
	case MEDIUM:
		length = 10; height = 10; minesCount = 25;
		break;
	case HARD:
		length = 15; height = 15; minesCount = 40;
		break;
	case CUST:
		system("cls");

		std::cout << "Enter length [5 < length < 50]: ";
		validateNumber(length, 5, 51);

		std::cout << "Enter height [5 < height < 50]: ";
		validateNumber(height, 5, 51);

		minesCount = 0.2 * length * height;
		break;
	}

	char** gameboard = new char* [height];

	for (int i = 0; i < length; i++)
		gameboard[i] = new char[length];

	int** minesLocationData = new int* [minesCount];

	for (int i = 0; i < minesCount; i++)
		minesLocationData[i] = new int[2];

	initDatabaseForLocationOfMines(minesLocationData, minesCount);

	getCoordinatesOfMines(minesLocationData, minesCount, length, height);

	initWithMines(gameboard, minesLocationData, minesCount, length, height);

	while (!gameover && !winner(gameboard, minesLocationData, minesCount, length, height)) {
		printBoard(gameboard, length, height);
		makeMove(gameboard, minesLocationData, minesCount, length, height);
	}

	for (int i = 0; i < minesCount; i++)
		delete[] minesLocationData[i];

	for (int i = 0; i < height; i++)
		delete[] gameboard[i];

	if (gameover)
		std::cout << "you lose :(";
	else
		std::cout << "you win :)";
}

void Create() {
	onStartUp();

	int mode = 0;
	validateNumber(mode, 0, 5);

	switch (mode) {
	case 1: play(EASY);
		break;
	case 2: play(MEDIUM);
		break;
	case 3: play(HARD);
		break;
	case 4: play(CUST);
		break;
	default:
		std::cout << "Fatal error.";
		break;
	}

	goAgain();
}

void goAgain() {
	int command;
	std::cout << "\nWanna go again?\n 1 restart \n 0 exit\n";
	validateNumber(command, -1, 2);
	switch (command)
	{
	case 1: system("cls"); gameover = false; Create(); break;
	case 0: exit(0);
	default:
		std::cout << "Fatal error! :(";
		break;
	}
}

int main() {
	Create();
}