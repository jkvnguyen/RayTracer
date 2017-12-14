/*
 * RNG is from Pierre L'Ecuyer, "Good Parameter Sets for Combined Multiple
 * Recursive Random Number Generators", Operations Research, 47, 1 (1999),
 * 159-164.  The algorithm is MRG32k3a. It has a period of approx 2^191.
 *
 * Paper + code can be found at http://www.iro.umontreal.ca/~lecuyer/papers.html
 */

#define norm 2.328306549295728e-10
#define m1   4294967087.0
#define m2   4294944443.0
#define a12     1403580.0
#define a13n     810728.0
#define a21      527612.0
#define a23n    1370589.0
#define LOWER_THIRTY_BITS (0x3fffffffL)

static double  s10= 12345.0, s11= 12345.0, s12= 12345.0;
static double  s20= 12345.0, s21= 12345.0, s22= 12345.0;

/*
 * return a number betwen 0 and 1 (0-1)
 */
double
frandom()
{
	long   k;
	double p1, p2;

	/* Component 1 */
	p1 = a12 * s11 - a13n * s10;
	k = p1 / m1;   p1 -= k * m1;   if (p1 < 0.0) p1 += m1;
	s10 = s11;   s11 = s12;   s12 = p1;

	/* Component 2 */
	p2 = a21 * s22 - a23n * s20;
	k  = p2 / m2;  p2 -= k * m2;   if (p2 < 0.0) p2 += m2;
	s20 = s21;   s21 = s22;   s22 = p2;

	/* Combination */
	if (p1 <= p2) return ((p1 - p2 + m1) * norm);
	else return ((p1 - p2) * norm);
}

void
set_frandom(long seed)
{
	seed &= LOWER_THIRTY_BITS; /* ensure seed is always < m1, m2 */
	seed++;	/* seed can't be all 0s */
	s10= seed;
	s11= seed;
	s12= seed;
	s20= seed;
	s21= seed;
	s22= seed;
}
