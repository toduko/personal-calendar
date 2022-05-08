#ifndef STRING_H_
#define STRING_H_

#include <cstddef>
#include <iostream>

class String
{
private:
  char *data;
  size_t length;

  void copy(const char *data);
  void move(String &&other);
  void free();

public:
  String(const char *data = "");
  String(const String &other);
  String(String &&other);
  String &operator=(const String &other);
  String &operator=(String &&other);
  ~String();

  char &operator[](size_t index);
  char operator[](size_t index) const;

  String &concat(const char *extra);

  const char *getData() const;
  size_t getLength() const;

  String &operator+=(const String &other);

  static bool isDigit(char c);
  static unsigned toDigit(char c);
  static char toChar(unsigned digit);
};

String operator+(const String &string1, const String &string2);
bool operator==(const String &string1, const String &string2);
bool operator!=(const String &string1, const String &string2);

std::istream &operator>>(std::istream &is, String &string);
std::ostream &operator<<(std::ostream &os, String &string);

#endif