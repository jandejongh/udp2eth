//
// $Id: option.hh,v 1.11 2004/01/13 18:08:42 cholm Exp $ 
//  
//  optionmm::option
//  Copyright (C) 2002 Christian Holm Christensen <cholm@nbi.dk> 
//
//  This library is free software; you can redistribute it and/or 
//  modify it under the terms of the GNU Lesser General Public License 
//  as published by the Free Software Foundation; either version 2.1 
//  of the License, or (at your option) any later version. 
//
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//  Lesser General Public License for more details. 
// 
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free 
//  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
//  02111-1307 USA 
//
#ifndef OPTIONMM_option
#define OPTIONMM_option

#ifndef __TYPEINFO__
#include <typeinfo>
#endif
#ifndef __VECTOR__
#include <vector>
#endif
#ifndef __STRING__
#include <string>
#endif
#ifndef __IOSTREAM__
#include <iostream>
#endif
#ifndef __IOMANIP__
#include <iomanip>
#endif
#ifndef __SSTREAM__
#include <sstream>
#endif
#ifndef __STDEXCEPT__
#include <stdexcept>
#endif

/** @file   option.hh
    @author Christian Holm
    @date   Sat Dec 28 19:10:36 2002
    @brief  Command line option  */

namespace optionmm
{
  //====================================================================
  /** @class option_base option.hh <optionmm/option.hh>
      @brief Base class for options. 

      This is needed to use the @c std::vector container in the class
      command_line below. */
  class  option_base 
  {
  public:
    typedef std::vector<int> position_list;
  protected:
    /// Short name of the option 
    char _short_name;
    /// Long name of the option 
    std::string _long_name;
    /// The help string 
    std::string _help_string;
    /// List of positions 
    position_list _positions;
  public:
    enum {
      cannot_handle,
      can_handle,
      bad_argument, 
      missing_argument
    };
    /** CTOR
	@param s The short name (possibly '\\0')
	@param l The long name (possibly "");
	@param h The help string. */
    option_base(char s, 
		 const std::string& l, 
		 const std::string& h);
    /// DTOR 
    virtual ~option_base() {}
    /** Get the short name 
	@return  the short name */
    char short_name() const { return _short_name; }
    /** Get the long name 
        @return  the long name */
    const std::string& long_name() const { return _long_name; }
    /** Get the help string 
        @return the help string  */
    const std::string& help_string() const { return _help_string; }
    /** Test whether we need an argument 
        @return whether we need an argument */
    virtual bool need_argument() const { return true; }
    /** Test if this option can have many values 
        @return  true if this option can have many values */
    virtual bool many_values() const { return true; }
    /** Set one value 
	@param arg The argument 
	@param pos Where the argument occured on the command line 
        @return  positive if OK, negative on errors */
    virtual int push_arg(const char* arg, int pos) = 0;
    /** Toggle the option.
	@param pos Where the option was set on the command line
	@return  positive if OK, negative on errors */
    virtual int push_arg(int pos) = 0;
    /** Get the position of the @a i'th argument 
	@param i Which argument to get the position off  
	@return Position of the @a i'th arument, or negative if @a is
	out of range   */
    virtual int position(int i=0) const;
    /** Print this option help line to a stream 
	@param ll Width for the option names
	@param o The stream to write to */
    virtual void print(int ll, std::ostream& o=std::cout) const = 0;
    /** Process this as a long option. 
	@param arg is the option with leading "--" 
	@param pos The position of the option on the command line.
	@return positive on success, 0 on if no match, negative on failure. */
    virtual int handle(const std::string& arg, int pos);
    /** Handle this option as a short. 
	@param opt The option 
	@param arg The possible argument. 
	@param pos The position of the option on the command line.
	@return positive on success, 0 on if no match, negative on failure. */
    virtual int handle(char*& opt, char*& arg, int pos);
  };

