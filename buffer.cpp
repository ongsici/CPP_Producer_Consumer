#include <iostream>
#include <vector>
#include "buffer.h"
using namespace std;


CircularBuffer::CircularBuffer(int size){
    buffer = vector<int>(size);
    buffer_size = size;
    cout << "first item in array: " << buffer[0] << endl;
    cout << buffer[1] << endl;
    cout << buffer[2] << endl;
}