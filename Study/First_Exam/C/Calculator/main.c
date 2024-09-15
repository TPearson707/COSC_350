// main.c

#include "arithmatic.h"

int main()
{

    float a;
    float b;
    int choice;
    float answer;

    printf("Enter a: ");
    scanf("%f", &a);

    printf("Enter b: ");
    scanf("%f", &b);
    
    printf("\n");

    printf("Calculator Options\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("Enter a number: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            answer = add(a, b);
            printf("The answer is: %f", answer);
            break;
        case 2:
            answer = subtract(a, b);
            printf("The answer is: %f", answer);
            break;
        case 3:
            answer = multiply(a, b);
            printf("The answer is: %f", answer);
            break;
        case 4:
            answer = divide(a, b);
            printf("The answer is: %f", answer);
            break;

        default:
            printf("Something went wrong");
            return 1;
    }

    printf("\n");

    return 0;
}
