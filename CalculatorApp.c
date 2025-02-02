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
// defined function so it can be used in other functions.
//

double evaluateExpression(char* expr);

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

//
// The stack was implemeneted with online resources 
//

Stack* createStack(int capacity) 
/*
Routine Description:

   This routine creates and initializes a stack with a specified capacity.
   It allocates memory for the stack structure and its data array, sets the 
   stack's initial top index to -1 (indicating the stack is empty), and 
   assigns the given capacity to the stack.

Arguments:

   capacity - The initial capacity of the stack, which determines the size 
              of the data array that holds the stack elements.

Return Value:

   Returns a pointer to the newly created stack.
*/
{
   Stack* stack = (Stack*)malloc(sizeof(Stack));
   stack->capacity = capacity;
   stack->top = -1;
   stack->data = (double*)malloc(stack->capacity * sizeof(double));
   return stack;
}

int isEmpty(Stack* stack)
/*
Routine Description:

   This routine checks if the stack is empty by evaluating whether the 
   stack’s top index is -1. If the top index is -1, the stack is considered empty.

Arguments:

   stack - A pointer to the stack that is being checked.

Return Value:

   Returns 1 if the stack is empty or 0 if its not.
*/
{
   return stack->top == -1;
}

void push(Stack* stack, double value)
/*
Routine Description:

   This routine pushes a value onto the stack. If the stack has reached its 
   capacity, it dynamically reallocates memory to double the stack's capacity 
   before adding the new value at the top. The stack's top index is then 
   incremented to point to the newly added element.

Arguments:

   stack - A pointer to the stack onto which the value will be pushed.
   value - The value to be added to the stack.

Return Value:

   This function does not return a value. It modifies the stack in place.
   If resizing is necessary, the stack's capacity is increased.
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
Routine Description:

   This routine pop the most recent value in the stack.

Arguments:

   stack - this is the stack 

Return Value:

   it returns the value of the pop item.
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
Routine Description:

   This routine returns the value at the top of the stack without removing it.
   If the stack is empty, an error message is displayed.

Arguments:

   stack - A pointer to the stack from which the top element is being peeked.

Return Value:

   Returns the value of the element at the top of the stack. If the stack is empty,
   the program will terminate with an error message.
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

This routine performs the addition of two operands, returning their sum.

Arguments:

   a - The first operand in the addition operation.
   b - The second operand in the addition operation.

Return Value:

   Returns the result of adding operand `a` and operand `b` together.
                                            
*/ 
{
   return a + b;
}

double Subtract(double a, double b)
/*

Routine Description:

   This routine performs subtraction of two operands, returning the difference.

Arguments:

   a - The first operand in the subtraction operation.
   b - The second operand in the subtraction operation.

Return Value:

   Returns the result of subtracting operand `a` and operand `b` together.
                                            
*/ 
{
   return a - b;
}

double Multiply(double a, double b)
/*

Routine Description:

   This routine performs multiplication of two operands, returning the product.

Arguments:

   a - The first operand in the multiplication operation.
   b - The second operand in the multiplication operation.

Return Value:

   Returns the result of multiplying operand `a` and operand `b` together.

*/ 
{
   return a * b;
}

double Divide(double a, double b)
/*

Routine Description:

   This routine performs division of two operands. If the second operand `b` is zero, 
   it prints an error message and returns `NAN` (Not A Number).

Arguments:

   a - The first operand (dividend) in the division operation.
   b - The second operand (divisor) in the division operation.

Return Value:

   Returns the result of dividing operand `a` by operand `b`
                                            
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

   This routine calculates the result of `a` raised to the power of `b` (i.e., `a^b`).
   If both `a` and `b` are zero, it returns `NAN` and prints an error message.

Arguments:

   a - The base of the exponentiation.
   b - The exponent to which the base `a` is raised.

Return Value:

   Returns the result of raising operand `a` to the power of operand `b`.
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

   This routine computes the sine of the input value `a` using the standard 
   trigonometric sine function. The input value is assumed to be in radians.

Arguments:

   a - input value.

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
Routine Description:

   This routine applies the operation type function based on its parameters.
   The ApplyOperation function is used in the evaluateExpression function.

Arguments:

   a - The double value variable 
   b - The double value variable
   op - the type of operation 

Return Value:

   It returns the value of the operation used.

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

//
// The function removeSpaces was implemented with online resources 
//

void removeSpaces(char* source) 
/*
Routine Description:

   This function removes all whitespace characters from the given input string. 
   It modifies the string in place to ensure that only non-whitespace characters remain.

Arguments:

   source - A pointer to the input string that represents the mathematical expression.

Return Value:

   The function does not return a value. Instead, it modifies the input string 
   directly, removing all whitespace characters.
*/
{

   //
   // i will be used to store non space characters
   // j will be used to store the original string
   //
   char* i = source;
   char* j = source;

   //
   // loop until the end of the string
   //

   while (*j != '\0') {

      //
      // check if the current character is Not a white space
      //

      if (!isspace(*j)) {

         //
         // move the non white space character to i then move i
         // forward to store the next valid character
         //

         *i = *j;  
         i++;
      }

      //
      // if j is a white space then we move it forward to chekc the next character
      //
      
      j++;
   }
   
   //
   // Null-terminate the modified string to indicate its new length
   //

   *i = '\0'; 
}

