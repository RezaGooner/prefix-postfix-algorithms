#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 100;

struct Stack {
    int top; // index of top of stack
    string elements[MAX_SIZE];
};

bool isEmpty(Stack& stack) {
    if (stack.top == -1) {
        return true;
    }
    return false;
}

bool isFull(Stack& stack) {
    if (stack.top == MAX_SIZE - 1) {
        return true;
    }
    return false;
}

void push(Stack& stack, string value) {
    if (isFull(stack)) {
        cout << "Stack overflow!" << endl;
        return;
    }
    stack.elements[++stack.top] = value;
}

void pop(Stack& stack) {
    if (isEmpty(stack)) {
        cout << "Stack underflow!" << endl;
        return;
    }
    stack.elements[stack.top--] = "";
}

string top(Stack& stack) {
    if (isEmpty(stack)) {
        // cout << "Stack is empty!" << endl;
        return "";
    }
    return stack.elements[stack.top];
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

string removeSpaces(string str) {
    string result;
    for (int i = 0 ; i < str.size() ; i++) {
        if (str[i] != ' ') {
            result += str[i];
        }
    }
    return result;
}

string prefix(Stack& stack ,string infixExpression) {
    string prefixExpression;
    for (int i = infixExpression.size() - 1; i >= 0; i--) {
        char currentChar = infixExpression[i];
        if (currentChar == ')' || currentChar == '}' || currentChar == ']') {
            string str(1, currentChar);
            push(stack, str);
        } else if (isOperator(currentChar)) {
            while (!isEmpty(stack) && isOperator(top(stack)[0]) && getPrecedence(currentChar) <= getPrecedence(top(stack)[0])) {
                prefixExpression += top(stack) + " ";
                pop(stack);
            }
            string str(1, currentChar);
            push(stack, str);
        } else if (currentChar == '(' || currentChar == '{' || currentChar == '[') {
            while (!isEmpty(stack) && isOperator(top(stack)[0])) {
                prefixExpression += top(stack) + " ";
                pop(stack);
            }
            pop(stack); // remove corresponding closing parenthesis
        } else {
            string operand;
            while ( (i >= 0 && isdigit(infixExpression[i])) || (i >= 0 && isalpha(infixExpression[i]) ))  {
                operand = infixExpression[i] + operand;
                i--;
            } 
            // reverse
			string tempOp ; 
            for (int i = operand.size() -1 ; i >= 0 ; i--){
            	tempOp += operand[i] ;
			}
			
            i++; // adjust the index after the loop
            prefixExpression += tempOp + " ";
        }
    }
    while (!isEmpty(stack)) {
        prefixExpression += top(stack) + " ";
        pop(stack);
    }
    // Reverse the prefix expression
    string reversedPrefixExpression;
    for (int i = prefixExpression.size() - 1; i >= 0; i--) {
        reversedPrefixExpression += prefixExpression[i];
    }
    return reversedPrefixExpression;
}

int main() {
	Stack stack;
    stack.top = -1;
    string infixExpression;
    cout << "Enter the infix phrase: ";
    getline(cin, infixExpression);

    cout << prefix(stack , removeSpaces(infixExpression)) ;

    return 0;
}

/*
    Reza Asadi (Github : RezaGooner)
	1402/08/24 ~ 2023/11/15
*/