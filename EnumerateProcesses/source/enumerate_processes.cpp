#include <iostream>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <cctype>
#include <string>
#include <pthread.h>
#include "./proc_class.h"
#include "./enumerate_processes.h"

pthread_mutex_t callback_lock = PTHREAD_MUTEX_INITIALIZER;

//According to man proc(5), only process "directories" in /proc start with a numeral  
static int selector (const struct dirent *entry)
{
  if(isdigit(entry->d_name[0])) 
     return 1;
  else return 0;
}

void* EnumerateProcessesA_M(void *arg){
   struct dirent **eps;
   int n;
   ifstream in;
   std::string process_name, process_dir;
   int process_id;
   Proc p(0,"");
   cb_struct* callback = reinterpret_cast<cb_struct*> (arg);

   //read all the files & directories in /proc, use selector to dump everything
   //that's not a process
   n = scandir (PROC_DIR, &eps, selector, alphasort);
   if (n >= 0)
   {
      int cnt;
      //for each process
      for (cnt = 0; cnt < n; ++cnt)
      {
         process_dir = PROC_DIR;
         process_dir += eps[cnt]->d_name;
         process_dir += "/stat";

         in.open(process_dir.c_str());
         
         if(!in){
           std::cout << "Could not open" <<endl;
           return (void *)-1;
         }
         //the first two words in stat are the process id and the process name
         in >> process_id; 
         in >> process_name; 

         //check to see if the process name is A-M
         if(tolower(process_name[1])<= 'm')
         {
           p.setName(process_name);
           p.setId(process_id);

           //STL containers are not thread safe, access locked
           pthread_mutex_lock(&callback_lock);
           callback->cb_pointer(p);
           pthread_mutex_unlock(&callback_lock);
         }
         in.close();
      }

   }
   else
      perror ("Couldn't open the directory");
  return (void *)0;
}

//comments above apply below
void* EnumerateProcessesN_Z(void *arg){
   struct dirent **eps;
   int n;
   ifstream in;
   std::string process_name, process_dir;
   int process_id;
   Proc p(0,"");
   cb_struct* callback = reinterpret_cast<cb_struct*> (arg);

   n = scandir (PROC_DIR, &eps, selector, alphasort);
   if (n >= 0)
   {
      int cnt;
      for (cnt = 0; cnt < n; ++cnt)
      {
         process_dir = PROC_DIR;
         process_dir += eps[cnt]->d_name;
         process_dir += "/stat";

         in.open(process_dir.c_str());
         
         if(!in){
           std::cout << "Could not open" <<endl;
           return (void *)-1;
         }
         in >> process_id; 
         in >> process_name; 

         if(tolower(process_name[1])>= 'n')
         {
           p.setName(process_name);
           p.setId(process_id);

           pthread_mutex_lock(&callback_lock);
           callback->cb_pointer(p);
           pthread_mutex_unlock(&callback_lock);

         }
         in.close();
      }

   }
   else
      perror ("Couldn't open the directory");
  return (void *)0;
}

