//
// $Id: demo.cc,v 1.2 2003/12/18 17:58:20 cholm Exp $
//
//      demo.cc 
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
/** @file   demo.cc
    @author Christian Holm
    @date   Sun Dec 29 13:36:43 2002
    @brief  Test of Option-- library  */

/** Demonstration program
    @param argc The number of arguments
    @param argv The arguments 
    @return non-zero on failure, zero on success. */
int main(int argc, char** argv) 
{
  optionmm::basic_command_line<> cl("Demonstration of Option--", "1.0", 
				    "Copyright (c) 2002 Christian Holm", 
				    "", argc, argv);
  
  optionmm::basic_option<int>  i_opt('i', "int", "Integer option", 0); 
  optionmm::int_option         I_opt('I', "Int", "Integer option", 42);
  
  cl.add(i_opt);
  cl.add(I_opt);

  if (!cl.process()) return 1;
  if (cl.help()) return 0;
  cl.version();
  
  for (int i = 0; i < i_opt.size(); i++) 
    std::cout << i_opt.value(i) << std::endl;

  return 0;
}

//
// EOF
//
  
  
  
  
