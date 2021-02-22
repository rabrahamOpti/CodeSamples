//Robert Abraham
//Robert.Abraham@gmail.com
//print_procs.cpp - creates two child threads to populate a list of all
//                  processes running on this machine, then sorts and prints.

#include <iostream>
#include <list>
#include <pthread.h>
#include <stdio.h>
#include "./proc_class.h"
#include "./enumerate_processes.h"

using namespace std;

//the STL container to hold the processes returned by callback()
list<Proc> process_list;

//the callback function. Enters the processes sent by the threads into
//process_list
void callback(Proc p)
{
  process_list.push_back(p);
  return;
}

//structure to hold the pointer to callback()
cb_struct enum_arg;

int main()
{
   pthread_t tid1, tid2;
   list<Proc>::iterator it;
   int err;
   //set the structs pointer to the callback function
   enum_arg.cb_pointer = callback;
   
   //cast into a void pointer for pthread_create
   void *arg = reinterpret_cast<void*>(&enum_arg);

// launch the threads
   err = pthread_create(&tid1, NULL, EnumerateProcessesA_M, arg);
   if (err != 0)
   {
     perror("Can't create thread A-M");
     return(-1);
   }
   
   err = pthread_create(&tid2, NULL, EnumerateProcessesN_Z, arg);  
   if (err != 0)
   {
     perror("Can't create thread N-Z");
     return(-1);
   }

// wait for the threads

   err = pthread_join(tid1, NULL);
   if (err != 0)
   {
     perror("Can't join with thread A-M");
     return(-1);
   }

   err = pthread_join(tid2, NULL);
   if (err != 0)
   {
     perror("Can't join with thread N-Z");
     return(-1);
   }

//sort the list of processes
   process_list.sort();

//output the list
   for(it=process_list.begin(); it!=process_list.end(); ++it)
   {
      cout << *it << endl;
   }
   cout << endl;

   return(0);
}