//
// The evaluateTrigFunction was implemented with online resources (chatgpt)
//

double evaluateTrigFunction(char* expr, int *i) 
/*
Routine Description:

   This routine evaluates a trigonometric or logarithmic function in an expression. 
   It extracts the function name from the string, retrieves the argument inside parentheses, 
   evaluates that argument as a sub-expression, and then applies the appropriate mathematical 
   function to the result. If the function is unknown, an error message is printed.

Arguments:

   expr - A string containing the mathematical expression to evaluate, which includes a function and 
          its argument enclosed in parentheses.
   i - A pointer to an index that tracks the current position in the expression string `expr`.

Return Value:

   Returns the result of the function applied to the argument.
   If the function is unknown, the function returns 0 and prints an error message.
*/
{
   char func[10];
   int j = 0;

   // 
   // Extract the function name until '(' is encountered.
   //

   while (expr[*i] != '(' && expr[*i] != '\0' && j < (int)sizeof(func)-1) {
      func[j++] = expr[*i];
      (*i)++;
   }

   func[j] = '\0';

   // 
   // Skip the '('
   //

   if (expr[*i] == '(') {
      (*i)++;
   }
   
   // 
   // Find the matching ')' while handling nested parentheses.
   //

   int start = *i;
   int parenCount = 1;
   while (expr[*i] != '\0' && parenCount > 0) {
      if (expr[*i] == '(')
         parenCount++;
      else if (expr[*i] == ')')
         parenCount--;
      (*i)++;
   }

   // 
   // Now, the argument is the substring from 'start' to (*i - 1).
   //

   int argLength = (*i) - start - 1; // exclude the final ')'
   if (argLength < 0)
      argLength = 0;
   char *argStr = (char*)malloc(argLength + 1);
   strncpy(argStr, expr + start, argLength);
   argStr[argLength] = '\0';
   
   // 
   // Evaluate the argument expression.
   //

   double arg = evaluateExpression(argStr);
   free(argStr);
   
   // 
   // Apply the appropriate function.
   //

   if (strcmp(func, "sin") == 0) {
      return Sin(arg);
   } else if (strcmp(func, "cos") == 0) {
      return Cos(arg);
   } else if (strcmp(func, "tan") == 0) {
      return Tan(arg);
   } else if (strcmp(func, "cot") == 0) {
      return Cot(arg);
   } else if (strcmp(func, "ln") == 0) {
      return Ln(arg);
   } else if (strcmp(func, "log") == 0) {
      return Log10(arg);
   } else {
      printf("Unknown function: %s\n", func);
      return 0;
   }
}

//
// The evaluateExpression function was implemented with online resources (chatgpt/geeksforgeeks)
//

