# BigInt
BigInteger implementation that supports upto 1024 bit integers. Addition, subtraction and multiplication are supported.

## Usage
Add the header file to your program.
```c
#include "bigint.h"
```

Initialise the numbers are strings.
```c
char s1[SIZE + 2] = "12345", // SIZE: max length of a 1024 bit integer
                             // +1 for a '-' sign in case of negative integers
                             // +1 for the null character
     s2[SIZE + 2] = "678";
```

Convert the strings to their BigInt representations.
```c
struct bigInt int1 = convert(s1),
              int2 = convert(s2);
```

Addition:
```c
struct bigInt result = add(&int1, &int2);
```

Subtraction:
```c
struct bigInt result = subtract(&int1, &int2);
```

Multiplication:
```c
struct bigInt result = multiply(&int1, &int2);
```

Printing the value
```c
print(&result);
```

Make sure you free the bigInts when you're done using them.
Not doing so would result in a memory leak.

```c
free(int1.val);
free(int2.val);
free(int3.val);
```

Also, free a bigInt before overwriting it.
```c
//Addition
int3 = add(&int1, &int2);
print(&int3);

//Subtraction
free(int3.val);
int3 = subtract(&int1, &int2);
print(&int3);
```

