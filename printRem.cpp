#include<iostream>
#include<cmath>

int occurs(const int* arr, int length, int argument) {
	for (size_t i = 0; i < length; i++)
		if (arr[i] == argument)
			return i;

	return -1;
}

void printRem(int number, int div) {
	if (!div) { std::cout << "Can't divide by zero\n"; return; }
	if(!number) { std::cout << "0\n"; return; }

	const int ACCURACY = 20;
	int helper[ACCURACY];
	double result = 0;
	double eps = 0.000000000001; //added to handle 10 / 3 issue, and more of this kind

	for (int i = 0; i < ACCURACY; i++) {
		result += (number / div) / pow(10, i) + eps;
		number = number % div;
		number *= 10;

		if (number / div == 0 && number % div == 0) {
			std::cout << result << '\n';
			return;
		}

		int occuranceInd = occurs(helper, i, number);

		if (occuranceInd == -1)   
			helper[i] = number;
		else {
			long long unsigned int periodPart = 0;
			double resultWholePart = 0;

			//Added to handle cases like 0.0(3), as the zero in 0(3) couldn't be remembered in datatype.
			int zeroesWhole = 0;
			int zeroesPeriod = 0;

			for (int i = 0; i < occuranceInd + 1; i++) {
				resultWholePart += (int)result;
				if (i != 0 && resultWholePart == 0)
					++zeroesWhole;
				result -= (int)result;
				result *= 10;
			}

			for (int j = 0; j < i - zeroesWhole; j++) {
				periodPart *= 10;
				if (j > 0 && periodPart == 0)
					++zeroesPeriod;
				periodPart += (int)result;
				result -= (int)result;
				result *= 10;
			}

			std::cout << resultWholePart << ".";

			for (int j = 0; j < zeroesWhole; j++)
				std::cout << "0";

			std::cout << "(";

			for (int j = 0; j < zeroesPeriod; j++)
				std::cout << "0";
			std::cout << periodPart << ")\n";
			return;
		}
	}
	std::cout << result << '\n';
}

int main() {
	//not enough tests yet!
	printRem(0, 30);
	printRem(1, 30);
	printRem(1, 0);
	printRem(17889, 17);
	printRem(10, 4);
	printRem(144996, 13);
	printRem(14, 13);
	printRem(10, 3);
}
