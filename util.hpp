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
    control,
    special,
  };
  template <typename charT>
  msg(charT val,  msg_types type = alpha): type{type}, value(val) {
  };
  msg_types type;
  std::basic_string<char> value;
};

msg wait_msg();
msg read_u8();
template  < int max_esc_seq_len  = 10>
msg read_escape();

class not_escape: public std::exception {

};
