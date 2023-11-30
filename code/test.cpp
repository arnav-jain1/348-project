#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) {
    return std::string("+-*/%^").find(c) != std::string::npos;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw std::runtime_error("Division by zero!");
            return a / b;
        case '%': return fmod(a, b);
        case '^': return pow(a, b);
        default: throw std::runtime_error("Invalid operator!");
    }
}

double evaluateExpression(const std::string& expr) {
    std::stack<double> values;
    std::stack<char> ops;
    std::string numberBuffer;

    for (int i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i]) || expr[i] == '.') {
            numberBuffer += expr[i];
        } else {
            if (!numberBuffer.empty()) {
                values.push(std::stod(numberBuffer));
                numberBuffer = "";
            }

            if (expr[i] == '(') {
                ops.push(expr[i]);
            } else if (expr[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                if (!ops.empty()) ops.pop();
            } else if (isOperator(expr[i])) {
                while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i])) {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                ops.push(expr[i]);
            } else {
                throw std::runtime_error("Invalid input!");
            }
        }
    }

    if (!numberBuffer.empty()) {
        values.push(std::stod(numberBuffer));
    }

    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
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
        throw std::runtime_error("Unmatched parantheses");
    } else {
    }

    try {
        double result = evaluateExpression(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
