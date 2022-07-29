#include <iostream>
#include <stack>

using namespace std;

bool isValidParentheses(string s) {
    if (s[0] == '}' || s[0] == ')' || s[0] == ']') return 0;
    stack<char> st;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '{' || s[i] == '(' || s[i] == '[') st.push(s[i]);
        else if (s[i] == '}' || s[i] == ')' || s[i] == ']') {
            if (s[i] == '}') {
                if (st.top() == '{') {
                    st.pop();
                    continue;
                } else return 0;
            }
            if (s[i] == ')') {
                if (st.top() == '(') {
                    st.pop();
                    continue;
                } else return 0;
            }
            if (s[i] == ']') {
                if (st.top() == '[') {
                    st.pop();
                    continue;
                } else return 0;
            }
        }
    }
    if (st.empty()) return 1;
    return 0;
}

int main() {
    cout << isValidParentheses("]");

}