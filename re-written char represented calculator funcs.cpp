//more actions to be added soon

void rotate(char* result, int resMaxSize) {
	for (int i = 0; i < resMaxSize / 2; i++) {
		char temp = result[i];
		result[i] = result[resMaxSize - i - 1];
		result[resMaxSize - i - 1] = temp;
	}
}

char* removeFrontZero(char* toRemove) {
	char* result = new char[strlen(toRemove)];
	int size = strlen(toRemove);
	for (int i = 0; i < size; i++)
		result[i] = toRemove[i + 1];
	delete[] toRemove;
	return result;
}

char* sumCharRepresentedNumber(const char* argOne, const char* argTwo) {
	int carry = 0;

	int resMinSize = strlen(argOne) < strlen(argTwo) ? strlen(argOne) : strlen(argTwo);
	int resMaxSize = strlen(argOne) > strlen(argTwo) ? strlen(argOne) : strlen(argTwo);

	const char* maxPtr;
	const char* minPtr;
	char* result = new char[resMaxSize + 2];

	if (resMaxSize == strlen(argOne)) { maxPtr = argOne; minPtr = argTwo; }
	else { maxPtr = argTwo; minPtr = argOne; }

	for (int i = 0; i < resMinSize; i++) {
		int number = (minPtr[resMinSize - i - 1] - '0') + //first digit fo first number
			(maxPtr[resMaxSize - i - 1] - '0') //second digit of second number
			+ carry;

		carry = number / 10;
		result[i] = number % 10 + '0';
	}

	for (int i = resMinSize; i < resMaxSize; i++) {
		int number = ((maxPtr[resMaxSize - i - 1]) - '0') //next digit from the greatest number
			+ carry;

		carry = number / 10;
		result[i] = number % 10 + '0';
	}

	if (carry)
		result[resMaxSize] = carry + '0';

	rotate(result, resMaxSize + !!(carry));
	result[resMaxSize + !!(carry)] = '\0';

	return result;
}

//argOne - argTwo = result;
const char* subtractCharNumber(const char* argOne, const char* argTwo) {
	int carry = 0;

	int minSize = strlen(argOne) < strlen(argTwo) ? strlen(argOne) : strlen(argTwo);
	int maxSize = strlen(argOne) > strlen(argTwo) ? strlen(argOne) : strlen(argTwo);

	const char* minArg = strlen(argOne) < strlen(argTwo) ? argOne : argTwo;
	const char* maxArg = strlen(argOne) > strlen(argTwo) ? argOne : argTwo;

	if (minSize == maxSize) { maxArg = argOne; minArg = argTwo; }

	char* result = new char[maxSize + 1];

	for (int i = 0; i < minSize; i++) {
		int number = (maxArg[maxSize - i - 1] - '0' - carry) - (minArg[minSize - i - 1] - '0');
		if (number < 0) { number += 10; carry = 1; }
		else carry = 0;
		result[i] = number % 10 + '0';
	}

	for (int i = minSize; i < maxSize; i++) {
		int number = maxArg[maxSize - i - 1] - '0' - carry;
		if (number < 0) { number += 10; carry = 1; }
		else carry = 0;
		result[i] = number % 10 + '0';
	}

	rotate(result, maxSize);

	result[maxSize + !!(carry)] = '\0';
	while (result[0] == '0')
		result = removeFrontZero(result);

	if (maxSize != strlen(argOne)) {
		int size = strlen(result);
		char* nResult = new char[size + 1];
		nResult[0] = '-';
		for (int i = 0; i <= size; i++)
			nResult[i + 1] = result[i];
		delete[] result;
		return nResult;
	}
	return result;
}

const char* multiplyCharNumbers(const char* argOne, const char* argTwo) {
	int carry = 0;
	int rNum = 0;

	int lenOne = strlen(argOne);
	int lenTwo = strlen(argTwo);

	char** results = new char* [lenOne];

	for (int i = 0; i < lenOne; i++)
		results[i] = new char[lenTwo + lenOne + 1];

	for (int i = 0; i < lenOne; i++) {
		int firstNumber = argOne[lenOne - i - 1] - '0';
		carry = 0;
		for (int j = 0; j < i; j++)
			results[i][j] = '0';

		for (int j = 0; j < lenTwo; j++) {
			int secondNumber = argTwo[lenTwo - j - 1] - '0';
			rNum = firstNumber * secondNumber + carry;
			carry = rNum / 10;
			results[i][j + i] = rNum % 10 + '0';
		}

		if (carry)
			results[i][lenTwo + i] = carry + '0';

		results[i][lenTwo + i + !!(carry)] = '\0';
	}

	for (int i = 0; i < lenOne; i++) rotate(results[i], strlen(results[i]));

	char* result = new char[2];
	result[0] = '0';
	result[1] = '\0';

	for (int i = 0; i < lenOne; i++) result = sumCharRepresentedNumber(result, results[i]);

	for (int i = 0; i < lenOne; i++) delete[] results[i];
	delete[] results;

	return result;
}
