#ifndef PRINT_PROCS_ENUMERATE_PROC_H
#define PRINT_PROCS_ENUMERATE_PROC_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <cctype>
#include <string>
#include <pthread.h>
#include "./proc_class.h"

#define PROC_DIR "/proc/"

using namespace std;

//function pointer type for the callback function
typedef void (*CB)(Proc);

//holds a pointer to the callback function
struct cb_struct {
  CB cb_pointer;
};

//The selector function for scandir, used by the Enumerate functions  
static int selector (const struct dirent *);

//Enumerates processes that begin with the letters A-M
void* EnumerateProcessesA_M(void *);

//Enumerates processes that begin with the letters N-Z
void* EnumerateProcessesN_Z(void *);

#endif
