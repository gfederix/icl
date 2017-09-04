#include <termios.h>
#include <sys/ioctl.h>
#include <string>
#include <memory>

class Terminal {
private:
  termios oldTermios;
  termios rawTermios;
  winsize wsz;
  using int_type = int;
  using char_type = char;
public:
  Terminal();
  ~Terminal();
  unsigned short rows() {
    return wsz.ws_row;
  }
  unsigned short cols() {
    return wsz.ws_row;
  }
  int get() {
    return std::getc(stdin);
  }
  Terminal& putback( char ch) {
    std::ungetc(ch, stdin);
    return *this;
  }
  int_type peek(){
    int_type ch = get();
    putback(ch);
    return ch;
  }
  Terminal& read(char_type* s, std::streamsize count) {
    while (count) {
      s[--count] = std::getc(stdin);
    };
    return *this;
  }
  void raw();
};

const  Terminal& operator<<(const Terminal& term, const std::string& str);
