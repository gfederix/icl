#include "terminal/util.hpp"
#include "terminal/terminal.hpp"
#include <iostream>

int main(){
  Terminal term;
  term.raw();
  for(;;) {
    msg msg = wait_msg();
    switch (msg.type) {
    case msg::alpha:
      std::cout << "alpha " << msg.value ; // << std::hex
      printf("%d",*reinterpret_cast<const unsigned char *>(msg.value.data()));
      break;
    case msg::control:
      std::cout << "control " << msg.value << ";";
      break;
    case msg::escape:
      std::cout << "escape ";
    };
    std::cout << "\n\r";
    if (msg.value == "q") break;
  }
  return 0;
}
