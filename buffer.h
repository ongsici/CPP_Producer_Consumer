#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
using namespace std;

class CircularBuffer{

    public:
        CircularBuffer(int size);

    private:
        int buffer_size;
        int head;
        vector<int> buffer;

};

#endif