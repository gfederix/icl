#include "terminal.hpp"
#include <unistd.h>

Terminal::Terminal(){
  ioctl(STDIN_FILENO, TIOCGWINSZ, &wsz);
  tcgetattr(STDIN_FILENO,  &oldTermios);
}
void Terminal::raw(){
  cfmakeraw(&rawTermios);
  tcsetattr(STDIN_FILENO, TCSANOW, &rawTermios);
}
Terminal::~Terminal(){
  tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

const Terminal& operator<<(const Terminal& term, const std::string& str) {
  printf("%s", str.c_str());
  return term;
}
