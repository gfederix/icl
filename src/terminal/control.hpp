#include "terminal.hpp"
#include <vector>
#include "ascii_control.hpp"

Terminal& operator>> (Terminal& term, ascii_control& ctrl) {
  ctrl.clear();
  unsigned ch = term.peek();
  if ( '\0'< ch && ch < ' ') {
    if ( ch == '\e') {
      read_escape(term, ctrl);
    }
    else {
    ctrl.push_back(term.get());
    }
  }
    
  return term;
}

void read_escape( Terminal& term, ascii_control& esc) {
  esc.clear();
  if( term.peek() != '\e') {
    // Not Escape
    return;
  }
  term.read(esc.resize(2).begin(), 2); // esc{\eX}
  if ( esc[1] == '[') {
    // Control Escape Sequence (CES)
    char ch;
    for (;;) {
      ch = term.get();
      esc.push_back(ch);
      if ('@' <= ch  &&  ch <= '~')  break; // terminator char
    } // esc{eX.*[terminalChar]}
  }
  return;
}
