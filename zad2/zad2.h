#include <iostream>

class ciag {
 public:
  ciag();
  ciag(const char* cstr);
  ciag(const ciag& inny);
  ~ciag();

  unsigned dl() const;

  ciag& operator=(const ciag& inny);
  ciag& operator+=(const ciag& inny);
  operator const char*();

  static unsigned ile();

  friend ciag operator+(const ciag& str1, const ciag& str2);
  friend std::istream& operator>>(std::istream& is, ciag& cg);
  friend std::ostream& operator<<(std::ostream& is, const ciag& cg);
  
 private:
  char* _dane;
  static unsigned _ile;
  static unsigned strlen(const char* str);
  static char* strcpy(char* to, const char* from);
  
};

ciag operator+(const ciag& str1, const ciag& str2);
std::istream& operator>>(std::istream& is, ciag& cg);
std::ostream& operator<<(std::ostream& os, const ciag& cg);
