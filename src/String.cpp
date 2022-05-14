#include "String.h"

#include <utility>
#include <cstring>

String::String(const char *data)
{
  this->copy(data);
}

String::String(const String &other)
{
  this->copy(other.data);
}

String::String(String &&other)
{
  this->move(std::move(other));
}

String &String::operator=(const String &other)
{
  if (this != &other)
  {
    this->free();
    this->copy(other.data);
  }

  return *this;
}

String &String::operator=(String &&other)
{
  if (this != &other)
  {
    this->move(std::move(other));
  }

  return *this;
}

char &String::operator[](size_t index)
{
  if (index >= this->length)
  {
    throw "Invalid index";
  }
  return this->data[index];
}

char String::operator[](size_t index) const
{
  if (index >= this->length)
  {
    throw "Invalid index";
  }
  return this->data[index];
}

String::operator char *() const
{
  return this->data;
}

void String::writeToFile(std::ofstream &file)
{

  file.write((const char *)&this->length, sizeof(this->length));
  file.write((const char *)this->data, this->length);
}

void String::readFromFile(std::ifstream &file)
{
  size_t newLength = 0;
  this->free();

  file.read((char *)&newLength, sizeof(this->length));
  char *newData = new char[newLength];
  file.read(newData, newLength);

  this->copy(newData);
  delete[] newData;
}

String::~String()
{
  this->free();
}

void String::free()
{
  delete[] this->data;
}

void String::copy(const char *data)
{
  if (data == nullptr)
  {
    throw "Cannot copy nullptr to string";
  }

  this->length = strlen(data);
  this->data = new char[this->length + 1];
  strcpy(this->data, data);
}

void String::move(String &&other)
{
  this->data = other.data;
  this->length = other.length;
  other.data = nullptr;
}

String &String::concat(const char *extra)
{
  if (extra == nullptr)
  {
    throw "Cannot copy nullptr to string";
  }

  size_t newLength = this->length + strlen(extra);
  char *newData = new char[newLength + 1];

  strcpy(newData, this->data);
  strcat(newData, extra);

  this->free();
  this->length = newLength;
  this->data = newData;

  return *this;
}

const char *String::getData() const
{
  return this->data;
}

size_t String::getLength() const
{
  return this->length;
}

bool String::isEmpty() const
{
  return this->length == 0;
}

String &String::operator+=(const String &other)
{
  return this->concat(other.data);
}

String operator+(const String &string1, const String &string2)
{
  String copy(string1);

  return (copy += string2);
}

bool operator==(const String &string1, const String &string2)
{
  return strcmp(string1.getData(), string2.getData()) == 0;
}

bool operator!=(const String &string1, const String &string2)
{
  return !(string1 == string2);
}

bool String::isDigit(char c)
{
  return c >= '0' && c <= '9';
}

unsigned String::toDigit(char c)
{
  if (!String::isDigit(c))
  {
    throw "Character is not a digit";
  }
  return c - '0';
}
char String::toChar(unsigned digit)
{
  if (digit >= 10)
  {
    throw "Number is not a digit";
  }
  return '0' + digit;
}

std::istream &operator>>(std::istream &is, String &string)
{
  const size_t MAX_INPUT_LENGTH = 1024;
  char input[MAX_INPUT_LENGTH + 1];

  is.getline(input, MAX_INPUT_LENGTH);
  string = input;

  return is;
}

std::ostream &operator<<(std::ostream &os, const String &string)
{
  os << string.getData();

  return os;
}