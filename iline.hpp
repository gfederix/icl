#include <unordered_map>
#include <functional>
#include <string>
#include "terminal.hpp"

constexpr int esc_max_len = 10;

namespace icl
{
class ReadLine {
private:
  using ctype = unsigned char;
  ctype c = '\0';
  std::unordered_map< std::string, std::function< std::string& ( const std::string&) >> cl; 
  unsigned char esc [esc_max_len];
  Terminal term;
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

} // end llc namespace
