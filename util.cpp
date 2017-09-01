#include "util.hpp"
unsigned char getc() {
    return std::getchar();
}

void ungetc(char c){
    std::ungetc(c, stdin);
}


msg wait_msg() {
  unsigned char c = getc();
  switch (c) {
  default:
    if ( '\0' < c  && c < ' '){
      if( c == '\e'){
        ungetc(c);
        return read_escape();
      }
      // Control char:
      std::string control{"C-"};
      control += c + 64;
      return msg(control, msg::control);
    };
    // if ( 128 <= c && c <= 191) {
    //   return msg("", msg::special);
    // }
    ungetc(c);
    return read_u8();
  }
}

msg read_u8() {
  unsigned char c = getc();
  ungetc(c);
  // UTF8 8-bit char length
  int u8bit_num =  (c >> 5 == 0b110 ? (c >> 4 == 0b1110 ? (c >> 3 == 0b11110? 4 : 3) : 2) : 1) + 1 /* '\0' char */;
  auto buf = std::make_unique< char[] >(u8bit_num);
  fgets(buf.get(), u8bit_num, stdin);
  return  buf.get();
}

template  < int max_esc_seq_len > 
msg read_escape() {
  unsigned char esc[max_esc_seq_len  + /* '\0' */  1 ];
    if ( (esc[0] = getc()) != '\e') {
      // ungetc(esc[0]);
      esc[1] = '\0';
      throw not_escape(/*reinterpret_cast<char*> (esc)*/);
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
    esc[3] = '\0';
  }
  return  {reinterpret_cast<const char*>(esc), msg::escape};
}
