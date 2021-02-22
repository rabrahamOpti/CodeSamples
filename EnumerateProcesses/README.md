# The Assignment
Write an application in C or C++ (or both) to display the process ids and process names on a local machine running a Linux OS. 

To do this, you will need to write a static library that contains two methods, EnumerateProcessesA-M(callback), and EnumerateProcessesN-Z(callback).  As the function signatures imply, each method should enumerate processes that begin with the particular letter range. The information returned via the callback function should be the process ID and the process name. Return a process ID of 0 and an empty string when the enumeration is complete. To receive the data, create a console application and link the static library you created above. This console application should launch two worker threads, one of which will call EnumerateProcessesA-M and the other EnumerateProcessesN-Z. The main application thread will provide a single structure to which the data from the worker threads will be written. Use STL for the container. Once both worker threads have completed their tasks, sort the structure by process name and display it.

# The Solution


* The source folder contains all my code. 
* The static library folder contains the requested static library and the accompanying header files
* print_procs is the executable binary I created on my machine. It was created and tested in the following environment:

`OS: ubuntu 9.04`
`compiler: g++ (Ubuntu 4.3.3-5ubuntu4) 4.3.3`


## Notes

* I chose to use the filename of the process' executable as the process name, as it is visible whether or not the executable is swapped out.
* The callback function accepts a Proc data type as an argument, which I created to hold the process name and ID.

## File Dependencies:


enumerate_processes depends on proc_class

print_procs.cpp depends on both enumerate_processes and proc_class.

So when compiling with the library, the g++ compiler required print_procs.cpp be listed first:
`g++ -static print_procs.cpp -o print_procs -L. -lenumeration -pthread`
(-L. assuming the library is in the current working directory)

Compiling without the library, with all the source files in one folder:
`g++ -static proc_class.cpp enumerate_processes.cpp print_procs.cpp -pthread -o print_procs`

## Author
Robert Abraham
Robert.Abraham@gmail.com