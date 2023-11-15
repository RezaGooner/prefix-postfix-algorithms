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
        //cout << "Stack overflow!" << endl;
        return;
    }
    stack.elements[++stack.top] = value;
}

void pop(Stack& stack) {
    if (isEmpty(stack)) {
        //cout << "Stack underflow!" << endl;
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

string prefixToInfix(string prefixPhrase) {
    Stack stack;
    stack.top = -1;

    int length = prefixPhrase.length();

    for (int i = length - 1; i >= 0; i--) {
        char currentChar = prefixPhrase[i];

        if (isOperator(currentChar)) {
            string operand1 = top(stack);
            pop(stack);

            string operand2 = top(stack);
            pop(stack);

            string newPhrase = "(" + operand1 + currentChar + operand2 + ")";
            push(stack, newPhrase);
        } else {
            push(stack, string(1, currentChar));
        }
    }

    return top(stack);
}

string postfixToInfix(string postfixPhrase) {
    Stack stack;
    stack.top = -1;

    int length = postfixPhrase.length();

    for (int i = 0; i < length; i++) {
        char currentChar = postfixPhrase[i];

        if (isOperator(currentChar)) {
            string operand2 = top(stack);
            pop(stack);

            string operand1 = top(stack);
            pop(stack);

            string newPhrase = "(" + operand1 + currentChar + operand2 + ")";
            push(stack, newPhrase);
        } else {
            push(stack, string(1, currentChar));
        }
    }
    return top(stack);
}

int main() {
    string prefixPhrase;
    cout << "Enter prefix phrase, for example '+*AB-CD' : ";
    cin >> prefixPhrase;
    string infixPhrase = prefixToInfix(prefixPhrase);

    cout << "Prefix to Infix Phrase: " << infixPhrase << endl;

    string postfixPhrase;
    cout << "Enter postfix phrase, for example'AB*CD-+' : ";
    cin >> postfixPhrase;
    infixPhrase = postfixToInfix(postfixPhrase);

    cout << "Postfix to Infix Phrase: " << infixPhrase << endl;

    return 0;
}

/*
    Reza Asadi (Github : RezaGooner)
	1402/08/25 ~ 2023/11/16
*/