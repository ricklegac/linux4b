#include <pthread.h>
#include <cstdio>
#include<iostream>
#include <unistd.h>
extern bool should_exit_thread_immediately (){return true;};

class ThreadExitException {
public:
    /* Create an exception signalling thread exit with RETURN_VALUE.  */
    ThreadExitException (void* return_value)
        : thread_return_value_ (return_value) {}

    /* Actually exit the thread, using the return value provided in the
       constructor.  */
    void* DoThreadExit () {
        pthread_exit (thread_return_value_);
    }

private:
    /* The return value that will be used when exiting the thread.  */
    void* thread_return_value_;
};

void do_some_work () {
    while (1) {
        printf(" me gusta mucho lp3 ");
        usleep(10000);
        
        if (should_exit_thread_immediately ()) 
            throw ThreadExitException (/* thread's return value = */ NULL);
    }
}

void* thread_function (void*) {
    try {
        do_some_work ();
    } catch (ThreadExitException ex) {
        /* Some function indicated that we should exit the thread.  */
        printf(" Exception \n");
        ex.DoThreadExit ();
    }
    return NULL;
}

int main (){
    pthread_t thread;
    pthread_create(&thread, NULL, &thread_function, NULL);
    pthread_join(thread, NULL);
    return 0;

}