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
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//
// defined enum to store the operation
// types. 
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
// Defined the Stack data structure to be used for 
// operands and operators.
//

typedef struct {
   int top;
   int capacity;
   double* data;
} Stack;

Stack* createStack(int capacity) {
   Stack* stack = (Stack*)malloc(sizeof(Stack));
   stack->capacity = capacity;
   stack->top = -1;
   stack->data = (double*)malloc(stack->capacity * sizeof(double));
   return stack;
}

int isEmpty(Stack* stack)
/*
*/
{
   return stack->top == -1;
}

void push(Stack* stack, double value)
/*
*/
{
   if (stack->top == stack->capacity - 1) {
      stack->capacity *= 2;
      stack->data = realloc(stack->data, stack->capacity * sizeof(double));
   }

   stack->data[++stack->top] = value;
}

double pop(Stack* stack) 
/*
*/
{
   if (isEmpty(stack)) {
      printf("Error: Stack overflow\n");
      exit(1);
   }
   
   return stack->data[stack->top--];
}

double peek(Stack* stack) 
/*
*/
{
   if (isEmpty(stack)) {
      printf("Error: Stack is empty\n");
      exit(1);
   }

   return stack->data[stack->top];
}


int precedence(char op)
/*
Routine Description:

   This routine determines the level of precedence for the operators.

Arguments:

   op - this is the char value for the type of operation.

Return Value:

   returns the level of precedence for the type of operation if
   the operation is non exisiting then the level of precedence
   is zero.
*/
{
   if (op == '+' || op == '-') {
      return 1;
   }
   
   if (op == '*' || op == '/') {
      return 2;
   }

   if (op == '^') {
      return 3;
   }

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
Routine Description:

   This routine will perform a ^ b

Arguments:

   a - operand 1
   b - operand 2 

Return Value:

   result of operand 1 ^ operand 2.
*/
{
   if (a == 0 && b == 0) {
      printf("/n Error: 0 to the power of 0 is undefined\n");
      return NAN;
   }

   return pow(a, b);
}

double Sin(double a)
/*
Routine Description:

   This routine computes the sine of the input value 
   using the trigonometric sine function.

Arguments:

   a - input value 

Return Value:

   The sine of the input value.
*/
{
   return sin(a);
}

double Cos(double a)
/*
Routine Description:

   This routine computes the cosine of the input value using 
   the trigonometric cosine function.

Arguments:

   a - input value

Return Value:

   The cosine of the input value.
*/
{
   return cos(a);
}

double Tan(double a)
/*
Routine Description:

   This routine computes the tangent of the input value 
   using the trigonometric tangent function.

Arguments:

   a - input value 

Return Value:

   The tangent of the input value.
*/
{
   return tan(a);
}

double Cot(double a)
/*
Routine Description:

   This routine computes the cotangent of the input value 
   using the trigonometric cotangent function.

Arguments:

   a - input value 

Return Value:

   The cotangent of the input value.
*/
{
   return 1.0 / tan(a);
}

double Ln(double a)
/*
Routine Description:

   This routine computes the natural logarithm of the input value using the logarithm function.

Arguments:

   a - input value

Return Value:

   The natural logarithm of the input value.
*/
{
   return log(a);
}

double Log10(double a)
/*
Routine Description:

   This routine computes the base-10 logarithm of the input value using the logarithm function.

Arguments:

   a - input value

Return Value:

   The base-10 logarithm of the input value.
*/
{
   return log10(a);
}

double ApplyOperation(double a, double b, OperationType op)
/*
*/
{
   switch (op) {
      case ADD:
         return Add(a, b);
      case SUBTRACT: 
         return Subtract(a, b);
      case MULTIPLY: 
         return Multiply(a, b);
      case DIVIDE: 
         return Divide(a, b);
      case EXPONENT: 
         return Exponent(a, b);
      case SIN:
         return Sin(a);
      case COS:
         return Cos(a);
      case TAN:
         return Tan(a);
      case COT:
         return Cot(a);
      case LN:
         return Ln(a);
      case LOG10:
         return Log10(a);
      default: 
         return 0;
   }
}

double evaluateExpression(char* expr) 
/*
*/
{
   Stack* values = createStack(10);
   Stack* ops = createStack(10);

   for (int i = 0; expr[i] != '\0'; i++) {
      char ch = expr[i];

      // Skip whitespace
      if (isspace(ch)) continue;

      // Handle negative numbers (unary minus)
      if (ch == '-' && (i == 0 || expr[i - 1] == '(' || strchr("+-*/^", expr[i - 1]))) {
         double value = 0;
         double fraction = 0.0;
         double divisor = 10.0;
         int isFraction = 0;
         i++;  // Skip the '-' and start parsing the number

         while (i < strlen(expr) && (isdigit(expr[i]) || expr[i] == '.')) {
            if (expr[i] == '.') {
               isFraction = 1;
            } else {
               if (isFraction) {
                  fraction += (expr[i] - '0') / divisor;
                  divisor *= 10.0;
               } else {
                  value = (value * 10) + (expr[i] - '0');
               }
            }
            i++;
         }
         i--;  // Step back to correct position
         value += fraction; // Add fractional part to the whole number
         value = -value; // Make the number negative
         push(values, value);
      }
      
      // Handle numbers (push to the value stack)
      else if (isdigit(ch) || ch == '.') {
         double value = 0;
         double fraction = 0.0;
         double divisor = 10.0;
         int isFraction = 0;

         while (i < strlen(expr) && (isdigit(expr[i]) || expr[i] == '.')) {
            if (expr[i] == '.') {
               isFraction = 1;
            } else {
               if (isFraction) {
                  fraction += (expr[i] - '0') / divisor;
                  divisor *= 10.0;
               } else {
                  value = (value * 10) + (expr[i] - '0');
               }
            }
            i++;
         }
         i--; // Step back to correct position
         value += fraction; // Add fractional part to the whole number
         push(values, value);
      }

      // Handle '('
      else if (ch == '(') {
         push(ops, ch);
      }

      // Handle ')'
      else if (ch == ')') {
         while (!isEmpty(ops) && peek(ops) != '(') {
            double val2 = pop(values);
            double val1 = pop(values);
            char op = (char)pop(ops);
            OperationType operation;
            switch (op) {
               case '+': operation = ADD; break;
               case '-': operation = SUBTRACT; break;
               case '*': operation = MULTIPLY; break;
               case '/': operation = DIVIDE; break;
               case '^': operation = EXPONENT; break;
               default: continue;
            }
            push(values, ApplyOperation(val1, val2, operation));
         }
         pop(ops);  // Pop '(' from the stack
      }

      // Handle operators
      else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
         while (!isEmpty(ops) && precedence(peek(ops)) >= precedence(ch)) {
            double val2 = pop(values);
            double val1 = pop(values);
            char op = (char)pop(ops);
            OperationType operation;
            switch (op) {
               case '+': operation = ADD; break;
               case '-': operation = SUBTRACT; break;
               case '*': operation = MULTIPLY; break;
               case '/': operation = DIVIDE; break;
               case '^': operation = EXPONENT; break;
               default: continue;
            }
            push(values, ApplyOperation(val1, val2, operation));
         }
         push(ops, ch);
      }

      // Handle trigonometric and logarithmic functions
      else if (strncmp(&expr[i], "sin", 3) == 0) {
         i += 2;  // Skip 'sin'
         push(ops, SIN);
      } else if (strncmp(&expr[i], "cos", 3) == 0) {
         i += 2;  // Skip 'cos'
         push(ops, COS);
      } else if (strncmp(&expr[i], "tan", 3) == 0) {
         i += 2;  // Skip 'tan'
         push(ops, TAN);
      } else if (strncmp(&expr[i], "cot", 3) == 0) {
         i += 2;  // Skip 'cot'
         push(ops, COT);
      } else if (strncmp(&expr[i], "ln", 2) == 0) {
         i += 1;  // Skip 'ln'
         push(ops, LN);
      } else if (strncmp(&expr[i], "log", 3) == 0) {
         i += 2;  // Skip 'log'
         push(ops, LOG10);
      }
   }

   // Apply remaining operators
   while (!isEmpty(ops)) {
      double val1 = 0; 
      double val2 = pop(values);  // Unary operators only need this
      char op = (char)pop(ops);  // Get the operator

      OperationType operation;
      switch (op) {
         case '+': 
            operation = ADD; 
            val1 = pop(values);  
            break;
         case '-': 
            operation = SUBTRACT; 
            val1 = pop(values);  
            break;
         case '*': 
            operation = MULTIPLY; 
            val1 = pop(values);  
            break;
         case '/': 
            operation = DIVIDE; 
            val1 = pop(values);  
            break;
         case '^': 
            operation = EXPONENT; 
            val1 = pop(values);
            break;

         // Unary operators (trigonometric and logarithmic)
         case SIN: 
            operation = SIN; 
            break;  
         case COS: 
            operation = COS; 
            break;  
         case TAN: 
            operation = TAN; 
            break;  
         case COT: 
            operation = COT; 
            break;  
         case LN:  
            operation = LN; 
            break; 
         case LOG10: 
            operation = LOG10; 
            break; 
         default: 
            continue;  
      }

      // Apply the operation
      double result;
      if (operation == ADD || operation == SUBTRACT || operation == MULTIPLY || 
         operation == DIVIDE || operation == EXPONENT) {
         result = ApplyOperation(val1, val2, operation);  // Binary operation
      } else {
         result = ApplyOperation(val2, 0, operation);  // Unary operation
      }

      // Push the result back onto the values stack
      push(values, result);
   }
   // The final result will be the only value in the stack
   double result = pop(values);

   // Free memory
   free(values->data);
   free(values);
   free(ops->data);
   free(ops);

   return result;
}



int main() {
   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n             Calculator App               \n");
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   char exp[100];

   // 
   // Prompt the user for input.
   //

   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n  Enter an expression (e.g., (1 + 2) * 3): \n");
   printf("-                                          -");
   printf("\n--------------------------------------------\n");
   fgets(exp, sizeof(exp), stdin);

   //
   // Remove newline character
   //

   exp[strcspn(exp, "\n")] = '\0';  

   // 
   // Evaluate and print the result for the user input expression
   //

   double result = evaluateExpression(exp);

   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n           Result: %.2f\n", result);
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   return 0;

} 
