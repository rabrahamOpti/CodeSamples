//Robert Abraham
//Robert.Abraham@gmail.com
//Proc class definitions

#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
#include "./proc_class.h"

Proc::Proc(int id, std::string name) : process_id(id), process_name(name)
{return;}

int Proc::getId()
{return process_id;}

void Proc::setId(int id)
{
   process_id = id;
   return;
}

std::string Proc::getName()
{return process_name;}

void Proc::setName(std::string name)
{
   process_name = name;
   return;
}

// comparison, not case sensitive.
// (Two strings otherwise equal, the shorter string will be come first in an 
//  alphabetically sorted list)
int Proc::compare_nocase (std::string first, std::string second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return LESS_THAN;
    else if (tolower(first[i])>tolower(second[i])) return GREATER_THAN;
    ++i;
  }
  if (first.length()<second.length()) return LESS_THAN;
  else if (first.length()>second.length()) return GREATER_THAN;
  else return EQUAL;
}

//overloaded comparison operators
bool Proc::operator<(Proc op2){
  if((compare_nocase(this->process_name, op2.process_name)) == LESS_THAN)
  return(true);
  else return false;
}

bool Proc::operator>(Proc op2){
  if((compare_nocase(this->process_name, op2.process_name)) == GREATER_THAN)
  return(true);
  else return false;
}

bool Proc::operator==(Proc op2){
  if((compare_nocase(this->process_name, op2.process_name)) == EQUAL)
  return(true);
  else return false;
}

bool Proc::operator<=(Proc op2){
   int return_value = compare_nocase(this->process_name, op2.process_name);
   if(return_value == EQUAL || return_value == LESS_THAN)
      return true;
   else return false;
}
      
bool Proc::operator>=(Proc op2){
   int return_value = compare_nocase(this->process_name, op2.process_name);
   if(return_value == EQUAL || return_value == GREATER_THAN)
      return true;
   else return false;
}

bool Proc::operator!=(Proc op2){
   int return_value = compare_nocase(this->process_name, op2.process_name);
   if(return_value != EQUAL)
      return true;
   else return false;
}

std::ostream& operator << (std::ostream &stream, Proc obj){
   stream << obj.getId() << " " << obj.getName();
   return stream; 
}

