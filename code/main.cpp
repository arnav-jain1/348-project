#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <algorithm>
// Function to determine the precedence of operators
int getPrecedence(char op) {
    // Higher number means higher precedence
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to check if a character is an operator
bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
        return true;
    } else {
        return false;
    }
}

// Function to apply an operation to two operands
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            // Division by zero is undefined
            if (b == 0) throw std::runtime_error("Division by zero!");
            return a / b;
        case '%': return fmod(a, b); // Modulus operation
        case '^': return pow(a, b);  // Exponentiation
        // Invalid operator as input
        default: throw std::runtime_error("Invalid operator!");
    }
}

// Function to check if a character is a unary operator
bool isUnary(char token, char prev){
    if (token == '+' || token == '-'){
        if (!isdigit(prev) && !(prev ==')')){
            // The previous character is not a digit or a closing parenthesis and the current character is a unary operator, then true
            return true;
        }
    }
    // Otherwise, false
    return false;
}

// Function to parse the expression and add 0 before unary operators
std::string parser(std::string expr){
    // The default previous character is '(' and the output string is empty
    char prev = '(';
    std::string out= "";
    // Boolean to track if a closing parenthesis is needed
    bool closeP = false;

    // Loop through each character in the expression, if the current character is a unary operator, add (0 and the operator to the output string, otherwise add the character to the output string
    for(int i =0; i<expr.length();i++){
        if(isUnary(expr[i],prev)){
            out+= "(0";
            out+= expr[i];
            // Set the boolean to true to add a closing parenthesis later
            closeP = true;
        } else {
            out+= expr[i];
            // After adding the next char, check if the boolean is true. If it is, add a closing parenthesis and set the boolean to false
            if (closeP){
                out+= ")";
                closeP = false;
            }
        }
        

        // Set the previous character to the current character
        prev = expr[i];
    }
    return out;
}

// Function to evaluate a given expression
double evaluateExpression(const std::string& expr) {
    std::stack<double> values; // Stack for storing numbers
    std::stack<char> ops;      // Stack for storing operators
    std::string numberBuffer;  // Buffer to accumulate digits of a number and then convert to double
    bool checkLeftOperator = true; // boolean to track if last token processed is operator, if so then it will throw error

    // Loop through each character in the expression
    for (int i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue; // Skip spaces but there shouldnt be any

        // If the character is a digit or a decimal point, add it to the number buffer
        if (isdigit(expr[i]) || expr[i] == '.') {
            numberBuffer += expr[i];
            checkLeftOperator = false;
        } else {
            // If number buffer is not empty, convert it to a number and push onto the stack
            if (!numberBuffer.empty()) {
                values.push(std::stod(numberBuffer));
                numberBuffer = "";
            }

            // Handling parentheses
            if (expr[i] == '(') {
                if (checkLeftOperator == false && expr[i-1] != '('){
                    throw std::runtime_error("Missing operator!");
                }
                ops.push(expr[i]);
                checkLeftOperator = false;
            } else if (expr[i] == ')') {
                if (i+1 < expr.length() && isdigit(expr[i+1])){
                    throw std::runtime_error("Missing operator!");
                }
                
                // Evaluate the expression inside the parentheses

                // while the operators stack is not empty and the top of the stack is not a '('
                while (!ops.empty() && ops.top() != '(') {
                    // Get the top 2 values from the numbers stack, remove it, get the top operator from the operators stack, remove it, apply the operator to the values and push the result to the numbers stack
                    double val2 = values.top(); 
                    values.pop();
                    double val1 = values.top(); 
                    values.pop();
                    char op = ops.top(); 
                    ops.pop();

                    values.push(applyOp(val1, val2, op));
                }
                if (!ops.empty()) {
                    ops.pop(); // Remove the '(' from the stack
                }
                checkLeftOperator = false;
            } else if (isOperator(expr[i])) {
                // If the current character is an operator, process the top of the stacks
                if (checkLeftOperator && expr[i] != '('){
                    throw std::runtime_error("Operator without operand!");
                }
                if (i+1 >= expr.length() || expr[i+1] == ')'){
                    throw std::runtime_error("Missing operand/Invalid operating sequence!");
                }
                while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i])) {
                    // If the top of the operators stack has higher precedence than the current operator, apply the operator to the top 2 values from the numbers stack and push the result to the numbers stack
                    double val2 = values.top(); 
                    values.pop();
                    double val1 = values.top(); 
                    values.pop();
                    char op = ops.top(); 
                    ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                ops.push(expr[i]); // Push current operator to stack
                checkLeftOperator = true;
            } else {
                throw std::runtime_error("Invalid input!"); // Error for invalid characters
            }
        }
    }

    // Push the last number in the buffer to the stack
    if (!numberBuffer.empty()) {
        values.push(std::stod(numberBuffer));
    }

    // Complete any remaining operations with the same logic as above
    while (!ops.empty()) {
        double val2 = values.top(); 
        values.pop();
        double val1 = values.top(); 
        values.pop();
        char op = ops.top(); 
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top(); // Return the final result
}

int main() {
    // Get the expression from the user
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);


    // Removes any whitespace in expression and trims the remaining string
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
    // Counts the number of ')' characters 
    int pEndCount = std::count(expression.begin(), expression.end(), ')');
    // Counts the number of '(' characters 
    int pStartCount = std::count(expression.begin(), expression.end(), '(');
    
    // If the number of ')' and '(' characters are not equal, then there is an unmatched parantheses, exit the program
    if (pEndCount != pStartCount) {
        std::cout << ("Unmatched parantheses")<< std::endl;
        return 1; 
    }

    try {
        // Evaluate the expression and print the result
        double result = evaluateExpression(parser(expression));
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        // Print the error message, if any
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
