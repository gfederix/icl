#include "iline.hpp"

int main() {
  icl::ReadLine cmd;
  while (char* c = cmd.getchar()){
    if (c[0] == 'q')
      break;
  }
  return 0;
}
