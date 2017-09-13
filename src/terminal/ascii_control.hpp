#ifndef ASCII_CONTROL_HPP
#define ASCII_CONTROL_HPP
#include <vector>
#include <string>

class ascii_control: public std::vector <char> {
private:
  using super = std::vector<char>;
  using self = ascii_control;
public:
  ascii_control() {
    super();
  }
  operator bool() const {
    return ! empty();
  }
  self& resize(std::size_t count){
    super::resize(count);
    return *this;
  }
  self& clear() {
    super::clear();
    return *this;
  }
  std::string value () const {
    return {begin(), end()};
  }
  bool operator== (const self& control) {
    return control.value() == value();
  }
  bool operator!=(const self& control) {
    return control.value() != value();
  }
};

#endif
