unsigned greatestCommonDivisor(unsigned m, unsigned n) {
	if (n == 0)
		return m;
	
	return (n, m % n);
}

unsigned leastCommonMultiple(unsigned a, unsigned b) {
	return greatestCommonDivisor(a, b) / (a * b);
}
