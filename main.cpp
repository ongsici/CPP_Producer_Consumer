#include <iostream>
#include <thread>
#include <semaphore>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "buffer.h"

using namespace std;
const int WAIT_TIME = 10;

void producer(int num_jobs, binary_semaphore &mutex, counting_semaphore<> &space, counting_semaphore<> &item, CircularBuffer &buffer_queue){
    for (int i=0; i < num_jobs; i++){
        int randNum = (rand() % 10)+1; // generates random number from 1 to 10, inclusive
        cout << "Random number: " << randNum << endl;
        if (space.try_acquire_for(chrono::seconds(WAIT_TIME))){
            mutex.acquire();
            buffer_queue.push_buffer_head(randNum);
            mutex.release();
            item.release();
        } 
        else {
            //space semaphore not acquired within 10s
            cout << "Space semaphore not acquired within 10s, exiting..." << endl;
        }
    }
}

void consumer(binary_semaphore &mutex, counting_semaphore<> &space, counting_semaphore<> & item, CircularBuffer &buffer_queue){
    int popped_int;
    if (item.try_acquire_for(chrono::seconds(WAIT_TIME))){
        mutex.acquire();
        popped_int = buffer_queue.pop_buffer_tail();
        mutex.release();
        space.release();
        cout << "Executing job with duration: " << popped_int << "s" << endl;
        sleep(popped_int);
    } else {
        cout << "Item semaphore not acquired within 10s, exiting..." << endl;
    }
}

int main(int arg_count, char* args[]) {

    // check that there are 4 CLI arguments parsed 
    if (arg_count!=5){
        cout << "This program requires 4 arguments to be parsed: (1) Size of queue, (2) no. of jobs to generate for each producer, (3) no. of producers and (4) no. of consumers." << endl;
        cout << arg_count-1 << " argument(s) were received." << endl;
        cout << "Please try again." << endl;
        exit(1);
    }

    const int size = stoi(args[1]);
    const int job_count = stoi(args[2]);
    const int num_producers = stoi(args[3]);
    const int num_consumers = stoi(args[4]);

    binary_semaphore mutex(1);
    counting_semaphore<> space(size);
    counting_semaphore<> item(0);

    cout << "buffer size: " << size << endl;
    cout << "job count: " << job_count << endl;
    cout << "num producers: " << num_producers << endl;
    cout << "num consumers: " << num_consumers << endl;

    CircularBuffer buffer_queue(size);
    producer(job_count, mutex, space, item, buffer_queue);
    producer(job_count, mutex, space, item, buffer_queue);
    producer(job_count, mutex, space, item, buffer_queue);
    producer(job_count, mutex, space, item, buffer_queue);

    buffer_queue.print_buffer();
    cout << "Head is at: " << buffer_queue.get_head() << endl;
    cout << "Tail is at: " << buffer_queue.get_tail() << endl;

    consumer(mutex, space, item, buffer_queue);

    buffer_queue.print_buffer();
    cout << "Head is at: " << buffer_queue.get_head() << endl;
    cout << "Tail is at: " << buffer_queue.get_tail() << endl;

    consumer(mutex, space, item, buffer_queue);

    buffer_queue.print_buffer();
    cout << "Head is at: " << buffer_queue.get_head() << endl;
    cout << "Tail is at: " << buffer_queue.get_tail() << endl;

    return 0;
}