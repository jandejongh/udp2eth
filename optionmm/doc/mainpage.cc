//
// $Id: mainpage.cc,v 1.5 2003/12/27 00:40:55 cholm Exp $
//
//   General C++ parser and lexer
//   Copyright (C) 2002  Christian Holm Christensen <cholm@nbi.dk>
//
//   This library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Lesser General Public License 
//   as published by the Free Software Foundation; either version 2 of 
//   the License, or (at your option) any later version.  
//
//   This library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   Lesser General Public License for more details. 
//
//   You should have received a copy of the GNU Lesser General Public
//   License along with this library; if not, write to the Free
//   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
//   MA 02111-1307  USA  
//
//
/** @file   mainpage.cc
    @author Christian Holm
    @date   Sun Sep 15 16:29:24 2002
    @brief  Title page documentation. */

/** @mainpage 
    @image html logo.png

    @section intro Introduction. 

    This library provides a number of classes to help applications
    with the tedious choir of parsing command line arguments.  I made
    this library as this is a thing that keeps poping up, so I
    thought: `Why not put that stuff which I did a thousand times over
    into a library, and save me the grief of doing over and  over
    again?'  If you fell the same way, this library is for you. 

    @section usage Usage 

    The use of this library is really easy.  First, include the header
    file optionmm/command_line.hh:
    @dontinclude demo.cc
    @skip  #ifndef
    @until #endif

    Then, in the main program, construct an instance of the class
    optionmm::command_line:  
    @skip int
    @until ""

    The first argument of the constructor is a tenative title of the
    application at hand, and the second is the version number (as a
    string) of the application.  

    If the project is using @b Autoconf, the preprocessor macros 
    @c PACKAGE_NAME and @c PACKAGE_VERSION for these two 
    arguments, thereby automating the process.  

    The third argument is a short line giving the copyright
    information of the application.  This is shown under the
    application title when the user requests help. 

    The fourth and fifth arguments are the command line length and
    array of arguments.  These are usually called @c argc and 
    @c argv. 

    One can pass an error handler class as a template parameter to the
    declaration of the optionmm::basic_command_line object.  This
    class should define the appropriate member functions to deal with
    unknown arguments, and bad option values.  See also
    optionmm::default_error_handler. 

    The next step is to define some options: 
    @until optionmm::basic_option<int>
    
    The class optionmm::basic_option is a templated class.  The
    requirements of the type parameter, is that it is assignable, and
    that it is possible to convert to from a string (@c const @c char*
    ) to that value type, using a regular cast a @c std::stringstream.
    For custom types, this is done by defining the extraction
    operator:
    
    @code 
    class foo 
    {
      ...
    };
    
    std::istream& operator>>(std::istream& i, foo& f) 
    { 
      ...
    }
    @endcode 

    The template class optionmm::basic_option takes two more optional
    parameters, both of which should be booleans.

    The optional second template parameter specifies whether or not
    the option needs an argument.  An error will be issued if the
    application user didn't specify an argument for an option that has
    this template parameter set to @c true.  The default value is @c
    true.  If this parameter is set to @c false, then specifying this
    option to the application makes an instance of @c operator!(Type)
    which you better define unless @c Type is convertable to some
    simple type. 

    The optional third template parameter specifies whether or not the
    option can take multiple values (arguments or set count).  If this
    parameter is @c true, (the default) then specifying the same
    option to the application more than once causes the
    optionmm::basic_option object to store all those values, which can
    later be retrived via calls to optionmm::basic_option::value(int).
    If @c false, giving the same option several times, overwrites the
    previous value.

    The first argument to the constructor is the letter of the short
    command line option the object corresponds to.  If @c '\\0' is
    specified, the option has no short command line option.  

    The second argument to the constructor, is the long command line
    option corresponding to the argument.  If this is left blank (the
    empty string) the object has no corresponding long option.

    The third argument, is the help string corresponding to the
    object.  This is shown, along with the applicaion synopsis and
    option list, when the user requests help from the application. 

    The final fourth argument to the constructor, is the default value
    for the option object.  Note that this must be of the value type
    of the option object.

    The library provides @c typedef of the most common option types:
    optionmm::int_option,  optionmm::float_option,
    optionmm::string_option, and optionmm::bool_option.  The latter is
    defined as a single-value, no-argument kind of option. 

    @until optionmm::int_option

    After defining an option, the optionmm::basic_command_line object
    needs to know about it: 
    
    @until cl.add(I_opt);

    After registering all the options the application may need, the
    application must call optionmm::basic_command_line::process to
    process the actual command line.

    @until if (!cl.process

    The member function optionmm::basic_command_line::process returns
    @c false if an error occured during parsing, so testing the return
    value of that member function is recommended.

    Note, that optionmm::basic_command_line::process changes the
    arguments of @c main (@c argc, and @c argv in the example above),
    by removing all components that was used in the parsing.  Hence,
    after optionmm::basic_command_line::process the two variables only
    contain what was on the command line, which wasn't options.  This
    is useful if the application wants to process files or similar.

    The optionmm::basic_command_line has two automatic options build
    in: One for showing the help, and one for showing the version
    number of the application.  These are invoked from the command
    line by @c -h or @c --help for the help, and @c --version for the
    version information. To facilitate that output in the application,
    it must invoke the member functions
    optionmm::basic_command_line::help and
    optionmm::basic_command_line::version.

    @until cl.version

    Both of these member functions return @c true if the corresponding
    option was given on the application command line.  Hence, one can
    for example stop the application if help was requested by the
    application user (as shown above).  Note, that the help always
    implies the version information too.

    After having processed the command line, and testing for errors or
    the like, the optionmm::basic_option objects now contain the
    values passed by the application user.  The application can then
    retrive these values by (possibly repeated) calls to
    optionmm::basic_option::value.  For example, one could print the
    values on standard out: 

    @until std::cout

    @section err Error handling

    Error handling is taken care of the template argument to
    optionmm::basic_command_line.  It's a policy argument.  The type
    should define four public member function, all returning a @c
    bool:

    @code 
    bool on_onknown(char c,std::string& progname) 
    @endcode 
    Member function invoked in case an unknown short option was passed
    to the application.  First argument is the short option given,
    while the second is the program invocation name.

    @code 
    bool on_onknown(const char* c,std::string& progname) 
    @endcode 
    Member function invoked in case an unknown long option was passed
    to the application.  First argument is the long option given,
    while the second is the program invocation name.

    @code 
    template <typename O>
    bool on_missing_argument(O&, bool is_short,std::string& progname) 
    @endcode 
    Member function invoked in case no argument was given to an option
    that needs an argument.  The first argument is the option that
    needs the argument, the second is whether it was invoked as in
    it's short form or not, and the third is the program invocation
    name.

    @code 
    template <typename O>
    bool on_bad_argument(O&, bool is_short,std::string& progname) 
    @endcode 
    Member function invoked in case a bad argument was given to an
    option e.g., a string was passed to an option taking an integer
    argument.  The long story of this is covered elsewhere (@ref
    conv). The first argument is the option that needs the argument,
    the second is whether it was invoked as in it's short form or not,
    and the third is the program invocation name.
      
    All these methods should return @c true if the
    basic_command_line should stop processing the command line and
    return immediately, or @c false if it should continue. 

    Client code can freely define new error handlers to suite the
    needs of the application.  For example: 
    @code 
    struct my_error_handler 
    {
      bool on_unknown(char c, const std::string& progname) 
      {
        throw std::runtime_error("unknown option");
        return true;
      }
      bool on_unknown(const std::string& str, const std::string& progname)
      {
        throw std::runtime_error("unknown option");
        return true;
      }
      template <typename Option>
      bool on_missing_argument(Option& o, 
	  		       bool is_short, 
			       const std::string& progname) 
      {
        throw std::runtime_error("missing argument to an option");
        return true;
      }
      template <typename Option>
      bool on_bad_argument(Option& o, 
	  		   bool is_short, 
			   const std::string& progname) 
      {
        throw std::runtime_error("bad argument to an option");
        return true;
      }
    };

    ...

    int main(int argc, char** argv) 
    { 
      optionmm::basic_command_line<my_error_handler> cl(...);

      ...

      try {
        cl.process();

	...

      } catch (std::exception& e)  {
        std::cerr << e.what() << std::endl;
	return 1;
      }
      return 0;
    }
    @endcode 

    @see optionmm::default_error_handler 

    @section conv Converting the command line arguments to option
    values. 

    When the command line arguments enters the application function
    (@c main) it is as an array of C string values.  However, a
    command line option may conceptually be something completely
    different from a string.  It could be a number or a flag. 

    Hence we need to convert the C strings to what ever type a given
    option wants and stores.  This is done via a <i>trait</i> argument
    to the optionmm::basic_option structure.  This trait type should
    define two member functions:

    @code 
    bool  convert (const char *arg, value_type &val)
    @endcode
    Convert the first argument (C string) to a value of type @c
    value_type and store it in the second output argument.  It should
    return @c true on success, and @c false otherwise.

    @code 
    bool  convert (reference val)
    @endcode
    Toggle the value in the argument. Usually this is just assigning
    @c !val to @c val (possibly via a temporary).

    The default trait is optionmm::option_trait.  The first member
    function is implemented using @c std::stringstream.  To extract a
    value, of a given type from a string, one can do
    @code 
      std::stringstream s(str);
      Type t;
      s >> t;
    @endcode 
    were @c str is some @c std::string object, and @c Type is some
    type for which the <i>extraction</i> operator 
    @code 
      std::istream operator>>(std::istream& i, Type& t);
    @endcode 
    is defined.  

    Hence, defining the above extraction operator for a user type,
    allows it to be used seemlessly with the <b>Option--</b> classes,
    as well as providing a useful tool in I/O operations, all in one
    go - pretty neat, eh!  For example, one could do 

    @code 
    struct foo 
    {
      foo(int f) : _foo(0) {}
      int _foo;
    };
    std::istream& operator(std::istream& i, foo& f) 
    {
      return i >> f._foo;
    }
    int main(int argc, char** argv) 
    {
      optionmm::command_line cl("Trying foo", "1.0", 
                                "Copyright (c) 2003 Christian Holm", "",
                                argc, argv);
      optionmm::basic_option<foo> foo_option('f',"foo", "foo option",foo());
      cl.add(foo_option);
      return cl.process();
    }
    @endcode
    The I/O sub-library of the Standard C++ Library is quite a
    powerful entity.

    @section app Application Usage 

    Running an application with lines like the above 
    (@link demo.cc demo.cc @endlink) with various command lines will give: 
    @verbatim 
    prompt> ./demo -h
    Demonstration of Option-- version 1.0
    Copyright (c) 2002 Christian Holm

    Usage: demo [OPTIONS]

        -h, --help         	Show this help
            --version      	Show version information
        -i, --int=VALUE    	Integer option (*)
        -I, --Int=VALUE    	Integer option (*)

    prompt> ./demo --version
    Demonstration of Option-- version 1.0
    Copyright (c) 2002 Christian Holm
    0
    prompt> ./demo -i 10 -i 42 
    10
    42
    prompt> ./demo --int=42 -i50 -I10 -I 19
    42
    50
    prompt> ./demo -f
    Option `-f' unknown, try `demo --help'
    @endverbatim

    @section autotools  Support Features 

    The library comes with two extra files: an @b Autoconf macro file 
    @c optionmm.m4 that defines @c AM_PATH_OPTIONMM, and a @b SH
    script @c optionmm-config that developers can use to get the
    relevant information into thier build system. 

    The syntax of the @b Autoconf macro is 
    @verbatim 
    AM_PATH_OPTIONMM([MINIMUM-VERSION[,ACTION-IF_FOUND[,ACTION-IF-NOT-FOUND]])
    @endverbatim 
    If the macro finds @b Option-- on the system, then it defines 
    @c OPTIONMM_CPPFLAGS to the relevant preprocessor flags for
    including @link command_line.hh <optionmm/command_line.hh>@endlink,
    and @c OPTIONMM_CONFIG to point to the @c optionmm-config shell
    script. 

    The shell script @c optionmm-config has the following synopsis: 
    @verbatim
    Usage: optionmm-config [options]
    
      --prefix          Gives the installation prefix
      --includedir      Gives path to headers 
      --cppflags        Gives preprocessor information
      --version         Gives version information
      --help            Gives this help
    @endverbatim
    where the options gives the various installation details. 
    
    Finally, there's a man(1) page for @c optionmm-config too.

    @section copyright Copyright

    Copyright (C) 2002	Christian Holm Christensen <cholm@nbi.dk>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public License
    as published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA

    See also @ref lgpl 
*/



//
// EOF
//
