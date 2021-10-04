//more actions to be added soon

void rotate(char* result, int resMaxSize) {
	for (int i = 0; i < resMaxSize / 2; i++) {
		char temp = result[i];
		result[i] = result[resMaxSize - i - 1];
		result[resMaxSize - i - 1] = temp;
	}
}

const char* sumCharRepresentedNumber(const char* argOne, const char* argTwo) {
	int carry = 0;

	int resMinSize = strlen(argOne) < strlen(argTwo) ? strlen(argOne) : strlen(argTwo);
	int resMaxSize = strlen(argOne) > strlen(argTwo) ? strlen(argOne) : strlen(argTwo);

	const char* maxPtr;
	const char* minPtr;
	char* result = new char[resMaxSize + 1];

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

	rotate(result, resMaxSize);
	result[resMaxSize + !!(carry)] = '\0';

	return result;
}
