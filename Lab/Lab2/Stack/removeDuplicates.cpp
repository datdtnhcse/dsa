#include <iostream>
#include <stack>

using namespace std;

string removeDuplicates(string S) {
    stack<char> the_stack;
    int index = 0;
     
    while (index < (int)S.size()) {
        if (the_stack.empty() || S[index] != the_stack.top()) {
            the_stack.push(S[index]);
            ++index;
        } else {
            the_stack.pop();
            ++index;
        }
    }
     
    if (S.empty()) {
        return ("NULL");
    } else {
        string returned_string = "";
        while (!the_stack.empty()) {
            returned_string = the_stack.top() + returned_string;
            the_stack.pop();
        }
        return (returned_string);
    }
}

