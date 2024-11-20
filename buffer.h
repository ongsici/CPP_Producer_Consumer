#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
using namespace std;

class CircularBuffer{

    public:
        CircularBuffer(int size);
        int pop_buffer_tail();
        void push_buffer_head(int);

        // for debugging
        void print_buffer();
        int get_tail();
        int get_head();

    private:
        int buffer_size;
        int head; //producer pushes to head
        int tail; // consumer pops from tail 
        vector<int> buffer;

};

#endif