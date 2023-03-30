//
//  eval.cpp
//  Homework2
//
//  Created by Impana on 2/7/23.
//

#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

//declarations of any additional functions you might have written
//        to help you evaluate an expression
int convert(string infix, string& postfix);

//implementations of any additional functions you might have written
//        to help you evaluate an expression

int convert(string infix, string& postfix){
    string infix2 = "";
    postfix = "";
    for (int i=0; i<infix.length(); i++){
        if (!isspace(infix[i]))
            infix2 += infix[i];
    }
    if (infix2 == "()") return 1;
    stack<ItemType> opStack;
    for (int i=0; i<infix2.length(); i++){
        char cur = infix2[i];
        if (islower(cur)) {
            if ( (i>=1) && ((islower(infix2[i-1])) || (infix2[i-1]==')')) )
                return 1;
            if ( (i<infix2.length()-1) && ((islower(infix2[i+1])) || (infix2[i+1]=='(') || (infix2[i+1]=='!')) )
                return 1;
            postfix += cur;
        } else if ((cur == '(') || (cur=='!')) {
            if (cur=='!'){
                if ( (islower(infix2[i-1])) || (infix2[i-1]==')') )
                    return 1;
                if ( (i==infix2.length()-1) || (infix2[i+1]==')') || (infix2[i+1]=='&') || (infix2[i+1]=='|') )
                    return 1;
            }
            opStack.push(cur);
        }
        else if (cur == ')'){
            while(opStack.top() != '('){
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.pop();
        }
        else if ((cur=='&') || (cur=='|')){
            if ( (i==0) || (infix2[i-1]=='&') || (infix2[i-1]=='|') || (infix2[i-1]=='!') || (infix2[i-1]=='(') )
                return 1;
            if ( (i==infix2.length()-1) || (infix2[i+1]=='&') || (infix2[i+1]=='|') || (infix2[i+1]==')') )
                return 1;
            while ( (!opStack.empty()) && (opStack.top()!='(') && (cur>=opStack.top()) ){
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(cur);
        }
        else
            return 1;
    }
    while (!opStack.empty()){
        postfix += opStack.top();
        if (opStack.top() == '(')
            return 1;
        opStack.pop();
    }
    return 0;
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result){
    if ((infix=="") || (convert(infix, postfix) == 1))
        return 1;
    
    //cerr << postfix << endl;
    stack<ItemType> opStack;
    for (int i=0; i<postfix.length(); i++){
        if (islower(postfix[i])){
            if (!trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
                return 2;
            if (trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]))
                return 3;
            opStack.push(postfix[i]);
        } else {
            ItemType tVal;
            trueValues.get(0,tVal);
            ItemType fVal;
            falseValues.get(0,fVal);
            
            ItemType op2 = opStack.top();
            opStack.pop();
            if (postfix[i] == '!'){
                if (trueValues.contains(op2))
                    opStack.push(fVal);
                else
                    opStack.push(tVal);
            } else {
                ItemType op1 = opStack.top();
                opStack.pop();
                switch (postfix[i]){
                    case '&':
                        if ((trueValues.contains(op1)) && (trueValues.contains(op2)))
                            opStack.push(tVal);
                        else
                            opStack.push(fVal);
                        break;
                    case '|':
                        if ((trueValues.contains(op1)) || (trueValues.contains(op2)))
                            opStack.push(tVal);
                        else
                            opStack.push(fVal);
                        break;
                }
            }
        }
    }
    ItemType finOp = opStack.top();
    if (trueValues.contains(finOp))
        result = true;
    else
        result = false;
    return 0;
}

int main(){
    string trueChars1  = "ucla";
    string falseChars1 = "nsx";
    Set trues1;
    Set falses1;
    for (int k = 0; k < trueChars1.size(); k++)
        trues1.insert(trueChars1[k]);
    for (int k = 0; k < falseChars1.size(); k++)
        falses1.insert(falseChars1[k]);
    
    string pf;
    bool answer;
    assert(evaluate("u", trues1, falses1, pf, answer) == 0  &&  answer);
    assert(evaluate("u&c&l&a & !(u&s&c) ", trues1, falses1, pf, answer) == 0 && answer);
    assert(evaluate("(n)", trues1, falses1, pf, answer) == 0  &&  !answer);
    assert(evaluate("a&(s)", trues1, falses1, pf, answer) == 0 &&  !answer);
    assert(evaluate("a & !s", trues1, falses1, pf, answer) == 0  &&  answer);
    assert(evaluate("!(n|u)", trues1, falses1, pf, answer) == 0  &&  !answer);
    assert(evaluate("!n|u", trues1, falses1, pf, answer) == 0  &&  answer);
    assert(evaluate("a|n&n", trues1, falses1, pf, answer) == 0  &&  answer);
    assert(evaluate("!!a", trues1, falses1, pf, answer) == 0  &&  answer);
    assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", trues1, falses1, pf, answer) == 0  && answer);
    cerr << "---1. Passed all tests---" << endl;
    
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("()z", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("n+y", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
                           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cerr << "---2. Passed all tests---" << endl;
    
    Set trues2;
    Set falses2;
    assert(evaluate("x", trues2, falses2, pf, answer) == 2);
    
    string trueChars3  = "abc";
    string falseChars3 = "abd";
    Set trues3;
    Set falses3;
    for (int k = 0; k < trueChars3.size(); k++)
        trues3.insert(trueChars3[k]);
    for (int k = 0; k < falseChars3.size(); k++)
        falses3.insert(falseChars3[k]);
    assert(evaluate("a", trues3, falses3, pf, answer) == 3);
    cerr << "---3. Passed all tests---" << endl;
    
}
