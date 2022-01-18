#include<iostream>
#include<cstring>
#pragma warning (disable:4996) //no errors(strcat)

const int STR_MAX_LEN = 100;

bool isOperator(const char& c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '=';
}

int calculate(const char* str) {
	int firstNumber = 0;
	int secondNumber = 0;

	bool firstNumInput = true;

	int strSize = strlen(str);

	char prevSign;

	for (int i = 0; i < strSize; i++) {
		if (!isOperator(str[i])) {
			if (firstNumInput) {
				firstNumber *= 10;
				firstNumber += str[i] - '0';
			}
			else {
				secondNumber *= 10;
				secondNumber += str[i] - '0';
			}
		}
		else {
			if (firstNumInput) {
				firstNumInput = false;
			}
			else {
				switch (prevSign){
				case '+':
					firstNumber = firstNumber + secondNumber;
					secondNumber = 0;
					break;
				case '-':
					firstNumber = firstNumber - secondNumber;
					secondNumber = 0;
					break;
				case '*':
					firstNumber = firstNumber * secondNumber;
					secondNumber = 0;
					break;
				case '/':
					firstNumber = firstNumber / secondNumber;
					secondNumber = 0;
					break;
				default:
					std::cout << "Invalid operator!";
					return -1;
					break;
				}
			}
			prevSign = str[i];
		}
	}
	return firstNumber;
}

int main() {
	char str[STR_MAX_LEN];
	
	std::cin.getline(str, STR_MAX_LEN, '=');

	// Adds equals at the end
	strcat(str, "=");

	std::cout << calculate(str);
}