  //__________________________________________________________________
  inline 
  option_base::option_base(char s, 
			     const std::string& l, 
			     const std::string& h)
    : _short_name(s), 
      _long_name(l),
      _help_string(h)
  {}

  //__________________________________________________________________
  inline 
  int
  option_base::position(int i) const
  { 
    if (i < 0 || i >= _positions.size()) return 0;
    if (!many_values()) return _positions[0]; 
    return _positions[i];
  }

  //__________________________________________________________________
  inline 
  int
  option_base::handle(const std::string& arg, int pos)
  {
    if (_long_name.empty() || 
#if defined(__GNUC__) && __GNUC__ <= 2
	arg.compare(_long_name, size_t(2), _long_name.size())
#else 
	arg.compare(size_t(2), _long_name.size(), _long_name)
#endif
	) return cannot_handle;
    if (!need_argument()) return push_arg(pos);

    std::string::size_type eq = arg.find_last_of('=');
    if (eq == std::string::npos) return missing_argument;
    
    std::string value(arg);
    value.erase(0, eq+1);
    return push_arg(value.c_str(), pos);
  }
  
  //__________________________________________________________________
  inline 
  int
  option_base::handle(char*& opt, char*& arg, int pos)
  {
    if (_short_name == '\0' || opt[0] != _short_name) return cannot_handle;
    if (!need_argument())                             return push_arg(pos);

    int ret = can_handle;
    if (opt[1] != '\0') {
      ret = push_arg(&(opt[1]), pos);
      if (ret > cannot_handle) opt[1] = '\0';
    }
    else if (arg) {
      ret = push_arg(arg, pos);
      // Flag argument as used. 
      if (ret > cannot_handle) arg = 0;
    }
    else 
      ret =  missing_argument;
    
    return ret;
  }
  
  //==================================================================
  /** @class option_trait optionmm/option.hh <optionmm/option.hh>
      @brief Trait to help do conversions. 
  */
  template <typename Type>
  struct option_trait 
  {
    /** Type of the trait */
    typedef Type                             value_type;
    /** Container used by the option */
    typedef std::vector<value_type>          list_type;
    /** Reference type used by the container */
    typedef typename list_type::reference    reference;
    
    /** Convert a string to the value type 
	@param arg The string to convert
	@param val The resulting value 
	@return  true on success, false otherwise. */
    static bool convert(const char* arg, value_type& val)
    {
      std::stringstream str(arg);
      str.unsetf(std::ios::skipws);
      str >> val;
      if (str.bad() || str.fail()) return false;
      std::string t;
      str >> t;
      if (!t.empty()) return false;
      return true;
    }
    /** Toggle a value.
	@param val The value to toggle
	@return  true on success */
    static bool convert(reference val) 
    {
      value_type tmp = !val;
      val = tmp;
      return true;
    }
  };

  //================================================================== 
  template <> 
  struct option_trait<std::string> 
  {
    typedef std::string value_type;
    typedef std::vector<value_type> list_type;
    typedef list_type::reference    reference;
    
    static bool convert(const char* arg, value_type& val)
    {
      val = arg;
      return true;
    }
    static bool convert(reference val) 
    {
      return true;
    }
  };
 
  //====================================================================
  /** @class basic_option option.hh <optionmm/option.hh>
      @brief Command line option class.

      The argument @c Type is the type of the value, @c argument
      specifies whether this option needs an argument, and 
      @c multivalue says whether the option can take multiple values. */
  template <typename Type, 
	    bool argument=true, 
	    bool multivalue=true, 
	    typename Trait=option_trait<Type> >
  class basic_option : public option_base
  {
  public:
    typedef Type value_type;	/** The value type */
    typedef std::vector<value_type> value_list;	/** Type of value container */
    typedef Trait trait_type;
  protected:
    value_list _values;		/** A list of the values */
    value_type _default;	/** Default value */
  public:
    /** Constructor.
	@param s The short name (possibly '\\0')
	@param l The long name (possibly "");
	@param h The help string. 
	@param d The default value. */    
    basic_option(char s, 
		 const std::string& l,
		 const std::string& h, 
		 value_type d);
    /** Destructor. */
    virtual ~basic_option() {}

