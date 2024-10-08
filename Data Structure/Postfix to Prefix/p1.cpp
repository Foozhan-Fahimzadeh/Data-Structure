#include <bits/stdc++.h>
using namespace std;
stack <char> st;
int main(){
    string str;
    cin >> str;
    for(int i = 0; i < str.size(); i ++){
        if(str[i] == '*' or str[i] == '/' or str[i] == '+' or str[i] == '-' or str[i] == '^' or str[i] == '%'){
            char x = st.top();
            st.pop();
            st.push(str[i]);
            st.push(x);
        }
        else{
            st.push(str[i]);
        }
    }
    for(int i = 0; i < str.size(); i ++){
        str[i] = st.top();
        st.pop();
    }
    for(int i = str.size() -1; i >= 0; i --)
    cout << str[i];
    return 0;
}