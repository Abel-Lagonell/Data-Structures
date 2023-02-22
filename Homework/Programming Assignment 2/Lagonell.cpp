/**
 * @file Lagonell.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief 
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// C++ program to check for balanced brackets.
#include <bits/stdc++.h>
using namespace std;

bool isBalanced(string str) {
    stack<char> s;
    char x;
    
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            s.push(str[i]);
            continue;
        }
        
        if (s.empty()) {
            return false;
        }
        
        switch (str[i]) {
            case ')':
                x = s.top();
                s.pop();
                if (x == '{' || x == '[') {
                    return false;
                }
                break;
            case '}':
                x = s.top();
                s.pop();
                if (x == '(' || x == '[') {
                    return false;
                }
                break;
            case ']':
                x = s.top();
                s.pop();
                if (x == '(' || x == '{') {
                    return false;
                }
                break;
        }
    }
    
    return (s.empty());
}

// Driver code
int main()
{
    string expr = "{()}[abc]";
    // Function call
    if (isBalanced(expr))
        cout << "Balanced"<<endl;
    else
        cout << "Not Balanced"<<endl;
    return 0;
}
