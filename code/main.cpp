#include <iostream>
#include "stack.h"
#include <string>
#include <sstream>

int precedence(char op) {
// Switch statement to determine precedence
    switch (op) {
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

bool isOperator(char c) {
// Function to determine if a character is an operator
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

Stack convertToRPN(const std::string& expr) {
    // Function to convert an infix expression to RPN

    // Create stacks for operators and output
    Stack operators;
    Stack output;

    // Loop through each character in the expression
    for (int i = 0; i < expr.length(); i++) {
        char token = expr[i];
        char next = expr[i + 1];
        if (isspace(token)) {
            // Ignore whitespace
            continue;
        } else if (!(isdigit(token) || isOperator(token) || token == '(' || token == ')')) {
            // Throw an error if the character is not a digit, operator, or parenthesis
            throw std::runtime_error("Invalid character in expression");
        } else if (isdigit(token)) {
            // If the character is a digit, push it to the output stack
            output.push(token);
        } else if (token == '(') {
            // If the character is a left parenthesis, push it to the operator stack
            operators.push(token);
        } else if (token == ')') {
            // If the character is a right parenthesis, pop operators from the operator stack to the output stack until a left parenthesis is found
            while (!operators.empty() && operators.peek() != '(') {
                output.push(operators.pop());
            }
            operators.pop(); // Remove '('
        } else if (isOperator(token)) {
            // If the character is an operator,
            if (!isdigit(next)) {
                // If the next character is not a digit, throw an error
                throw std::runtime_error("Invalid expression");
            }

            // pop operators from the operator stack to the output stack until either: 
            // an operator with lower precedence is found
            // the operator stack is empty
            // the operator is a right associative operator (^)
            while (   (!operators.empty()) && (precedence(operators.peek()) >= precedence(token)) && (token != '^')) {
                output.push(operators.pop());
            }
            operators.push(token);
        }
    }

    // Pop any remaining operators from the operator stack to the output stack
    while (!operators.empty()) {
        output.push(operators.pop());
    }

    // Reverse the output stack and return it
    Stack reversed = output.reverse();
    return reversed;
}

int main() {
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);

    Stack rpn = convertToRPN(expression);
    std::cout << "RPN: " << rpn << std::endl;


    return 0;
}
