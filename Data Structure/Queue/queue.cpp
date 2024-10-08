#include <bits/stdc++.h>
using namespace std;
class queueFunc {
    private:
    stack <int> stack1, stack2, stack3;
    vector <int> vec;
    public:
    void pushQueue(int a){
        stack1.push(a);
        ///getmin
        vec.push_back(a);
        sort(vec.begin(), vec.end());
    }
    void popQueue(){
        while(stack1.size() > 0){
            int a = stack1.top();
            stack1.pop();
            stack2.push(a);
        }
        int x = stack2.top();
        stack2.pop();
        while(stack2.size() > 0){
            int a = stack2.top();
            stack2.pop();
            stack1.push(a);
        }
        cout << "pop: " << x << endl;
        ///getmin
        remove(vec.begin(),vec.end(), x);
        sort(vec.begin(), vec.end()); 
    }
    void printQueue(){
        while(stack1.size() > 0){
            int a = stack1.top();
            stack1.pop();
            stack2.push(a);
        }
        while(stack2.size() > 0){
            int a = stack2.top();
            stack2.pop();
            cout << a << " ";
            stack1.push(a);
        }
        cout << endl;
    }
    int getmin(){
        //O(1)
        vector <int>:: iterator it;
        it = vec.begin();
        return *it;
    }
    void reverseQueue(){
        //O(n)
        while(stack1.size() > 0){
            int a = stack1.top();
            stack1.pop();
            stack2.push(a);
        }
        while(stack2.size() > 0){
            int a = stack2.top();
            stack2.pop();
            stack3.push(a);
        }
        while(stack3.size() > 0){
            int a = stack3.top();
            stack3.pop();
            stack1.push(a);
        }
    }


};
int main(){
    string cmn;
    queueFunc q;
    while(true){
        cin >> cmn;
        if(cmn == "push"){
            int a;
            cin >> a;
            q.pushQueue(a);
        }
        if(cmn == "pop"){
            q.popQueue();
        }
        if(cmn == "revese"){
            q.reverseQueue();
        }
        if(cmn == "getmin"){
            cout << "min: " << q.getmin() << endl;
        }
        if(cmn == "print"){
            q.printQueue();
            cout << "***********" << endl;
        }
    }
    return 0;
}