#ifndef STRING_H_
#define STRING_H_

#include <cstddef>

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

  String &concat(const char *extra);

  const char *getData() const;
  size_t getLength() const;

  String &operator+=(const String &other);
};

String operator+(const String &string1, const String &string2);
bool operator==(const String &string1, const String &string2);
bool operator!=(const String &string1, const String &string2);

#endif