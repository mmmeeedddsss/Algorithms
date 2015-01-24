#include <string>
#include <iostream>
#include <thread>

using namespace std;

//The function we want to make the thread run.
void task1(string msg)
{
	double d = -1100010;
	for( ; d<0;  )
    	d+=0.0001;
}

int main()
{
    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1, "Hello");

    //Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
}
