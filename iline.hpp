#include <cstdio>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>

constexpr int esc_max_len = 10;

namespace icl
{
 static struct termios oldTermios, rawTermios;

class ReadLine {
private:
  using ctype = unsigned char;
  ctype c = '\0';
  std::unordered_map< std::string, std::function< std::string& ( const std::string&) >> cl; 
  unsigned char esc [esc_max_len];

public:
  ReadLine();
  ~ReadLine();
  char* getchar();
  bool escape();
  ctype& lastc() {return c;}

  ctype& getc() {
    return c = std::getchar();
  }

  void ungetc(){
    std::ungetc(c, stdin);
  }

  void csi();  
};

}
