#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

queue<string> getInput(){
    queue<string> Q;
    string token;
    cin >> token;
    // TODO: loop and input rest of expression, adding to queue
    // Do not add the sentinel # to the queue.
    while (token != "#"){
        Q.push(token);
        cin >> token;
    }
    return Q;
}

bool evaluatePostfix(queue<string> input, int& result) {
    stack<int> operands;
    // evaluate expression:
    //first traverse
    while (!input.empty()){
        string s = input.front();
        input.pop();
        if (isdigit(s[0])){
            operands.push(stoi(s));
        }
        else{
            if (operands.size() < 2) return false;
            int op1 = operands.top();
            operands.pop();
            int op2 = operands.top();
            operands.pop();
            int result;
            if (s == "+") result = op1 + op2;
            else if (s == "-") result = op2 - op1;
            else if (s == "*") result = op1 * op2;
            else if (s == "/") result = op2/op1;
            else return false;
            operands.push(result);
        }
    }

    result = operands.top();  // answer is on top
    return true;  // successful evaluation
}


int main()
{
    queue<string> input = getInput();
    if (input.empty()){
        cout << "invalid" << endl;
        return 0;
    }
    int result = 0;
    if (evaluatePostfix(input, result)){

        cout << result << endl;
    }
    else cout << "Invalid" << endl;

    return 0;
}
