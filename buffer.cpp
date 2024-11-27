#include <iostream>
#include <vector>
#include "buffer.h"
using namespace std;


CircularBuffer::CircularBuffer(int size){
    buffer = vector<int>(size);
    buffer_size = size;
    head = 0; // index of next empty slot to insert into buffer
    tail = 0; // index of oldest value in buffer 
}

int CircularBuffer::pop_buffer_tail(){
    tail = tail % buffer_size;
    int popped_value = buffer[tail];
    buffer[tail] = 0; 
    
    // check tail doesnt exceed head 
    if (tail+1 <= head){
        tail++;
    }

    return popped_value;
}

void CircularBuffer::push_buffer_head(int i){
    head = head % buffer_size;
    buffer[head] = i;
    head++;
}

// for debugging

void CircularBuffer::print_buffer(){
    for (int i = 0 ; i < buffer_size ; i++){
        cout << "Position " << i << ": " << buffer[i] << endl;
    }
}

int CircularBuffer::get_head(){
    return head;
}

int CircularBuffer::get_tail(){
    return tail;
}