// compile with
// g++ stdin_boost.cpp -lboost_regex

// regex_match example
#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

int main ()
{


  string s, rs;
  regex e;

  // see http://www.boost.org/doc/libs/1_55_0/boost/regex/v4/error_type.hpp
  cout << "Here are some helpful error codes you may encounter\n";
  cout << "while constructing your regex\n";
  cout << "error_bad_pattern " << regex_constants::error_bad_pattern << endl;
  cout << "error_collate " << regex_constants::error_collate << endl;
  cout << "error_ctype " << regex_constants::error_ctype << endl;
  cout << "error_escape " << regex_constants::error_escape << endl;
  cout << "error_backref " << regex_constants::error_backref << endl;
  cout << "error_brack " << regex_constants::error_brack << endl;
  cout << "error_paren " << regex_constants::error_paren << endl;
  cout << "error_brace " << regex_constants::error_brace << endl;
  cout << "error_badbrace " << regex_constants::error_badbrace << endl;

  cout << endl;

  cout << "Enter regex > ";
  getline (cin, rs);

  try {
    e = regex (rs);
  } catch (regex_error& exc) {
    cout << "Regex constructor failed with code " << exc.code() << endl;
    exit(1);
  }

  cout << "Enter line > ";

  while (getline(cin, s)) {

    cout << endl;

    if (regex_match (s,e))
      cout << "string object \"" << s << "\" matched\n\n";

    if ( regex_match ( s.begin(), s.end(), e ) )
      cout << "range on \"" << s << "\" matched\n\n";

    smatch sm;    // same as match_results<string::const_iterator> sm;
    regex_match (s,sm,e);
    cout << "string object \"" << s << "\" with " << sm.size() << " matches\n\n";
    // uses constant iterators so requires -std=gnu++0x
    //    regex_match ( s.cbegin(), s.cend(), sm, e);
    //    cout << "range on \"" << s << "\" with " << sm.size() << " matches\n";

    if (sm.size() > 0) {
      cout << "the matches were: ";
      for (unsigned i=0; i<sm.size(); ++i) {
  cout << "[" << sm[i] << "] " << endl;
      }
    }

    cout << endl << endl;

    cout << "Enter line > ";
  }


  return 0;
}
