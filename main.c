#include "bigint.h"

int main()
{

    char s1[SIZE + 2], s2[SIZE + 2];

    printf("Enter the first number: ");
    scanf("%s", s1);

    printf("Enter the second number: ");
    scanf("%s", s2);
    
    struct bigInt int1, int2, int3;
    int1 = convert(s1);
    int2 = convert(s2);

    printf("Addition:\n");
    int3 = add(&int1, &int2);
    print(&int3);

    printf("\nSubtraction:\n");
    free(int3.val);
    int3 = subtract(&int1, &int2);
    print(&int3);

    printf("\nMultiplication:\n");
    free(int3.val);
    int3 = multiply(&int1, &int2);
    print(&int3);

    free(int1.val);
    free(int2.val);
    free(int3.val);
}
