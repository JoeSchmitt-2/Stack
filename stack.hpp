/*Joseph Schmitt
 *cop4530
 *proj3
*/
#ifndef STACK_HPP
#define STACK_HPP
#include "stack.h"
using namespace cop4530;

// zero-argument constructor.
template<typename T>
Stack<T>::Stack() : data()
{ }
//destructor
template<typename T>
Stack<T>::~Stack()
{
    clear();
}
//copy constructor
template<typename T>
Stack<T>::Stack(const Stack<T> &x)
{
    this->data = x.data;
}
//move contructor
template<typename T>
Stack<T>::Stack(Stack<T> &&x)
{
    this->data = std::move(x.data);
}
//copy assignment operator=
template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &rhs)
{
    Stack<T> copy = rhs;
    std::swap(*this, copy);
    return *this;
}
//move assignment operator=
template<typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&rhs)
{
    std::swap(data, rhs.data);
}
//copy version
template<typename T>
void Stack<T>::push(const T& x)
{
    this->data.push_back(x);
}
//mutator that returns a reference to most recent element
template<typename T>
T &Stack<T>::top()
{
    return this->data.back();
}
//returns true if empty
template<typename T>
bool Stack<T>::empty()
{
    return this->data.empty();
}
//removes and discards the most recent element
template<typename T>
void Stack<T>::pop()
{
    this->data.pop_back();
}
//delete all the elements from the stack
template<typename T>
void Stack<T>::clear()
{
    while(!empty())
        pop();
}
//move version
template<typename T>
void Stack<T>::push(const T &&x)
{
    this->data.push_back(std::move(x));
}
//returns the number of elements
template<typename T>
int Stack<T>::size() const
{
    return data.size();
}
//accessor that returns the most recently added element
template<typename T>
const T &Stack<T>::top() const
{
    return data.back();
}

template<typename T>
void Stack<T>::print(std::ostream &os, char ofc) const
{
    for(auto i = data.begin(); i != data.end(); i++)
    {
        os << *i;
        os << ofc;
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &a)
{
    a.print(os);
    return os;
}

template<typename T>
bool operator==(const Stack<T> &a, const Stack<T> &b)
{
    if(a.size() == b.size())
    {
        Stack<T> temp1, temp2;
        temp1 = a;
        temp2 = b;
        while(!temp1.empty() && !temp2.empty())
        {
            if(!temp1.top() != !temp2.top())
                return false;
            temp1.pop();
            temp2.pop();
        }
        return true;
    }
    else return false;
}

template<typename T>
bool operator!=(const Stack<T> &a, const Stack<T> &b)
{
    return (!(a == b));
}

template<typename T>
bool operator<=(const Stack<T> &a, const Stack<T> &b)
{
    if(a==b)
        return true;
    Stack<T> temp1, temp2;
    temp1 = a;
    temp2 = b;

    while(!temp1.empty())
    {
        if(temp2.empty())
            return true;
        if(temp1.top() > temp2.top())
            return false;
        temp1.pop();
        temp2.pop();
    }
    return true;
}


#endif
