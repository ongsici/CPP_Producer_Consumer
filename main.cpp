#include <iostream>
#include <thread>
#include <semaphore>
#include <cstdlib>
#include "buffer.h"

using namespace std;




void producer(){

}


void consumer(){

}





int main(int arg_count, char* args[]) {

    // check that there are 4 CLI arguments parsed 
    if (arg_count!=5){
        cout << "This program requires 4 arguments to be parsed: (1) Size of queue, (2) no. of jobs to generate for each producer, (3) no. of producers and (4) no. of consumers." << endl;
        cout << arg_count-1 << " argument(s) were received." << endl;
        cout << "Please try again." << endl;
        exit(1);
    }

    int size = atoi(args[1]);
    int job_count = atoi(args[2]);
    int num_producers = atoi(args[3]);
    int num_consumers = atoi(args[4]);

    cout << "buffer size: " << size << endl;
    cout << "job count: " << job_count << endl;
    cout << "num producers: " << num_producers << endl;
    cout << "num consumers: " << num_consumers << endl;

    CircularBuffer buffer(5);

    return 0;
}