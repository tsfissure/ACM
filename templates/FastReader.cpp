#include <bits/stdc++.h>

namespace tsf {
static const int MAX_BUFFER = 200 << 20;
static char buf[MAX_BUFFER];
static char *curPtr = buf, *endPtr;

void read() { endPtr = buf + fread(buf, 1, MAX_BUFFER, stdin); }

template<typename T>inline bool integer(T& v) {
  bool sgn = false;
  for(v = 0; curPtr < endPtr && !isdigit(*curPtr); ++curPtr) {
    if('-' == *curPtr) { sgn = true; ++curPtr; break; }
  }
  if(curPtr >= endPtr) { return false;}
  for(; curPtr < endPtr && isdigit(*curPtr); ++curPtr) {
    v = (v << 3) + (v << 1) + *curPtr - '0';
  }
  if(sgn) { v = -v; }
  return true;
}

inline bool charer(char *s, bool spaceable = false) {
  for(; curPtr < endPtr && (!isprint(*curPtr) || (!spaceable && ' ' == *curPtr)); ++curPtr);
  if(curPtr >= endPtr) { return false;}
  for(; curPtr < endPtr && isprint(*curPtr); ++curPtr, ++s) {
    if(!spaceable && ' ' == *curPtr) { break; }
    *s = *curPtr;
  }
  *s = 0;
  return true;
}

template<typename T>inline bool floater(T& v) {
  //the decimal length must not ex 18?
  bool sgn = false;
  for(v = 0.0f; curPtr < endPtr && !isdigit(*curPtr); ++curPtr) {
    if('-' == *curPtr) { sgn = true; ++curPtr; break;}
    //if('.' == *curPtr) { break;} if u want to read ".xx" release this
  }
  if(curPtr >= endPtr) { return false;}
  unsigned long long dec = 1;
  for(; curPtr < endPtr && isdigit(*curPtr); ++curPtr) {
    v = v * 10 + *curPtr - '0';
  }
  if(curPtr < endPtr && '.' == *curPtr) {
    for(++curPtr; curPtr < endPtr && isdigit(*curPtr); ++curPtr) {
      v = v * 10 + *curPtr - '0';
      dec = (dec << 3) + (dec << 1);
      //++dec
    }
  }
  v /= dec;
  if(sgn) { v = -v; }
}
}


int main() {
  tsf::read();
  int a;
  tsf::integer(a);
  std::cout << a << std::endl;
  float b;
  //tsf::floater(b);
  //std::cout << b << std::endl;
  char c[2222];
  tsf::charer(c, true);
  std::cout << c << std::endl;
  
  return 0;
}
