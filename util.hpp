// c lib
#include <cstdio>
#include <cstring>
// terminal 
#include <termios.h>
#include <unistd.h>
// std++ lib
#include <vector>
#include <iostream>
#include <memory>

struct msg {
  enum msg_types {
    alpha,
    escape,
  };
  msg_types type;
  std::basic_string<char> value;
  msg(const char* val,  msg_types type = alpha): type{type}, value(val) {
  };

};

template <typename T>
T wait_char();

msg read_u8();
template  < typename T, int max_esc_seq_len = 10 > 
msg read_escape();
