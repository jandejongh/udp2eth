//
// $Id: tryit.cc,v 1.3 2003/12/26 23:41:01 cholm Exp $
//
//      tryit.cc 
//      Copyright (C) 2002  Christian Holm <cholm@linux.HAL3000> 
//   
//      This library is free software; you can redistribute it and/or 
//      modify it under the terms of the GNU Lesser General Public 
//      License as published by the Free Software Foundation; either 
//      version 2.1 of the License, or (at your option) any later version. 
//   
//      This library is distributed in the hope that it will be useful, 
//      but WITHOUT ANY WARRANTY; without even the implied warranty of 
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//      Lesser General Public License for more details. 
//   
//      You should have received a copy of the GNU Lesser General Public 
//      License along with this library; if not, write to the Free Software 
//      Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
//      02111-1307  USA 
//
#ifndef OPTIONMM_command_line
#include <optionmm/command_line.hh>
#endif
#ifndef __IOSTREAM__
#include <iostream>
#endif
/** @file   tryit.cc
    @author Christian Holm
    @date   Sun Dec 29 13:36:43 2002
    @brief  Test of Option-- library  */

using namespace std;
using namespace optionmm;

/** Print all values of one option. 
    @param title Title to print before values.
    @param o     The option to print. */
template<class Option>
void print_one(const char* title, const Option& o)
{
  cout << title << ": ";
  for (int i = 0; i < o.size(); i++) 
    cout << (i == 0 ? "\t" : ", ") << o.value(i);
  cout << endl;
};


/** Test program.
    @param argc The number of arguments
    @param argv The arguments 
    @return non-zero on failure, zero on success. */
int main(int argc, char** argv) 
{
  // Note, that one would ideally like to have "[OPTIONS]" in the
  // `usage' argument to the optionmm::command_line constructor, but,
  // because we're comparing the output of this program to a literal
  // string in an Autotest macro (M4), the `[' and `]' are ignored, as
  // they are defined as quotation characters in Autotest.  Hence, we
  // don't want that in the output. Instead I've used "{OPTIONS}"
  // which isn't readlly standard, and not advicable.
  command_line cl("Test of Option--", "1.0", "(c) 2002 Christian Holm", 
		  "{OPTIONS}", argc, argv);
  
  int_option    i_opt('i', "int",    "Integer option",        42);
  float_option  f_opt('f', "float",  "Floating point option", 3.14);
  string_option s_opt('s', "string", "String option",         "Hello World");
  bool_option   b_opt('b', "bool",   "Boolean option",        true);
  
  basic_option<int,true,false> e_opt('\0', "exclusive", "Exclusive", 10);
  
  cl.add(i_opt);
  cl.add(f_opt);
  cl.add(s_opt);
  cl.add(b_opt);
  cl.add(e_opt);

  if (!cl.process()) return 1;
  cl.help();
  cl.version();
  
  print_one("Integer values       ", i_opt);
  print_one("Floating point values", f_opt);
  print_one("String values        ", s_opt);
  print_one("Boolean values       ", b_opt);
  print_one("Exclusive values     ", e_opt);
  
  return 0;
}

//
// EOF
//
  
  
  
  
