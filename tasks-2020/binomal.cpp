/*****************************************************
Returning the value of (n, k) BINOMIAL COEFFICIENT
******************************************************/

size_t Binomial(int n, int k) {
	if(n <= k || n <= 0 || k <= 0)
		return 1;
	
	size_t* pascalNthGrid = new size_t[++n];
	pascalNthGrid[0] = 1;
	
	int tempFirst = 0;
	int tempSecond = 0;

	for (int i = 1; i < n; i++) {
		pascalNthGrid[i] = pascalNthGrid[i - 1];

		for (int j = 1; j < i; j++) {
			if (!tempFirst) {
				tempFirst = pascalNthGrid[j - 1];
				tempSecond = pascalNthGrid[j];
			}
			else {
				tempFirst = tempSecond;
				tempSecond = pascalNthGrid[j];
			}
			pascalNthGrid[j] += tempFirst;
		}
		tempFirst = tempSecond = 0;
	}

	size_t result = pascalNthGrid[k];
	delete[] pascalNthGrid;

	return result;
}
