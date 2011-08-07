#ifndef _JSON_TYPES_H_
#define _JSON_TYPES_H_


#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/cstdint.hpp>

namespace json_qi {

struct json_subobject;
struct json_array;
typedef std::string json_string_type;
typedef double json_int_type;
typedef double json_float_type;

typedef boost::variant<
  json_string_type
  , json_int_type
  , json_float_type
  , boost::recursive_wrapper<json_subobject>
  , boost::recursive_wrapper<json_array> > json_object;

struct json_subobject {

  typedef std::map<json_string_type, json_object> object_map;
  object_map contents;

  json_subobject& operator=(std::map<json_string_type, json_object> m) { contents = m; }
  
};


struct json_array {

  typedef std::vector<json_object> object_list;
  object_list contents;

};


}


BOOST_FUSION_ADAPT_STRUCT(json_qi::json_array, (json_qi::json_array::object_list, contents));
BOOST_FUSION_ADAPT_STRUCT(json_qi::json_subobject, (json_qi::json_subobject::object_map, contents));



#endif
