#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 100;

struct Stack {
    int top; // index of top of stack
    string elements[MAX_SIZE];
};

bool isEmpty(Stack& stack) {
    return stack.top == -1;
}

bool isFull(Stack& stack) {
    return stack.top == MAX_SIZE - 1;
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
        return "";
    }
    return stack.elements[stack.top];
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

void postfix(Stack& stack, string phrase) {
    for (int i = 0; i < phrase.size(); i++) {
        string p = string(1, phrase[i]);
        if (p >= "0" && p <= "9" || p >= "a" && p <= "z") {
            string number;
            while (p >= "0" && p <= "9" || p >= "a" && p <= "z") {
                number += p;
                i++;
                if (i < phrase.size()) {
                    p = string(1, phrase[i]);
                } else {
                    break;
                }
            }
            i--; 
            cout << number << " ";
        } else if (p == "(" || p == ")" || p == "{" || p == "}" || p == "[" || p == "]") {
            push(stack, p);
        } else {
            while (true) {
                if (isEmpty(stack) || top(stack) == "(" || top(stack) == "[" || top(stack) == "{") {
                    push(stack, p);
                    break;
                } else if (top(stack) == "+" || top(stack) == "-" || top(stack) == "/" ||
                           top(stack) == "*") {
                    if ((p == "*" || p == "/") && (top(stack) == "-" || top(stack) == "+")) {
                        push(stack, p);
                        break;
                    } else {
                        if (top(stack) != "(" && top(stack) != ")" && top(stack) != "{" &&
                            top(stack) != "}" && top(stack) != "[" && top(stack) != "]") {
                            cout << top(stack) << " ";
                        }
                        pop(stack);
                    }
                } else {
                    break;
                }
            }
        }
    }
    while (!isEmpty(stack)) {
        string p = top(stack);
        if (p != "(" && p != ")" && p != "{" && p != "}" && p != "[" && p != "]") {
            cout << p << " ";
        }
        pop(stack);
    }
}

int main() {
    Stack stack;
    stack.top = -1;
    string str;
    cout << "Enter the phrase: ";
    getline(cin,str);
    postfix(stack, removeSpaces(str));

    return 0;
}

/*
    Reza Asadi (Github : RezaGooner)
	1402/08/22 ~ 2023/11/13
*/