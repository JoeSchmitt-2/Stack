/*Joseph Schmitt
 *cop4530
 *proj3
*/
#ifndef DL_LIST_H
#define DL_LIST_H
#include <iostream>
#include <vector>
using namespace std;
namespace cop4530 {

    template <typename T>
    class Stack
    {
        private:
            vector<T> data;

        public:
            void push (const T& x);
            bool empty();
            T& top();
            void pop();

            void clear();
            void push(const T && x);
            const T& top() const;
            int size() const;
            void print(std::ostream& os, char ofc = ' ') const;

            Stack();
            ~Stack();
            Stack(const Stack<T>& x);
            Stack(Stack<T> && x);
            Stack<T>& operator= (const Stack <T>& x);
            Stack<T>& operator= (Stack<T> && x);

    };

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>& a);
    template <typename T>
    bool operator== (const Stack<T>&, const Stack <T>&);
    template <typename T>
    bool operator!= (const Stack<T>&, const Stack <T>&);
    template <typename T>
    bool operator<=(const Stack<T>& a, const Stack <T>& b);
   
// include the implementation file here
#include "stack.hpp"
} // end of namespace 4530
#endif

                          
