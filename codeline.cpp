#include "codeline.hpp"
#include "util.hpp"
#include <numeric>

using namespace cli;
CodeLine::CodeLine() {
  term.raw();
}

std::string CodeLine::get() {
  for(msg msg = wait_msg(); ; msg = wait_msg() )
    {
      switch(msg.type) {
      case msg::alpha:
        insert(msg.value);
        continue;
      default:
        return std::accumulate(lines.begin(), lines.end(),std::string(),
                               [](auto s1,auto s2) {return s1 + "\n" + s2;});
      }
    }
}


