#include <termios.h>
#include <sys/ioctl.h>
#include <string>
class Terminal {
private:
  termios oldTermios;
  termios rawTermios;
  winsize wsz;
public:
  Terminal();
  ~Terminal();
  unsigned short rows() {
    return wsz.ws_row;
  }
  unsigned short cols() {
    return wsz.ws_row;
  }
  void raw();
};

const  Terminal& operator<<(const Terminal& term, const std::string& str);
