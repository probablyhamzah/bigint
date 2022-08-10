#include "bigint.h"

void print(struct bigInt* data)
{
    if(data->sign == 1)
        printf("-");
    for(int i = data->size - 1; i >= 0; i--)
        printf("%d", data->val[i]);
    printf("\n");
}

void swap(struct bigInt* x, struct bigInt* y)
{
    struct bigInt temp = *x;
    *x = *y;
    *y = temp;
}

void init(struct bigInt* num, int n, int size)
{
    num->size = size;
    num->val = (char*)malloc(n * sizeof(char));
    num->sign = 0;
}

struct bigInt convert(char s[SIZE + 2])
{
    struct bigInt num;
    init(&num, SIZE, strlen(s));

    int i = 0, j = strlen(s) - 1;
    if(s[0] == '-')
    {
        num.size--;
        num.sign = 1;
    }
    else
    {
        num.sign = 0;
    }
    
    while(i < num.size)
    {
        num.val[i] = s[j] - '0'; 
        i++;
        j--;
    }
    return num;
}

int compare(struct bigInt* num1, struct bigInt* num2)
{
    int retval = 0;
    
    if(num1->size > num2->size)
        retval = 1;
    else if(num1->size < num2->size)
        retval = -1;
    else
    {
        for(int i = num1->size - 1; i >= 0 && retval == 0; i--)
        {
            if(num1->val[i] > num2->val[i])
            {
                retval = 1;
            }
            if(num1->val[i] < num2->val[i])
            {
                retval = -1;
            }
        }
        
    }
    return retval;
}

struct bigInt add(struct bigInt* num1, struct bigInt* num2)
{    
    struct bigInt total;
    init(&total, SIZE, 0);

    // Take care of + and - cases
    if(num1->sign != num2->sign)
    {
        num2->sign = !num2->sign;
        total = subtract(num1, num2);
        num2->sign = !num2->sign;
        return total;
    }
    
    int i = 0, carry = 0;

    // Add the corresponding values of the digits along with the carry
    // and manage the carry value.
    while(i < num1->size && i < num2->size)
    {
        int sum = num1->val[i] + num2->val[i] + carry;
        
        total.val[i] = sum % 10;
        carry = sum / 10;
        
        ++total.size;
        ++i;
    }

    // If the size of num1 is greater than that of num2, we'll be left with
    // digits that we haven't iterated through. In this case iterate through
    // them adding just the carry.
    while(i < num1->size)
    {
        int sum = num1->val[i] + carry;
        
        total.val[i] = sum % 10;
        carry = sum / 10;
        
        ++total.size;
        ++i;
    }

    // Similary for the case when num2 is greater than num1.
    // Since either num1 > num2 or num2 > num1, we can assure that either one
    // of this or the previous one would run but not both. Neither in the case
    // of num1 = num2
    while(i < num2->size)
    {
        int sum = num2->val[i] + carry;
        
        total.val[i] = sum % 10;
        carry = sum / 10;
        
        ++total.size;
        ++i;
    }

    // If we're left with a carry, append it to the end.
    if(carry != 0)
    {
        total.val[i] = carry;
        ++total.size;
    }

    // Assign the appropriate sign to the total
    if(num1->sign == 1 && num2->sign == 1)
        total.sign = 1;
    else
        total.sign = 0;
    
    return total;
}

struct bigInt subtract(struct bigInt* num1, struct bigInt* num2)
{
    struct bigInt total;
    init(&total, SIZE, 0);
    
    if(num1->sign != num2->sign)
    {
        num2->sign = !num2->sign;
        total = add(num1, num2);
        num2->sign = !num2->sign;
        
        return total;
    }
    else
    {
        if(num1->sign == 0 && num2->sign == 0)
        {
            if(compare(num1, num2) >= 0)
                total.sign = 0;
            else
            {
                swap(num1, num2);
                total.sign = 1;
            }
        }
        else
        {
            if(compare(num1, num2) >= 0)
            {
               
                total.sign = 1;
            }
            else
            {
                total.sign = 0;
                swap(num1, num2);
            }
        
        }
    }
    

    int i = 0, borrow = 0;
    while(i < num1->size && i < num2->size)
    {
        int diff = num1->val[i] - num2->val[i] - borrow;

        if(diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        total.val[i] = diff;
        ++total.size;
        ++i;
    }

    
    while(i < num1->size)
    {
        int diff = num1->val[i] - borrow;

        if(diff <= 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        total.val[i] = diff;
        ++total.size;
        ++i;
    }
    

    if(borrow != 0)
    {
        --total.size;
    }

    for(int i = total.size - 1; i > 0; i--)
    {
        if(total.val[i] == 0)
            --total.size;
        else
            break;
    }
    
    
    return total;
}

struct bigInt multiply(struct bigInt* num1, struct bigInt* num2)
{
    struct bigInt total;
    init(&total, 2 * SIZE, 0);
    
    int carry = 0, offset = 0;
    for(int i = 0; i < num2->size; i++)
    {
        int j = 0, k;
        while(j < num1->size)
        {
            int prod = num2->val[i] * num1->val[j] + carry;
            carry = prod / 10;
            k = j + offset;
            if(k < total.size)
            {
                total.val[k] += prod % 10;

                if(total.val[k] > 9)
                {
                    if(k + 1 < total.size)
                    {
                        total.val[k + 1] += total.val[k] / 10;
                    }
                    else
                    {
                        total.val[k + 1] = total.val[k] / 10;
                        ++total.size;
                    }
                    total.val[k] %= 10;
                }
            }
            else
            {
                total.val[k] = prod % 10;
                ++total.size;
            }
            j++;
        }
        
        k = j + offset;
        
        if(carry != 0)
        {
            if(k < total.size)
            {
                total.val[k] += carry;

                if(total.val[k] > 9)
                {
                    if(k + 1 < total.size)
                    {
                        total.val[k + 1] += total.val[k] / 10;
                    }
                    else
                    {
                        total.val[k + 1] = total.val[k] / 10;
                        ++total.size;
                    }
                }
                total.val[k] %= 10;

            }
            else
            {
                total.val[k] = carry;
                ++total.size;
            }
        }
        carry = 0;
        ++offset;
    }

    if(num1->sign == num2->sign)
        total.sign = 0;
    else
        total.sign = 1;
    return total;
}
