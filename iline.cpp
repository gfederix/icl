/*
 * Simple UNIX interactive commandlie  C++ lib.
 * Copyright  (c) 2017 Fyodor Goncharov.
 *
 */
#include <cstring>
#include <iostream>
#include "iline.hpp"
//using namespace std;
namespace icl {

ReadLine::ReadLine() {
  term.raw();
}

ReadLine::~ReadLine() {
};

char* ReadLine::getchar(){
  if (escape()) return getchar();
  getc();
  ungetc();
  // UTF8 8-bit char length + \0
  int u8charlen = c >> 5 == 0b110 ? (c >> 4 == 0b1110 ? (c >> 3 == 0b11110? 5 : 4) : 3) : 2;
  char* buf = new char[u8charlen];
  fgets(buf, u8charlen, stdin);
  std::cout << buf;
  return  buf;
}

bool ReadLine::escape() {
  if ( getc() != '\e') {
    ungetc();
    return false;
  }
  std::cout << "ESC{ ";
  esc[0] = '\e';
  esc[1] =  getc();
  if( ! ( '@' < lastc() && lastc() < '_') ) {
    ungetc();
    std::cout << " }ESC(wrong symbol) ";
    return false;
  }


  for (int i = 2;  i < esc_max_len - 1; i ++ ) {
    esc[i] = getc();
    if ( i > 1 && ('@' <= lastc()  &&  lastc() <= '~')){
      esc[i + 1] = '\0';
      break;
    }
  }
  
  std::string key{reinterpret_cast<const char*>(esc)};
  if ( key == "\e[A") {
    std::cout << " arrow up ";
  } else if (key == "\e[3~") {
    std::cout << " DEL ";
  }  else {
    std::cout << " OTHER  ";
  }
  try   {
    cl.at(key)(key);
  } catch (const std::out_of_range& e) { }
          
  std::cout << "}ESC ";
  return true;
}

void ReadLine::csi() {
  std::cout << " CSI: ";
}

}

