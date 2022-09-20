/*Joseph Schmitt
 *cop4530
 *proj3
*/
#include "stack.h"
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;
using namespace cop4530;

Stack<string> operators_stack;
Stack<double> operand_stack;
vector<string> infix;
vector<string> postfix;
string infixExpression;

//checks to see if there is letters
bool has_variable(const string& x)
{
    for(int i = 0; i < x.length(); i++)
    {
        if(isalpha( x[i] ))
            return true;
        else
            return false;
    }
}
//checks for operands
bool find_operator(const string& x)
{
    for(int i = 0; i < x.length(); i++)
    {
        if( x[i] == '*' || x[i] == '+'
            || x[i] == '-' || x[i] == '/'
            || x[i] == '(' || x[i] == ')')
            return true;
        else
            return false;
    }
}
//separates the string(infix expression) into tokens in a vector
void tokenize(string const &str, const char delim, vector<string> &out)
{
    size_t start;
    size_t end = 0;
    while((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
         out.push_back(str.substr(start, end - start));
    }
}
//gives precedence to the operators
int precedence(const string &operatorP)
{
    if(operatorP == "*" || operatorP == "/")
        return 2;
    else if(operatorP == "+" || operatorP == "-")
        return 1;
    else
        return -1;
}
//change to postfix expression
void change2Postfix(vector<string> &x)
{
    for(auto &infixExpression: infix)
    {
        if(!find_operator(infixExpression))
        {
            postfix.push_back(infixExpression);
        }
        else if(find_operator(infixExpression))
        {
            if(infixExpression == "(")
            {
                operators_stack.push(infixExpression);
            }
            else if(infixExpression == ")")
            {
                while(!operators_stack.empty() && operators_stack.top() != "(")
                {
                    string temp = operators_stack.top();
                    operators_stack.pop();
                    postfix.push_back(temp);
                }
                if(operators_stack.top() == "(")
                {
                    string temp = operators_stack.top();
                    operators_stack.pop();
                }
            }
            else{
                while(!operators_stack.empty() && precedence(infixExpression) <=
                        precedence(operators_stack.top()))
                {
                    string temp = operators_stack.top();
                    operators_stack.pop();
                     postfix.push_back(temp);
                }
                operators_stack.push(infixExpression);
            }
        }
    }
    //pop remaining elements from stack
    while(!operators_stack.empty())
    {
        string temp = operators_stack.top();
        operators_stack.pop();
        postfix.push_back(temp);
    }
}
//does the arithmetic of the function
double arithmetic4Postfix(const string& wOperator, double lhs, double rhs)
{
    if(wOperator == "*")
        return lhs * rhs;
    else if(wOperator == "/")
        return lhs / rhs;
    else if(wOperator == "+")
        return lhs + rhs;
    else if(wOperator == "-")
        return lhs - rhs;
    else
        return -1;
}
//this function evaluates the postfix vector using Stacks
void evaluatePostfix()
{
    bool eval = true;
    for(string& anyExpression: postfix)
    {
        if(has_variable(anyExpression))
        {
            eval = false;
            for(auto postfixExpression: postfix)
                cout << postfixExpression << ' ';
            break;
        }

    }

    for(string& anyExpression: postfix)
    {
        if(eval == false)
        {
            break;
        }
        else{

            if(!find_operator(anyExpression))
                operand_stack.push(stod(anyExpression));
            else{
                double lhs, rhs;

                rhs = operand_stack.top();
                operand_stack.pop();

                lhs = operand_stack.top();
                operand_stack.pop();

                operand_stack.push(arithmetic4Postfix(anyExpression, lhs, rhs));
            }
        }
    }
    operand_stack.print(cout, ' ');
}
//resets and cleans up for new expression
void newExpression()
{
    operators_stack.clear();
    operand_stack.clear();
    infixExpression = "";
    infix.clear();
    postfix.clear();
}
//error checking
void errorChecking()
{
    bool noErrors = false, tracker = false;

    while(noErrors == false) {
        for (int i = 0; i < infix.size(); i++)
        {
            if (infix.at(i) == "(") {
                tracker = true;
                for (int j = i; j < infix.size(); j++)
                {
                    if (infix.at(j) == ")") {
                        tracker = true;
                        noErrors = true;
                        break;
                    } else
                        noErrors = false;
                }
            }
            else if (tracker == false && infix.at(i) == ")")
            {
                tracker = true;
                noErrors = false;
                break;
            }
            else
                continue;
        }
        if (tracker == false)
            noErrors = true;
        for (int i = 0; i < infix.size(); i++)
        {
            if((i < infix.size() - 1) && has_variable(infix.at(i)) &&
            !find_operator(infix.at(i + 1)))
            {
                noErrors = false;
                break;
            }
        }
        if(noErrors == false)
        {
            newExpression();
            cout << "Invalid entry. Check spacing/operators/operands/parenthesis and try again" << endl;
            cout << "Enter infix expression ('exit' to quit): ";
            getline(cin, infixExpression);
            tokenize(infixExpression, ' ', infix);
        }
    }
}
//main function
int main()
{
    cout << "Enter infix expression ('exit' to quit): ";
    //main program loop
    while(getline(cin,infixExpression) && infixExpression != "exit")
    {
        //checks for input
        if(!isatty(STDIN_FILENO))
            cout << endl;

        //set the input into tokens and store them in the infix vector
        tokenize(infixExpression, ' ', infix);
        
        errorChecking();

        //change the infix vector and store in postfix vector
        change2Postfix(infix);

        //menu loop
        cout << "Postfix expression: ";
        for(auto postfixExpression: postfix)
            cout << postfixExpression << ' ';
        cout << endl;

        cout << "Postfix evaluation: ";

        //evaluate the postfix expression
        evaluatePostfix();

        cout << endl;
        cout << "Enter infix expression('exit' to quit): ";

        //reset for a new expression
        newExpression();
    }//end of main program loop
}
