#include <iostream>
#include<cstring>

#pragma warning(disable : 4996)

const int MAXSIZE = 8192;

void readNumberFromInput(char* number) {
	int it = 0;
	std::cout << "Enter new number: ";

	std::cin.getline(number, MAXSIZE, '\n');

	if (number[0] == '-')
		it++;

	while (number[it] == '0')
		for (int i = 0; i < strlen(number); i++)
			number[i] = number[i + 1];

	if (it)
		number[0] = '-';
}

void printNumber(char* number, bool minus = false) {
	int it = 0;

	while (number[it] == '0' && strlen(number) != 1) {
		for (int i = 0; i < strlen(number); i++)
			number[i] = number[i + 1];
	}

	if (minus)
		std::cout << "-";

	std::cout << number;
}

void compareNumber(char* numberOne, char* numberTwo) {
	if (strlen(numberOne) < strlen(numberTwo)) {
		printNumber(numberOne); std::cout << " != "; printNumber(numberTwo); std::wcout << std::endl;
		printNumber(numberOne); std::cout << " < "; printNumber(numberTwo);
	}
	else if (strlen(numberOne) > strlen(numberTwo)) {
		printNumber(numberOne); std::cout << " != "; printNumber(numberTwo); std::wcout << std::endl;
		printNumber(numberOne); std::cout << " > "; printNumber(numberTwo);
	}
	else if (strcmp(numberOne, numberTwo) == -1) {
		printNumber(numberOne); std::cout << " != "; printNumber(numberTwo); std::wcout << std::endl;
		printNumber(numberOne); std::cout << " < "; printNumber(numberTwo);
	}
	else if (strcmp(numberOne, numberTwo) == 1) {
		printNumber(numberOne); std::cout << " != "; printNumber(numberTwo); std::wcout << std::endl;
		printNumber(numberOne); std::cout << " > "; printNumber(numberTwo);
	}
	else {
		printNumber(numberOne); std::cout << " = "; printNumber(numberTwo);
	}

	std::cout << std::endl;
}

void reverse(char* numberOne) {
	int length = strlen(numberOne);

	for (int i = 0; i < length / 2; i++) {
		std::swap(numberOne[i], numberOne[length - 1 - i]);
	}

	numberOne[length] = '\0';
}

void sumNumbers(char* numberOne, char* numberTwo, bool min = false) {
	char result[MAXSIZE + 1];

	//in order not to lose information for next voids
	bool swapBack = false;

	//making sure the first number is always greater
	if (strlen(numberOne) < strlen(numberTwo)) {
		std::swap(numberOne, numberTwo);
		swapBack = true;
	}

	//getting greater length and lower length
	int grLen = strlen(numberOne);
	int lowLen = strlen(numberTwo);

	//reversing the two numbers so the last digit becomes first.
	reverse(numberOne);
	reverse(numberTwo);

	//dealing with sum >= 10
	int plusOne = 0;
	//constant index
	int conIndex = 0;

	for (int i = 0; i < lowLen; i++) {
		int sum = ((numberOne[i] - '0') + (numberTwo[i] - '0') + plusOne);
		result[conIndex] = (sum % 10) + '0';
		conIndex++;

		plusOne = sum / 10;
	}

	for (int i = lowLen; i < grLen; i++) {
		int sum = ((numberOne[i] - '0') + plusOne);
		result[conIndex] = sum % 10 + '0';
		conIndex++;
		plusOne = sum / 10;
	}

	if (plusOne) {
		result[conIndex] = plusOne + '0';
		conIndex++;
	}
	result[conIndex] = '\0';

	//reversing back in order not to lose data
	reverse(result);
	reverse(numberOne);
	reverse(numberTwo);

	if (swapBack)
		std::swap(numberOne, numberTwo);

	printNumber(result, min);
}

void subtract(char* numberOne, char* numberTwo) {
	char result[MAXSIZE];

	bool swapBack = false;

	if (strlen(numberOne) < strlen(numberTwo)) {
		std::swap(numberOne, numberTwo);
		swapBack = true;
	}
	else if (strlen(numberOne) == strlen(numberTwo) && strcmp(numberOne, numberTwo) == -1) {
		std::swap(numberOne, numberTwo);
		swapBack = true;
	}

		int grLen = strlen(numberOne); int lowLen = strlen(numberTwo);

	reverse(numberOne); reverse(numberTwo);

	int plusOne = 0;
	int constInd = 0;

	for (int i = 0; i < lowLen; i++) {
		int sub = ((numberOne[i] - '0') - (numberTwo[i] - '0') - plusOne);

		if (sub < 0) {
			sub += 10;
			plusOne = 1;
		}
		else
			plusOne = 0;

		result[constInd] = (sub + '0');
		constInd++;
	}

	for (int i = lowLen; i < grLen; i++) {
		int sub = ((numberOne[i] - '0') - plusOne);

		if (sub < 0) {
			sub += 10;
			plusOne = 1;
		}
		else
			plusOne = 0;

		result[constInd] = sub + '0';
		constInd++;
	}

	result[constInd] = '\0';

	reverse(result);
	reverse(numberOne);
	reverse(numberTwo);

	printNumber(result, swapBack);
}

