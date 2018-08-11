//
//  main.cpp
//  eval
//
//  Created by Elizabeth Han on 2/6/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include  <cctype>
#include <cassert>


using namespace std;

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    stack<char> charStack;
    string tempfix = "";
    
    //////////ACCOUNTS FOR NO DIGITS//////////
    int counter = 0;
    for (int i=0; i!= infix.size(); i++)
    {
        if (isdigit(infix[i]))
            counter++;
    }
    if (counter==0)
        return 1;
    /////////////////////
    
    //ACCOUNTS FOR PARENTHESES WITHOUT OPERATORS / MULTIPLE DIGITS WITHOUT OPERATORS
    
    for (int i=0; i+1!= infix.size(); i++) //should account for parenthesis without operators
    {
        
        if (isdigit(infix[i]) && (infix[i+1]== '!' || infix[i+1]== '('|| isdigit(infix[i+1])))
            return 1;
    }
    ////////////////AND DIGITS WITH A UNARY OPERATOR AFTER THEM
    
    ////////////ACCOUNTS FOR TOO MANY/NOT ENOUGH PARANTHESES
    int open = 0, close=0;
    for (int i=0; i!= infix.size(); i++)
    {
        if (infix[i]== '(')
            open++;
        else if (infix[i]==')')
            close++;
    }
    if (open!=close)
        return 1;
    /////////////////////////
    
    //BEGIN WITH THE CODE : INFIX TO POSTFIX
    for (int i = 0; i!= infix.size(); i++)
    {
        if (isdigit(infix[i])) // case operand
            tempfix+= infix[i];
        else if (infix[i]=='(') // case '('
            charStack.push(infix[i]);
        else if (infix[i]==')')
        {
            if (charStack.empty()) // parantheses weirdness
                return 1;
            while (charStack.top()!= '(') // case '('
            {
                tempfix+=charStack.top();
                charStack.pop();
            }
            charStack.pop(); //gets rid of the extra parenthesis;
        }
        else if (infix[i] == '!' || infix[i] == '|' || infix[i] == '&' )// if we have our operators
        {
            if (infix[i] == '|' && !charStack.empty())
            {
                while(!charStack.empty())
                {
                    if (charStack.top()== '(')
                        break;
                    tempfix+= charStack.top();
                    charStack.pop();
                }
            }
            
            else if (infix[i] == '&' && !charStack.empty())
            {
                while(!charStack.empty())
                {
                    if (charStack.top()=='(' ||charStack.top()=='|')
                        break;
                    tempfix+= charStack.top();
                    charStack.pop();
                }
            }
            
            charStack.push(infix[i]); //no need to account for ! since greatest precedence
        }
        
        else if (infix[i] != ' ') //ignoring spaces!
            return 1;
        
    }
    while (!charStack.empty()) //pop off all remaning operators
    {
        
        tempfix += charStack.top();
        charStack.pop();
    }
    /// //////////////////POSTFIX TO EVALUATION
    stack<bool> operand;
    
   
    ///////IF NUMBERS BUT NO OPERATORS (in case infix doesn't catch it)
    int ator = 0, rand = 0;
    for (int i=0; i!= tempfix.size(); i++)
    {
        if (isdigit(tempfix[i]))
            rand++;
        else if (tempfix[i]== '&' || tempfix[i]== '|'||tempfix[i]=='!')
            ator++;
    }
    
    if (rand > 1 && ator==0)
        return 1;
    ////////////
    
    
  /*  for (int i=0; i!= tempfix.size(); i++) //if there are any paranthesis left in here, you fucked up
    {
        if (tempfix[i]== '('||tempfix[i]== ')')
            return 1;
    }
   */

    ///BEGIN POSTFIX TO EVALUATION

    
    for (int i=0; i!= tempfix.size(); i++)
    {
        bool answer;
        if (isdigit(tempfix[i]))
        {
            int k = tempfix[i] - '0';
            if (k < 0 || k >= 10) //check to see if valid position
                return 1;
            operand.push(values[k]); //if so, push onto stack
        }
        else if (tempfix[i]== '&' || tempfix[i]== '|' ) //if binary operator
        {
            
            if (operand.empty()) //if operand stack empty, but there's an operator around, you messed up
                return 1;
            bool operand2 = operand.top(); operand.pop();
            
            if (operand.empty()) //check to see that there are at least two operands
                return 1;
            bool operand1 = operand.top(); operand.pop();
            
            if (tempfix[i]=='|')
                answer = operand1 | operand2 ; //evaluate |
            else if (tempfix[i]=='&')
                answer = operand1 & operand2; //evaluate &
            operand.push(answer);
        }
        else if (tempfix[i]=='!') //if unary operator
        {
            if (operand.empty()) //only need to check if there's one operator
                return 1;
            else
            {
                bool operand1 = operand.top(); operand.pop();
                answer = !operand1;
                operand.push(answer);
            }
            
        }
        
    }
    postfix = tempfix; //finally give postfix a value
    result = operand.top(); //what's left in operand stack should be result
    
    return 0;
}
int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    
    
    assert(evaluate("", ba, pf, answer) == 1); //empty string
    assert(evaluate("()", ba, pf, answer) == 1); //essentially empty string
    assert(evaluate(")(", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1); //lack of closing brace
    assert(evaluate("6&7|7)", ba, pf, answer) == 1);  //no open brace
    assert(evaluate("6&(7|7))", ba, pf, answer) == 1); //too many closing braces
    assert(evaluate("6)!(6", ba, pf, answer) == 1); //parentheses weirdness
    assert(evaluate("6)(6", ba, pf, answer) == 1);
    assert(evaluate("6(&)6)", ba, pf, answer) == 1); //parantheses enclosing operator
    assert(evaluate(";jklafdsjklafdsjkl", ba, pf, answer) == 1); //string of invalid items
    assert(evaluate("4 5", ba, pf, answer) == 1); //no operators
    assert(evaluate("&", ba, pf, answer) == 1); //single binary operator
    
    assert(evaluate("1!", ba, pf, answer) == 1);//postfix function
    assert(evaluate("&4", ba, pf, answer) == 1); //binary operator before digit
    assert(evaluate("8|", ba, pf, answer) == 1); //binary operator after digit
     assert(evaluate("|8|", ba, pf, answer) == 1); // binary operator before and after digit
    assert(evaluate("1!1!", ba, pf, answer) == 1); //unary operator after digit
    assert(evaluate("!1!1!", ba, pf, answer) == 1); //unary operator before AND after digit
    assert(evaluate("2(9|8)", ba, pf, answer) == 1); //lacking a neccessary operator
    assert(evaluate("2(&8)", ba, pf, answer) == 1); //lacking a neccessary operator and operand
    assert(evaluate("1911&|9|!&91&9&!!!|", ba, pf, answer) == 1); //giant postfix function
    assert(evaluate("2&(9||8)", ba, pf, answer) == 1);
    
    ////VALID INFIX FUNCTIONS
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
        //single digit
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
        //simple infix function
     assert(evaluate("!!!!1", ba, pf, answer) == 0); //multiple nots
    assert(evaluate("1&!(9|1&1|9) | !!!(9&1&9)", ba, pf, answer) == 0  &&  pf == "1911&|9|!&91&9&!!!|" &&  answer); //large and confusing
    assert(evaluate("1 & ! ( 9 | 1 & 1 | 9) | ! ! ! ( 9 & 1 & 9 )", ba, pf, answer) == 0  &&  pf == "1911&|9|!&91&9&!!!|" &&  answer); //large and confusing
    assert(evaluate("2&(3) ", ba, pf, answer) == 0  &&  pf == "23&" &&  !answer);
        //contains parantheses used correctly
    assert(evaluate("!(7|8)", ba, pf, answer) == 0  &&  !answer);
        //unary applied to larger expression
    assert(evaluate("!7|8", ba, pf, answer) == 0  &&  answer);
        //unary applied to only single with binary after
    assert(evaluate(" 6|4&5 ", ba, pf, answer) == 0  &&  answer);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
           &&  pf == "43!03&&|"  &&  !answer);
    

    
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer); //multiple parantheses
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
   
    
}

