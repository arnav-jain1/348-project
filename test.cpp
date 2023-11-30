#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <algorithm>
// Function to determine the precedence of operators
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to check if a character is an operator
bool isOperator(char c) {
    return std::string("+-*/%^").find(c) != std::string::npos;
}

// Function to apply an operation to two operands
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw std::runtime_error("Division by zero!");
            return a / b;
        case '%': return fmod(a, b); // Modulus operation
        case '^': return pow(a, b);  // Exponentiation
        default: throw std::runtime_error("Invalid operator!");
    }
}

bool isUnary(char token, char prev){
    if (token == '+' || token == '-'){
        if (!isdigit(prev) && !(prev ==')')){
            return true;
        }
    }
    return false;
}

std::string parser(std::string expr){
    char prev = '(';
    std::string out= "";
    for(int i =0; i<expr.length();i++){
        if(isUnary(expr[i],prev)){
            out+= "0";
            out+= expr[i];
        }else{
            out+= expr[i];
        }
        prev = expr[i];
    }
    return out;
}

// Function to evaluate a given expression
double evaluateExpression(const std::string& expr) {
    std::stack<double> values; // Stack for storing numbers
    std::stack<char> ops;      // Stack for storing operators
    std::string numberBuffer;  // Buffer to accumulate digits of a number

    // Loop through each character in the expression
    for (int i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue; // Skip spaces

        // If the character is a digit or a decimal point, add it to the number buffer
        if (isdigit(expr[i]) || expr[i] == '.') {
            numberBuffer += expr[i];
        } else {
            // If number buffer is not empty, convert it to a number and push onto the stack
            if (!numberBuffer.empty()) {
                values.push(std::stod(numberBuffer));
                numberBuffer = "";
            }

            // Handling parentheses
            if (expr[i] == '(') {
                ops.push(expr[i]);
            } else if (expr[i] == ')') {
                // Evaluate the expression inside the parentheses
                while (!ops.empty() && ops.top() != '(') {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                if (!ops.empty()) ops.pop(); // Remove the '(' from the stack
            } else if (isOperator(expr[i])) {
                // If the current character is an operator, process the top of the stacks
                while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i])) {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                ops.push(expr[i]); // Push current operator to stack
            } else {
                throw std::runtime_error("Invalid input!"); // Error for invalid characters
            }
        }
    }

    // Push the last number in the buffer to the stack
    if (!numberBuffer.empty()) {
        values.push(std::stod(numberBuffer));
    }

    // Complete any remaining operations
    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top(); // Return the final result
}

int main() {
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);
    // Removes any whitespace in expression and trims the remaining string
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
    // Counts the number of ')' characters 
    int pEndCount = std::count(expression.begin(), expression.end(), ')');
    // Counts the number of '(' characters 
    int pStartCount = std::count(expression.begin(), expression.end(), '(');
    if (pEndCount != pStartCount) {
        std::cout << ("Unmatched parantheses")<< std::endl;
        return 1; 
    } else {
    }

    try {
        double result = evaluateExpression(parser(expression));
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