    /** Whether this option need an argument */
    bool need_argument() const { return argument; }  
    /** Whether this optin can take many values */ 
    bool many_values() const { return multivalue; }  
    /** Number of values of this option */
    int size() const { return  (_values.size() == 0 ? 1 : _values.size()); }

    /** Get value
	@param i The value number to get. 
	@return the @p i value, or if that is out of bounds, the first
	value. */ 
    const value_type& value(int i=0) const;
    /** Get all values */ 
    const value_list& values() const { return _values; }

    /** Add a value from a string.  This is used by the command_line
	class to set the values of the options, in case need_argument 
	tests true. 
	@param pos The position on the command line the option was
	given at.
	@param arg The value added. */
    int push_arg(const char* arg, int pos);
    /** Add a value.  This is used by the command_line
	class to set the values of the options, in case need_argument 
	tests false. 
	@param pos The position on the command line the option was
	given at. */
    int push_arg(int pos);

    /** Print this option help line to a stream 
	@param ll Width for the option names
	@param o The stream to write to */
    virtual void print(int ll, std::ostream& o=std::cout) const;
  };
  //____________________________________________________________________
  template<typename Type, bool arg, bool multi, typename Trait>
  inline 
  basic_option<Type,arg,multi,Trait>::basic_option(char s, 
						   const std::string& l, 
						   const std::string& h, 
						   value_type d) 
    : option_base(s, l, h), _default(d) 
  {}
  
  //____________________________________________________________________
  template<typename Type, bool arg, bool multi, typename Trait> 
  inline const Type& 
  basic_option<Type,arg,multi,Trait>::value(int i) const
  { 
    if (i >= _values.size() || i < 0) return _default; 
    const value_type& ret = _values[i];
    return ret;
  }

  //____________________________________________________________________
  template<typename Type, bool arg, bool multi, typename Trait> 
  inline 
  int
  basic_option<Type,arg,multi,Trait>::push_arg(const char* a, int pos) 
  { 
    value_type val;
    if (!trait_type::convert(a, val)) return bad_argument;
    
    if (!many_values()) {
      if (_values.size() == 0) {
	_values.push_back(val);
	_positions.push_back(pos);
      }
      else {
	_values[0]    = val;
	_positions[0] = pos;
      }
    } else {
      _values.push_back(val);
      _positions.push_back(pos);
    }
    return can_handle;
  }

  //____________________________________________________________________
  template<typename Type, bool arg, bool multi, typename Trait> 
  inline 
  int
  basic_option<Type,arg,multi,Trait>::push_arg(int pos) 
  { 
    if (many_values()) {
      _values.push_back(_default);
      _positions.push_back(pos);
    }
    else {
      if (_values.size() == 0) {
	_values.push_back(_default);
	_positions.push_back(pos);
      }
      else 
	_positions[0] = pos;
      trait_type::convert(_values[0]); // = !_values[0];
    }
    return can_handle;
  }

  //__________________________________________________________________
  template<typename Type, bool arg, bool multi, typename Trait> 
  inline 
  void
  basic_option<Type,arg,multi,Trait>::print(int ll, std::ostream& o) const
  {
    if (ll <= 0) ll=16;
    if (_short_name != '\0') o << "-" << _short_name <<", ";
    else                     o << "    ";
    if (!_long_name.empty()) {
      o << "--" << _long_name;
      if (need_argument()) o << "=VALUE";
      else                 o << "      ";
      for (int i = _long_name.size(); i < ll; i++) o << " ";
    }
    else {
      o << std::setw(ll+2) << " ";
      if (need_argument()) o << " VALUE";
      else                 o << "      ";
    }
    o << "\t" << _help_string; // << " (default: " << _default << ")";
    if (many_values()) o << " (*)";
  }  
}

#endif
//____________________________________________________________________
//
// EOF
//

