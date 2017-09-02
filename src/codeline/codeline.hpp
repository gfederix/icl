#include "terminal/terminal.hpp"
#include <string>
#include <vector>

namespace cli {
class CodeLine {
private:
  Terminal term;
  int row = 0;
  std::vector<std::string> lines {""};
public:
  std::string& line(){
    return lines[row];
  };
  void insert(std::string w) {
    line() += w;
    term << w;
  }
  CodeLine();
  std::string get();
  enum states {
    read,
    stop,
  };
  states state = read;
  class iterator {
    CodeLine& cl;
    int line;
    std::string code;
  public:
    explicit iterator(CodeLine& c, int ln = 1): cl{c}, line{ln} {
    };
    std::string operator* (){
      return code;
    }
    void operator++() {
      line ++;
      code = cl.get();
    }
    bool operator== (iterator it) { return it.line == line;}
    bool operator!= (iterator it) { return ! (it == *this);}
  };
    
  iterator begin(){
    return iterator(*this);
  }
  iterator end() {
    return iterator(*this, 5);
  }

};
} // end namespace cli
