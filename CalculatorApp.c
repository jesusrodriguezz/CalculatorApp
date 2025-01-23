/*++

Module Name: 

   Calculator App 

Abstract: 

   A advance calculator app that can do basic arithmetic/trigonometric/logarithmic operations 
   “+”,”-“,”*”,”/”, ”^”, sin, cos, tan, cot, ln, log10 with real numbers involving parenthesis and curly brackets

Author: 

   Jesus Rodriguez

Class:

   Advanced Software Engineering(CS480)

--*/
#include <stdio.h>
#include <math.h>

//
// defined enum to store the operation
// type. 
//

typedef enum {
   ADD,
   SUBTRACT,
   MULTIPLY,
   DIVIDE,
   EXPONENT,
   SIN,
   COS,
   TAN,
   COT,
   LN,
   LOG10
} OperationType;

//
// defined struct to hold the number values
// and result. 
//

typedef struct {
   double operand_1;
   double operand_2;
   double result;
   OperationType operation;
} Calculator;

int precedence(char op)
/*
*/
{
   return 0;
}


double Add(double a, double b)
/*

Routine Description:

   This routine will perform addition.

Arguments:

   A - operand 1
   B - operand 2 

Return Value:

   result of operand 1 + operand 2.
                                            
*/ 
{
   return a + b;
}

double Subtract(double a, double b)
/*

Routine Description:

   This routine will perform subtraction.

Arguments:

   A - operand 1
   B - operand 2 

Return Value:

   result of operand 1 - operand 2.
                                            
*/ 
{
   return a - b;
}

double Multiply(double a, double b)
/*

Routine Description:

   This routine will perform multiplication.

Arguments:

   A - operand 1
   B - operand 2 

Return Value:

   result of operand 1 * operand 2.
                                            
*/ 
{
   return a * b;
}

double Divide(double a, double b)
/*

Routine Description:

   This routine will perform division.

Arguments:

   A - operand 1
   B - operand 2 

Return Value:

   result of operand 1 / operand 2.
                                            
*/ 
{
   if (b == 0) {
      printf("\nError: divison by zero\n");
      return NAN;
   }

   return a / b;
}

double Exponent(double a, double b)
/*
*/
{
   if (a == 0 && b == 0) {
      printf("/n Error: 0 to the power of 0 is undefined\n");
      return NAN;
   }

   return pow(a, b);
}

void PerformOperation(Calculator* calc) 
/*

Routine Description:

   This routine will call the function to perform
   the operation.

Arguments:

   calc - this is just so we can get a refrence to the struct and access the values.

Return Value:

   None.
*/
{
   switch (calc->operation) {
      case ADD:
         calc->result = Add(calc->operand_1, calc->operand_2);
         break;
      case SUBTRACT:
         calc->result = Subtract(calc->operand_1, calc->operand_2);
         break;
      case MULTIPLY:
         calc->result = Multiply(calc->operand_1, calc->operand_2);
         break;
      case DIVIDE:
         calc->result = Divide(calc->operand_1, calc->operand_2);
         break;
      case EXPONENT:
         calc->result = Exponent(calc->operand_1, calc->operand_2);
         break;
      default:
         printf("\nError: Invalid operation\n");
   }
}


int main() {
   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n             Calculator App               \n");
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   Calculator calc;
   char operator;
   
   // 
   // Prompt the user for input.
   //

   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n           Enter first operand: ");
   scanf("%lf", &calc.operand_1);
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n        Enter operator (+, -, *, /, ^): ");
   scanf(" %c", &operator);
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n           Enter second operand: ");
   scanf("%lf", &calc.operand_2);
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   switch (operator) {
      case '+':
         calc.operation = ADD;
         break;
      case '-':
         calc.operation = SUBTRACT;
         break;
      case '*':
         calc.operation = MULTIPLY;
         break;
      case '/':
         calc.operation = DIVIDE;
         break;
      case '^':
         calc.operation = EXPONENT;
         break;
      default:
         printf("Error: Invalid operator\n");
         return 1;
   }

   PerformOperation(&calc);


   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n          Result: %.2f %c %.2f = %.2f\n", calc.operand_1, operator, calc.operand_2, calc.result);
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

} 
