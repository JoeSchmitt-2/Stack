all: in2post.x test_stack1.x

test_stack1.x : test_stack1.cpp stack.hpp stack.h
        g++ -std=c++11 test_stack1.cpp -o test_stack1.x

in2post.x : in2post.cpp stack.hpp stack.h
        g++ -std=c++11 in2post.cpp -o in2post.x

clean:
        rm -f *.o *.x core.*
