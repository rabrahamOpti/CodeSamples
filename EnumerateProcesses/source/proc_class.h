//Robert Abraham
//Robert.Abraham@gmail.com
//Proc class declaration

#ifndef PRINT_PROCS_PROC_CLASS_H
#define PRINT_PROCS_PROC_CLASS_H

#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

#define LESS_THAN 1
#define GREATER_THAN 2
#define EQUAL 3

class Proc {
  private:
    int process_id;
    std::string process_name;

    //compare_nocase could easily be decoupled from this class, but it's fine
    //here for the purposes of this exercise. 
    int compare_nocase (std::string, std::string); 

  public:
    Proc(int, std::string);
    int getId();
    void setId(int);

    std::string getName();
    void setName(std::string);

    //overloading the comparison operators for list's sort method
    bool operator<(Proc);
    bool operator>(Proc);
    bool operator==(Proc);
    bool operator<=(Proc);
    bool operator>=(Proc);
    bool operator!=(Proc);

    //overloading the stream insertion operator to simplify outputting to the console
    friend std::ostream& operator << (std::ostream &, Proc);
};

#endif
