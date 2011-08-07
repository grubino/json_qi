#include <deque>
#include <map>
#include <utility>

#include <fstream>
#include <iostream>
#include <iomanip>

#include <algorithm>
#include <iterator>

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "json_types.hpp"
#include "json_types_io.hpp"
#include "json_grammar.hpp"

int main(int argc, char** argv) {

  using namespace std;
  using namespace boost::fusion;
  using namespace boost::posix_time;
  using namespace json_qi;

  namespace qi = boost::spirit::qi;

  if(argc != 2) {
    cout << "usage: " << argv[0] << " <JSON file name>" << endl;
    return 1;
  }

  std::string json_in;
  json_object json_out;
  
  ifstream json_infile(argv[1]);
  if(!json_infile) {
    cout << "problem reading JSON file: " << argv[1] << endl;
    return 2;
  }
  json_infile >> noskipws;
  copy(istream_iterator<char>(json_infile), istream_iterator<char>(), back_inserter(json_in));

  cout << "parsing: " << json_in << endl;

  ptime start(microsec_clock::universal_time());
  json_map js_map(json_in);
  ptime end(microsec_clock::universal_time());

  /*
  // some usage examples:

  // if your json file contains:
  // [ "something", {"state": "good"} ]
  // you can parse into a heterogeneous map like this:

  js_map(my_json_string);

  // and then reassign the state if you want:
  js_map[1]["state"]() = "bad";

  // notice the '()' operator?  it's annoying but necessary until i figure out a
  // more readable way of doing this.

  // then you can serialize back to JSON onto a stream: 
  cout << "after the change: " << js_map() << endl;

  // the types are dynamic, though they are restricted to:
  // json_qi::json_string_type,
  // json_qi::json_int_type,
  // json_qi::json_float_type,
  // json_qi::json_subobject,
  // json_qi::json_array
  // these types are all defined in include/json_types.hpp
  js_map[1]["state"]() = 2.4;

  // it's a little more complicated to change to a container type dynamically.
  // you could manually construct the object and then assign it, but that would
  // require some knowledge of the internals of json_qi::json_array and
  // json_qi::json_subobject, so the easiest thing to do may be to default
  // construct the container type and assign it.  Then use the built-in
  // stl-like member functions of json_qi::json_map for altering the contents
  // of containers.  boost::variant will throw exceptions if you invoke these
  // member functions before the underlying variant has been assigned to the
  // container that makes sense for the function you're calling.
  js_map[1]["state"]() = json_array();
  js_map[1]["state"].push_back(2.2);
  js_map[1]["state"].push_back("something else");
  js_map[1]["state"].push_back(json_subobject());

  js_map[1]["state"][2].insert(make_pair("sub", "object"));
  js_map[1]["state"][2].insert(make_pair("subsub", json_subobject()));
  js_map[1]["state"][2].insert(make_pair("subarray", json_array()));

  js_map[1]["state"][2]["subsub"].insert(make_pair("more", "stuff"));
  js_map[1]["state"][2]["subsub"].insert(make_pair("even more", "stuff"));
  js_map[1]["state"][2]["subsub"].insert(make_pair("yet more", "stuff"));

  js_map[1]["state"][2]["subarray"].push_back(2.2);
  js_map[1]["state"][2]["subarray"].push_back(2);
  js_map[1]["state"][2]["subarray"].push_back("another string");
  js_map[1]["state"][2]["subarray"].push_back("you get the idea");
  */

  cout << "parsed: " << js_map() << endl;
  cout << "parsing took: " << (end - start) << endl;

  return 0;
  
}
