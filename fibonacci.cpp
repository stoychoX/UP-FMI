//linear solution, way faster:
size_t fib(size_t n) {
	size_t result = 1;
	size_t temp = 1;
	size_t temp1 = 1;

	for (int i = 2; i < n; i++) {
		result = temp1 + temp;
		temp1 = temp;
		temp = result;
	}

	return result;
}

//recursive solution, slow
size_t fibs(size_t n) {
	if (n == 1 || n == 2)
		return 1;
	return fibs(n - 1) + fibs(n - 2);
}
