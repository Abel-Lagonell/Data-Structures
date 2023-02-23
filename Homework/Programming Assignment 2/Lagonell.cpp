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
#include <fstream>

using namespace std;

int balanced_string(string s) {
    stack<char> st;
    int failurePoint = 0,
        prevPoint = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            st.push(s[i]);
            if(prevPoint != failurePoint){
                failurePoint = i;
            }
            if(prevPoint == failurePoint){
                prevPoint = failurePoint;
                failurePoint = i;
            }
            
        } else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            if (st.empty()) {
                return i+1;
            } else if((st.top() == '(' && s[i] == ')') || (st.top() == '{' && s[i] == '}') || (st.top() == '[' && s[i] == ']')){
                st.pop();
                failurePoint = prevPoint;
            }
            else 
                return i+1;
        }
    }
    if (!st.empty())
        return failurePoint+1;
    return -1;
}

// Driver code
int main()
{
    string expr;
    ifstream MainFile("mergedFile.txt");
    ifstream SampleFile("sample.txt");
    int count = 1;
    while (getline(SampleFile, expr))
    {
        int temp = balanced_string(expr);
        if (temp == -1)
            cout << "Sample " << count << ". Success"<<endl;
        else
            cout << "Sample " << count << ". " << temp <<endl;
        count++;
    }
    count =0;
    while (getline(MainFile, expr))
    {
        int temp = balanced_string(expr);
        if (temp == -1)
            cout << count << ". Success"<<endl;
        else
            cout << count << ". " << temp <<endl;
        count++;
    }
    return 0;
}
