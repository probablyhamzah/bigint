#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 309

struct bigInt
{
    int size;
    int sign;
    char* val;
};


void print(struct bigInt* data);
void swap(struct bigInt* x, struct bigInt* y);
void init(struct bigInt* num, int n, int size);
int compare(struct bigInt* num1, struct bigInt* num2);

struct bigInt convert(char s[SIZE + 2]);

struct bigInt add(struct bigInt* num1, struct bigInt* num2);
struct bigInt subtract(struct bigInt* num1, struct bigInt* num2);
struct bigInt multiply(struct bigInt* num1, struct bigInt* num2);
