#ifndef _JSON_TYPES_IO_H_
#define _JSON_TYPES_IO_H_

#include <iostream>
#include <iomanip>

#include <boost/variant/static_visitor.hpp>
#include <boost/foreach.hpp>

#include "json_types.hpp"

namespace json_qi {

struct json_subobject_output_visitor
  : boost::static_visitor<std::ostream&> {

  json_subobject_output_visitor(std::ostream& os)
    : m_os(os) {}
  
  std::ostream& operator()(const json_subobject& subobject) const {
    
    size_t i = 1;
    
    m_os << "{ ";
    BOOST_FOREACH(json_subobject::object_map::value_type subobject_pair, subobject.contents) {
      m_os << std::noskipws;
      m_os << "\"" << subobject_pair.first << "\": ";
      boost::apply_visitor(*this, subobject_pair.second);
      if(i++ < subobject.contents.size())
	m_os << ", ";
    }
    m_os << " }";
    m_os << std::skipws;
    
    return m_os;
    
  }
  
  std::ostream& operator()(const json_array& array) const {

    size_t i = 1;
    
    m_os << std::noskipws;
    m_os << "[ ";
    BOOST_FOREACH(json_array::object_list::value_type element, array.contents) {
      boost::apply_visitor(*this, element);
      if(i++ < array.contents.size())
	m_os << ", ";
    }
    m_os << " ]";
    m_os << std::skipws;

    return m_os;
    
  }
  
  std::ostream& operator()(const json_string_type& str) const {
    m_os << "\"" << str << "\"";
    return m_os;
  }
  std::ostream& operator()(const json_float_type& f) const {
    m_os << f;
    return m_os;
  }

  std::ostream& m_os;
  
};

std::ostream& operator<<(std::ostream& os, const json_object& object) {
  return boost::apply_visitor(json_subobject_output_visitor(os), object);
}

}

#endif
