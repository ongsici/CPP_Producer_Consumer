#include <iostream>
#include <thread>
#include <semaphore>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "buffer.h"

using namespace std;
const int WAIT_TIME = 10;

void producer(int num_jobs, int thread_id, binary_semaphore &mutex, counting_semaphore<> &space, counting_semaphore<> &item, CircularBuffer &buffer_queue){
    for (int i=0; i < num_jobs; i++){
        int randNum = (rand() % 10)+1; // generates random number from 1 to 10, inclusive
        if (space.try_acquire_for(chrono::seconds(WAIT_TIME))){
            mutex.acquire();
            buffer_queue.push_buffer_head(randNum);
            cout << "Producer thread " << thread_id << " pushed " << randNum << " to buffer" << endl;
            mutex.release();
            item.release();
        } 
        else {
            //space semaphore not acquired within 10s
            cout << "Space semaphore not acquired within 10s, exiting..." << endl;
        }
    }
}

void consumer(int thread_id, binary_semaphore &mutex, counting_semaphore<> &space, counting_semaphore<> & item, CircularBuffer &buffer_queue){
    int popped_int;
    if (item.try_acquire_for(chrono::seconds(WAIT_TIME))){
        mutex.acquire();
        popped_int = buffer_queue.pop_buffer_tail();
        mutex.release();
        space.release();
        cout << "Consumer thread " << thread_id << " executing job with duration: " << popped_int << "s" << endl;
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
        return 1;
    }
    
    try {
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

        thread prodThreadArray[num_producers];
        thread consumerThreadArray[num_consumers];

        for (int i=0; i<num_producers; i++){
            prodThreadArray[i] = thread(producer, job_count, i, ref(mutex), ref(space), ref(item), ref(buffer_queue));
        }

        for (int j=0; j<num_consumers; j++){
            consumerThreadArray[j] = thread(consumer, j, ref(mutex), ref(space), ref(item), ref(buffer_queue));
        }

        for (int i=0; i<num_producers; i++){
            prodThreadArray[i].join();
        }

        for (int j=0; j<num_consumers; j++){
            consumerThreadArray[j].join();
        }

        buffer_queue.print_buffer();
        cout << "Head is at: " << buffer_queue.get_head() << endl;
        cout << "Tail is at: " << buffer_queue.get_tail() << endl;
    }
    catch (const exception& e) {
        cerr << "Exception " << e.what() << endl ;
        return 1;
    }

    return 0;
}