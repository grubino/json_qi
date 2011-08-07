#ifndef _JSON_GRAMMAR_H_
#define _JSON_GRAMMAR_H_

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "json_types.hpp"

namespace json_qi {
  
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

template <typename InputIterator>
struct json_grammar
  : qi::grammar<InputIterator, json_object(), ascii::space_type> {

  json_grammar()
    : json_grammar::base_type(json_object_) {

    json_object_ %=
      json_string_
      | json_float_
      | json_int_
      | json_subobject_
      | json_array_
      ;

    json_string_ %=
      (qi::lit("'")
       >> qi::lexeme[*(qi::char_ - qi::char_('\''))]
       >> (qi::lit("'")))
       | (
    	  qi::lit("\"")
    	  >> qi::lexeme[*(qi::char_ - qi::char_('"'))]
    	  >> (qi::lit("\"")))
      ;
    
    json_float_ %= qi::double_;
    
    json_int_ %= qi::int_;
    
    json_subobject_ %=
      qi::lit("{")
      >> json_subobject_map_
      >> qi::lit("}")
      ;
    
    json_subobject_map_ =
      (
       (json_string_
	>> qi::lit(":")
	>> json_object_)[phoenix::insert(qi::_val
					 , phoenix::construct
					 <json_subobject::object_map::value_type>(qi::_1
										  , qi::_2))]
       ) % ','
      ;
      
    json_array_ %= qi::lit("[") >>  (json_object_ % ',') >> qi::lit("]");

  }

  qi::rule<InputIterator, json_object(), ascii::space_type> json_object_;
  
  qi::rule<InputIterator, json_string_type(), ascii::space_type> json_string_;
  qi::rule<InputIterator, json_float_type(), ascii::space_type> json_float_;
  qi::rule<InputIterator, json_int_type(), ascii::space_type> json_int_;

  qi::rule<InputIterator, json_subobject(), ascii::space_type> json_subobject_;
  qi::rule<InputIterator, json_subobject::object_map(), ascii::space_type> json_subobject_map_;
  qi::rule<InputIterator, json_array(), ascii::space_type> json_array_;
  
};


class json_map {

public:
  json_map(json_object& obj)
    : m_obj(obj), m_obj_(0) {}

  json_map(std::string& json_in)
    : m_obj(m_obj_) {

    json_grammar<std::string::iterator> jg;

    std::string::iterator start_it(json_in.begin());
    if(!qi::phrase_parse(start_it
			 , json_in.end()
			 , jg
			 , boost::spirit::ascii::space
			 , m_obj_)) {
      throw;
    }

  }

  json_map operator[](const json_string_type& key) {
    return json_map(boost::get<json_subobject>(m_obj).contents[key]);
  }
  json_map operator[](size_t index) {
    return json_map(boost::get<json_array>(m_obj).contents[index]);
  }
  json_object& operator()() {
    return m_obj;
  }
  void push_back(const json_object& obj) {
    boost::get<json_array>(m_obj).contents.push_back(obj);
  }
  void insert(const json_subobject::object_map::value_type& val) {
    boost::get<json_subobject>(m_obj).contents.insert(val);
  }
  
  json_object& m_obj;
  json_object m_obj_;
  
};

}

#endif
