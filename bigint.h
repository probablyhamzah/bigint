/*
  For my implementation of BigInteger, I have chosen to represent the input number as an array of characters, with each element holding one 
  digit of the number. Since the supported operations are performed starting from LSB (least significant bit) and the number of digits in the
  result can be difficult to predict, I have chosen to represent the input number in the char array as LSB-first (in other words, in reverse).
  An MSB-first approach would require us to shift all elements to the right and add a new element to the start as the size increases or to the
  left if it decreases, whereas in LSB-first we can simply add or remove to the end of the array. This way we do not have to worry about the
  size of the result of the operations.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 309 is the max length of a 1024 bit integer.
#define SIZE 309

/*
  size: length of the integer
  sign: 0 for positive, 1 for negative
  val: Each element will hold a value between 0 and 9, so it would be more efficient to use a char over, say, an integer. val is an array of chars.
  Note that the sign is stored separately from the magnitude.
*/
struct bigInt
{
    int size;
    int sign;
    char* val;
};

/*
  Prints the number. 
*/
void print(struct bigInt* data);

/*
  Swaps x and y.
  This function would be useful during subtraction, since it's easier to subtract y from x when x > y. In the other case, we'd simply swap x and y.
*/
void swap(struct bigInt* x, struct bigInt* y);

/*
  Initialises num.
  size = size,
  sign = 0
  val = char array of length n
*/
void init(struct bigInt* num, int n, int size);

/*
  Returns
  0 if num1 = num2
  1 if num1 > num2
  -1 if num1 < num2
*/
int compare(struct bigInt* num1, struct bigInt* num2);

/*
  Takes an integer in the form of a string, and converts it into our bigint representation.
*/
struct bigInt convert(char s[SIZE + 2]);

/*
  For simplicity, we'll use a and b instead of num1 and num2

  Handling negative numbers:
  +a, +b -> a + b
  +a, -b -> a - b : subtract(a, b)
  -a, +b -> -a + b : subtract(a, b)
  -a, -b -> -(a + b)
*/
struct bigInt add(struct bigInt* num1, struct bigInt* num2);

/*
  Handling negative numbers:
  +a, +b -> a - b
  +a, -b -> a + b : add(a, b)
  -a, +b -> -(a + b) : add(a, b)
  -a, -b -> -a + b

  Further, we assume that a is numerically greater than b
  +a, +b: if a < b, swap a and b
  -a, -b: if a < b, swap a and b

  Note that for the same case, that is, one positive number and one negative number, we call subtract() from add() and vice versa. 
  This leads to an infinite loop.
  To avoid this we flip the sign bit of b and the operation is carried appropriately.
*/
struct bigInt subtract(struct bigInt* num1, struct bigInt* num2);

/*
  Handling negative numbers:
  +a, +b -> a * b
  +a, -b -> -(a * b)
  -a, +b -> -(a * b)
  -a, -b -> a * b
*/
struct bigInt multiply(struct bigInt* num1, struct bigInt* num2);
