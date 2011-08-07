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
  
  js_map[1]["good"]() = "bad";

  cout << "after the change: " << js_map() << endl;

  js_map[1]["good"]() = 2.4;

  cout << "after the change: " << js_map() << endl;

  js_map[1]["good"]() = 9200;

  cout << "after the change: " << js_map() << endl;

  js_map[1]["good"]() = json_array();
  js_map[1]["good"].push_back(2.2);
  js_map[1]["good"].push_back("something else");
  js_map[1]["good"].push_back(json_subobject());

  js_map[1]["good"][2].insert(make_pair("sub", "object"));
  js_map[1]["good"][2].insert(make_pair("subsub", json_subobject()));
  js_map[1]["good"][2].insert(make_pair("subarray", json_array()));

  js_map[1]["good"][2]["subsub"].insert(make_pair("more", "stuff"));
  js_map[1]["good"][2]["subsub"].insert(make_pair("even more", "stuff"));
  js_map[1]["good"][2]["subsub"].insert(make_pair("yet more", "stuff"));

  js_map[1]["good"][2]["subarray"].push_back(2.2);
  js_map[1]["good"][2]["subarray"].push_back(2);
  js_map[1]["good"][2]["subarray"].push_back("another string");
  js_map[1]["good"][2]["subarray"].push_back("you get the idea");
  */

  cout << "parsed: " << js_map() << endl;
  cout << "parsing took: " << (end - start) << endl;

  return 0;
  
}