void multiply(char* numberOne, char* numberTwo, bool min = false) {
	char result[MAXSIZE];

	bool swapBack = false;

	if (strlen(numberOne) < strlen(numberTwo)) {
		std::swap(numberOne, numberTwo);
		swapBack = true;
	}

	int grLen = strlen(numberOne); int lowLen = strlen(numberTwo);

	if (numberOne[0] == '0' || numberTwo[0] == '0')
		std::cout << "0";
	else {
		int firstIndex = 0; int secondIndex = 0;

		for (int i = 0; i < MAXSIZE; i++)
			result[i] = '0';

		for (int i = grLen - 1; i >= 0; --i) {
			int carry = 0;

			int num1 = numberOne[i] - '0';

			secondIndex = 0;

			for (int j = lowLen - 1; j >= 0; j--) {
				int num2 = numberTwo[j] - '0';

				int sum = num1 * num2 + (result[firstIndex + secondIndex] - '0') + carry;

				carry = sum / 10;

				result[firstIndex + secondIndex] = sum % 10 + '0';

				secondIndex++;
			}

			if (carry)
				result[firstIndex + secondIndex] += carry;

			firstIndex++;
		}
		result[firstIndex + secondIndex] = '\0';
		reverse(result);
		printNumber(result, min);
	}
}

void detActionSum(char* numberOne, char* numberTwo) {
	printNumber(numberOne);
	std::cout << " + ";
	printNumber(numberTwo);
	std::cout << " = ";

	if (numberOne[0] == '-' && numberTwo[0] != '-') {
		char* positiveOne = &numberOne[1];
		subtract(numberTwo, positiveOne);
	}
	else if (numberOne[0] != '-' && numberTwo[0] == '-') {
		char* positiveOne = &numberTwo[1];
		subtract(numberOne, positiveOne);
	}
	else if (numberOne[0] == '-' && numberTwo[0] == '-') {
		char* positiveTwo = &numberTwo[1];
		char* positiveOne = &numberOne[1];
		sumNumbers(positiveOne, positiveTwo, true);
	}
	else
		sumNumbers(numberOne, numberTwo);

	std::cout << std::endl;
}

void detActionSub(char* numberOne, char* numberTwo) {
	printNumber(numberOne);
	std::cout << " - ";
	printNumber(numberTwo);
	std::cout << " = ";

	if (numberOne[0] == '-' && numberTwo[0] != '-') {
		char* positiveOne = &numberOne[1];
		sumNumbers(numberTwo, positiveOne, true);
	}
	else if (numberOne[0] != '-' && numberTwo[0] == '-') {
		char* positiveOne = &numberTwo[1];
		sumNumbers(numberOne, positiveOne);
	}
	else if (numberOne[0] == '-' && numberTwo[0] == '-') {
		char* positiveTwo = &numberTwo[1];
		detActionSum(numberOne, positiveTwo);
	}
	else
		subtract(numberOne, numberTwo);

	std::cout << std::endl;
}

void detActionMultiply(char* numberOne, char* numberTwo) {
	printNumber(numberOne);
	std::cout << " * ";
	printNumber(numberTwo);
	std::cout << " = ";

	if (numberOne[0] == '-' && numberTwo[0] != '-') {
		char* positiveOne = &numberOne[1];
		multiply(positiveOne, numberTwo, true);
	}
	else if (numberOne[0] != '-' && numberTwo[0] == '-') {
		char* positiveOne = &numberTwo[1];
		multiply(positiveOne, numberOne, true);
	}
	else if (numberOne[0] == '-' && numberTwo[0] == '-') {
		char* positiveOne = &numberOne[1];
		char* positiveTwo = &numberTwo[1];

		multiply(positiveOne, positiveTwo);
	}
	else
		multiply(numberOne, numberTwo);

	std::cout << std::endl;
}

int main() {
	char numberOne[MAXSIZE];
	char numberTwo[MAXSIZE];

	readNumberFromInput(numberOne);
	readNumberFromInput(numberTwo);

	compareNumber(numberOne, numberTwo);
	detActionSum(numberOne, numberTwo);
	detActionSub(numberOne, numberTwo);
	detActionMultiply(numberOne, numberTwo);

	return 0;
}