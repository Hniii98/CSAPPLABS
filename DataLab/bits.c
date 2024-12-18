/* 
 * CS:APP Data Lab 
 * 
 * <KunhuangZhu 752608928@qq.com>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
/* transfer problem into exploit Xor gate by using and gate and not gate */
	int result = ~(~(~x & y) & ~(x & ~y));
	return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/* implement tmin by shifting 1 with 31 times */
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	/* Use Tmax to construct 0x0 to detect and avoid 0xFFFFFFFF */
//  return !(~(1 << 31) ^ x);
	int result = ~(x + 1 + x); // construct 0xFFFFFFFF by using Tmax and reverse bits
	result = (result | !(x + 1)); // exclude 0xFFFFFFFF by !(x + 1), because it has same property
	return !result;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	/* detect symmertric difference by using mask 0xAAAAAAAA */
	int mask = 0xAA;
	int result; // should declare in front, otherwise dlc report comppilation error
	mask = mask + (mask << 8) +(mask << 16) + (mask << 24); // construct mask
	result  = !((x & mask) ^ mask);
  return result;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/* reverse every bit then plus one */
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	/* decompose inequlity into x-0x30 >=0 and 0x39-x >=0 and compute intersection */
	int TMin = 1 << 31;
	int lowerBound = !((x + ~0x30 + 1) & TMin);
	int upperBound = !((~x + 1 + 0x39) & TMin);
	int result = lowerBound & upperBound;
  return result;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/* use bitsign 0xFFFFFFFF、0x00000000 implement output and block */
	int logicSign = !!x; // any bit is one, logicsign equals True. Otherwise False. 
	int bitSign  = ~logicSign + 1; // True turn into bit sign 0xFF..FF. False into 0x0.
	int result = (bitSign & y) | (~bitSign & z); 
  return result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /* detect less or equal by sign bit */
    int sign = 1 << 31;
    int result = !((y +(~x + 1)) & sign); // fetch sign bit and calculate
  return result;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/* use the property of difference between the opposite of zero , TMin , and the others. */
	int bitUnion = (x | (~x + 1)); // x=0,-x=0; x=TMin,-x=TMin;x=the others, -x=-the others, compute their union by using | operator.
	int result = (bitUnion >> 31) + 1; //  use arithmetic right shift to detect 0x00000000.
  return result;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
	/* use bisection method to detect whether section exist at each time */
	int signBit = x >> 31;
	int exist16Bits, exist8Bits, exist4Bits, exist2Bits, exist1Bits; 
	int result;
	x = x ^ signBit; // use Xor operator to implement negation or maintain (x ^ 1 negation x ^ 0 maintain)

	exist16Bits =  !!(x >> 16) << 4; // Bisection, if high 16BitExist, exist16Bits = 1 << 4 = 16, otherwise 0.
	x = x >> exist16Bits; // if high 16bits exist, remove lower 16bits and keep detecting, otherwise don't shift.
	exist8Bits = !!(x >> 8) << 3;
	x = x >> exist8Bits;
	exist4Bits = !!(x >> 4) << 2;
	x = x >> exist4Bits;
	exist2Bits = !!(x >> 2) << 1;
	x = x >> exist2Bits;
	exist1Bits = !!(x >> 1) << 0;
	x = x >> exist1Bits;

	result = x + exist1Bits + exist2Bits + exist4Bits + exist8Bits + exist16Bits + 1; // finally we need msb bit to represent sign, so +1.
  return result;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	/* implement expression by manipulating exponent bits and fraction bits */
	unsigned expBits = (uf >> 23) & 0x000000FFu; 
	unsigned fracBits = uf & 0x007FFFFFu;

	if(expBits == 0xFF) return uf; // uf is NAN or infinite
    else if(expBits == 0x00 && fracBits == 0x00) return uf; // when f = 0, 2 * 0 = 0, return uf
	
	if(expBits == 0x00) return uf + fracBits; // denormalize number, can only manipulate fraction to imlement x2.
	else return uf + (1 << 23); // normalized number, due to the leading 1 in frac, can only manipulate exponent to implement x2 
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	/* transfer float by manipulate exponent and fraction */

	unsigned expBits = (uf >> 23) & 0x000000FFu;
	unsigned fracBits = uf & 0x007FFFFFu;
	unsigned signBit = (uf >> 31) & 0x1u;
	unsigned Bias = 127; // 2 ^ (k-1) - 1 = 12
	unsigned normE; // normalized number's E, E = exp - Bias
	unsigned normM; // normalized number's M, M = 1.frac
					
	if(expBits == 0xFF) return 0x80000000; // uf is NaN or infinity
	else if(expBits == 0x00) return 0;   // denormalized, return 0

	/* normalized number*/
	// constrcut exp <= Bias - 1 to avoid representing negative number
	if(expBits <= Bias - 1) return 0; // normalized, exp-Bias <= -1, number < 1, so return 0. 
	normE = expBits - Bias;		     
	normM = (1 << 23) + fracBits;   // add the leading 1.	
	if(normE <= 23) 
	{ 
		if(!signBit)
			return normM >> (23 - normE); // normlized norm <= 23, positive number 
		else
			return ~(normM >> (23 - normE)) + 1; // negative number
	}
	if(normE >= 24 && normE <= 31)
	{
		if(!signBit)
			return normM << (normE - 23); // positive number
		else
			return ~(normM << (normE -23)) + 1;
	}
    // normE > 31, 32bit int can not represent anymore. includ TMIN
	return 0x80000000u;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	/* transfer expression 2.0 ^ x by manipulating frac and exp */
	int Bias = 127;
	int posINF = 0x7F800000;
	unsigned V = 0;
	unsigned expBits;
	unsigned fracBits; // all number all positive, don't need neg sign bit

	//signle-prescision can represent  2.0^x ,which x locate in [-149, 127]

	if(x >= -126 && x <= 127) // normal number
	{
		expBits = x + Bias; // all the result are postive, int/unsign can savely transfer.
		return expBits << 23;
	}
	else if(x < -126 && x >= -149) // denorm number
	{
		fracBits = 0x1 << (x - (-149));
		return fracBits;
	}

	if(x > 127) return posINF; // too large, larger than what normal number exp can represent 
	else if(x < -149) return 0; // too small, smaller than what denorm can represent, frac can provide extral 23, which is LSB=1 
}
