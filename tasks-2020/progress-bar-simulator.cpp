#include <iostream>
#include <thread>
#include <chrono>

const char LEFT_SYMB = '<';
const char RIGHT_SYMB = '>';
const char DEF_FILL = '#';
const char DEF_EMPTY = '-';
const int MAX_LEN_BAR = 1026;
const int LENGTH = 100;

void initBar(char* bar, int len, char left, char right, char fill) {
	bar[0] = left;
	bar[len] = right;
	for (int i = 0; i < len - 1; i++)
		bar[i] = fill;
}

void printBar(char* bar, int len, int speed, char left, char right, bool perc = false) {
	std::cout << left;
	int info = 0;
	auto start = std::chrono::steady_clock::now();
	for (int i = 1; i < len - 1; i++) {
		std::cout << bar[i];
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		if (bar[i] == DEF_FILL && bar[i + 1] == DEF_EMPTY) {
			if (perc) {
				int res = ceill((float)(i) / (float)(len - 1) * 100);
				std::cout << res << "%";
			}
			auto end = std::chrono::steady_clock::now();
			info = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		}
	}
	std::cout << right;
	std::cout << "\nExecution time: " << info << " second(s)";
}

void fillBar(char* bar, int border, char fill) {
	for (int i = 1; i < border+1; i++)
		bar[i] = fill;
}

void drawBar(char* bar, float currentProgress,int speed, bool perc = false, int length = 100, char leftSymb = LEFT_SYMB, char rightSymb = RIGHT_SYMB, char fillSymb = DEF_FILL, char emptySymb = DEF_EMPTY) {
	if (currentProgress > 1 || currentProgress < 0)
		std::cout << "Can't display more than 100%";
	else if (length > 1024)
		std::cout << "Can't display such bar.";
	else {
		length += 2;
		initBar(bar, length, leftSymb, rightSymb, emptySymb);

		float borderF = (length - 2) * currentProgress;

		int border = borderF;

		fillBar(bar, border, fillSymb);

		printBar(bar, length, speed, leftSymb, rightSymb, perc);
	}
}

void validate(int& number) {
	bool errorMessage = false;

	do {
		if (errorMessage)
			std::cout << "Bad input. Please try again.";

		std::cin >> number;

		bool validateCharInput = !((bool)(std::cin));
		if (validateCharInput) {
			std::cout << "No symbols allowed\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}

		errorMessage = true;
	} while (number <= 0);
}

int main() {
	int seconds = 0;
	char bar[MAX_LEN_BAR];

	std::cout << "Enter seconds: ";
	validate(seconds);
	const float percentage = 0.74;
	float speed = 10*((float)seconds / percentage);
	//speed *= 10;
	drawBar(bar, percentage, (int)speed, true, LENGTH);
}