#include "util.hpp"
unsigned char getc() {
    return std::getchar();
}

void ungetc(char c){
    std::ungetc(c, stdin);
}

template <typename T>
T wait_char() {
  char c = getc();
  ungetc(c);
  switch (c) {
  case '\e':
    return ;
  default:
    return read_u8();
  }
}

msg read_u8() {
  unsigned char c = getc();
  ungetc(c);
  // UTF8 8-bit char length
  int u8bit_num = c >> 5 == 0b110 ? (c >> 4 == 0b1110 ? (c >> 3 == 0b11110? 4 : 3) : 2) : 1;
  auto buf = std::make_unique< char[] >(u8bit_num + 1);
  fgets(buf.get(), u8bit_num, stdin);
  return  buf.get();
}

template  < int max_esc_seq_len > 
msg read_escape() {
  unsigned char esc[max_esc_seq_len  + /* '\0' */  1 ];
    if ( (esc[0] = getc()) != '\e') {
    ungetc(esc[0]);
    return '\0';
  }
  esc[1] =  getc();
  if( '@' < esc[1] && esc[1] < '_' ) {
    // Control Escape Sequence (CES) 
      for (int i = 2;  i < max_esc_seq_len; i ++ ) {
      esc[i] = getc();
      if ('@' <= esc[i]  &&  esc[i] <= '~') {
        esc[i + 1] = '\0';
        break;
      }
    } // for loop
  } else {
    // ESC+letter == ALT+letter
    esc[3] = "\0";
  }
  return  msg(reinterpret_cast<const char*>(esc), msg::escape);
}