double evaluateExpression(char* expr) 
/*
Routine Description:

   This routine evaluates a mathematical expression represented as a string.
   It parses the expression character by character, handling numbers, operators,
   parentheses, trigonometry functions and logarithmetic functions. The function
   uses two stacks: one for values (values) and one for operators (ops). It applies
   the operators in the correct order of precedence, computes intermediate results,
   and returns the final result of the expression.

   The function uses recursion to evaluate sub-expressions inside parentheses.
   When it encounters a nested expression in parentheses, it calls itself to evaluate
   the expression within those parentheses, ensuring the correct evaluation order.

   The function uses helper functions like precedence, and evaluateTrigFunction.

Arguments:

   expr - A string representing the mathematical expression to be evaluated.

Return Value:

   Returns the result of evaluating the mathematical expression.
*/
{
   //
   // function call to remove spaces for better parsing
   //

   removeSpaces(expr);

   //
   // 2 stacks to hold numbers and operators
   //

   Stack* values = createStack(10);
   Stack* ops = createStack(10);
   
   //
   // get the length of the expressing string
   //

   int len = strlen(expr);
   int i = 0;

   //
   // iterate through the expression character by character
   //
   
   while (i < len && expr[i] != '\0') {
      char ch = expr[i];
      
      // 
      // Handle negative numbers (unary minus)
      //

      if (ch == '-' && (i == 0 || expr[i - 1] == '(' || strchr("+-*/^", expr[i - 1]))) {

         //
         // if the character is a '(' then we handle the negative number inside the paranthesis
         //

         if (expr[i + 1] == '(') {

            // 
            // Skip the '('
            //

            i++;  

            //
            // recursively solve the expression inside the paranthesis
            //

            double value = evaluateExpression(&expr[i]);

            // 
            // Negate the result and push it onto the values stack.
            //

            push(values, -value);

            // 
            // Skip the closing ')'
            //

            while (expr[i] != ')') i++;
         } else {

            //
            // Parsing a negative number (e.g., -1, -2.5)
            //

            double value = 0;
            double fraction = 0.0;
            double divisor = 10.0;
            int isFraction = 0;
            i++;  // Skip the '-' and start parsing the number

            //
            // Parse the number, handling integer and fractional parts.
            //

            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
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

            // 
            // Step back to the correct position after parsing the number.
            // Add fractional part to the whole number
            // Make the number negative
            // Push the negative value onto the stack.
            //

            i--; 
            value += fraction; 
            value = -value; 
            push(values, value);
         }
      } 

      // 
      // Handle numbers (push to the value stack)
      //

      else if (isdigit(ch) || ch == '.') {
         double value = 0;
         double fraction = 0.0;
         double divisor = 10.0;
         int isFraction = 0;
         while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
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

         //
         // Step back to correct position
         // Add fractional part to the whole number
         // Push the value into the stack
         //

         i--; 
         value += fraction;
         push(values, value);
      }

      // 
      // Handle '(' and push into the stack
      //

      else if (ch == '(') {
         push(ops, ch);
      }

      // 
      // Handle ')'
      //

      else if (ch == ')') {

         //
         // Pop and apply operators from the operator stack until we find the matching '('
         //

         while (!isEmpty(ops) && peek(ops) != '(') {
            double val2 = pop(values);
            double val1 = pop(values);
            char op = (char)pop(ops);
            OperationType operation;
            switch (op) {
               case '+': 
                  operation = ADD; 
                  break;
               case '-': 
                  operation = SUBTRACT; 
                  break;
               case '*': 
                  operation = MULTIPLY; 
                  break;
               case '/': 
                  operation = DIVIDE; 
                  break;
               case '^': 
                  operation = EXPONENT; 
                  break;
               default: 
                  continue;
            }

            //
            // Apply the operation and push the result onto the value stack.
            //

            push(values, ApplyOperation(val1, val2, operation));
         }

         // 
         // Pop '(' from the stack 
         //

         pop(ops);  
      }

      // 
      // Handle operators
      //

      else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {

         //
         // Apply operators with higher or equal precedence before pushing the current operator onto the stack.
         //

         while (!isEmpty(ops) && precedence(peek(ops)) >= precedence(ch)) {
            double val2 = pop(values);
            double val1 = pop(values);
            char op = (char)pop(ops);
            OperationType operation;
            switch (op) {
               case '+': 
                  operation = ADD; 
                  break;
               case '-': 
                  operation = SUBTRACT; 
                     break;
               case '*': 
                  operation = MULTIPLY; 
                  break;
               case '/': 
                  operation = DIVIDE; 
                  break;
               case '^': 
                  operation = EXPONENT; 
                  break;
               default: 
                  continue;
            }
            push(values, ApplyOperation(val1, val2, operation));
         }

         push(ops, ch);
      }

      // 
      // Handle trig and log functions using the helper function evaluateTrigFunction
      //

      else if (isalpha(ch)) {
         double funcVal = evaluateTrigFunction(expr, &i);
         push(values, funcVal);
         //
         // Decrement i because evaluateTrigFunction already advanced it,
         //

         i--;  
      }
      
      //
      // move to the next character in the expression
      //

      i++;
   }

   // 
   // Apply remaining operators.
   //

   while (!isEmpty(ops)) {
      double val2 = pop(values);
      double val1 = 0; 
      char op = (char)pop(ops);
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
         default: 
            continue;  
      }

      double result = ApplyOperation(val1, val2, operation);
      push(values, result);
   }
   
   // 
   // The final result will be the only value in the stack.
   //

   double result = pop(values);
   
   // 
   // Free memory.
   //

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
   printf("\n               Created By                  \n");
   printf("\n             Jesus Rodriguez             \n");
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   printf("\n");

   printf("\n--------------------------------------------\n");
   printf("\n");
   printf("-                                          -");
   printf("\nHow To Use Calculator:               \n");
   printf("\nEnter a valid mathematical expression ex: ((1+2)*3)\n");
   printf("\nYou can include spaces if you like\n");
   printf("\nTrigonometry functions:\n");
   printf("\nsin - sin(number)\n");
   printf("\ncos - cos(number)\n");
   printf("\ntan - tan(number)\n");
   printf("\ncot - cot(number)\n");
   printf("\nln - ln(number)\n");
   printf("\nlog10 - log(number)\n");
   printf("\n");
   printf("-                                          -");
   printf("\n--------------------------------------------\n");

   char exp[100];


   // 
   // Prompt the user for input.
   //

   printf("\n--------------------------------------------\n");
   printf("-                                          -");
   printf("\n  Enter an expression : \n");
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