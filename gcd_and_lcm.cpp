//using recursive version of Eucledian algorithm
unsigned greatestCommonDivisor(unsigned m, unsigned n) {
	if (n == 0)
		return m;
	
	return (n, m % n);
}

//gcd(a, b) * lcm(a, b) = a * b where a and b are POSITIVE INTEGERS
unsigned leastCommonMultiple(unsigned a, unsigned b) {
	return greatestCommonDivisor(a, b) / (a * b);
}
