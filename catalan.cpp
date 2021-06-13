size_t catalan(unsigned int n) {

	size_t* catalan = new size_t[n + 1];

	catalan[0] = catalan[1] = 1;

	for (size_t i = 2; i <= n; i++) {
		catalan[i] = 0;
		for (size_t j = 0; j < i; j++)
			catalan[i] += catalan[j] * catalan[i - j - 1];
	}

	return catalan[n];
}