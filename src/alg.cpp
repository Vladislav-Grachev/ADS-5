// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char dey) {
switch (dey) {
  case '(': return 0;
  case ')': return 1;
  case '-': return 2;
  case '+': return 2;
  case '*': return 3;
  case '/': return 3;
  case ' ': return 5;
  default: return 4;
  }
}
int calc(char dey, int x, int y) {
switch (dey) {
  case '-': return (y - x);
  case '+': return (x + y);
  case '*': return (x * y);
  case '/':
    if (x != 0)
      return y / x;
default: return 0;
}
}
std::string infx2pstfx(std::string inf) {
  std::string res;
  char probel = ' ';
  TStack <char, 100> stack;
  for (int i = 0; i < inf.size(); i++) {
    if (prioritet(inf[i]) == 4) {
      res.push_back(inf[i]);
      res.push_back(probel);
    } else {
      if (prioritet(inf[i]) == 0) {
        stack.push(inf[i]);
      } else if (stack.isEmpty()) {
        stack.push(inf[i]);
      } else if ((prioritet(inf[i]) > prioritet(stack.get()))) {
        stack.push(inf[i]);
      } else if (prioritet(inf[i]) == 1) {
        while (prioritet(stack.get()) != 0) {
          res.push_back(stack.get());
          res.push_back(probel);
          stack.pop();
        }
        stack.pop();
      } else {
        char l = prioritet(inf[i]);
        char k = prioritet(stack.get());
        while ((l <= k) && (!stack.isEmpty())) {
          res.push_back(stack.get());
          res.push_back(probel);
          stack.pop();
        }
        stack.push(inf[i]);
      }
    }
  }
  while (!stack.isEmpty()) {
    res.push_back(stack.get());
    res.push_back(probel);
    stack.pop();
  }
  for (int i = 0; i < res.size(); i++) {
    if (res[res.size() - 1] == ' ')
      res.erase(res.size() - 1);
    }
  return res;
  }

int eval(std::string pref) {
TStack <int, 100> kon_stack;
int o = 0;
int p = 0;
int r = 0;
for (int i = 0; i < pref.size(); i++) {
  if (prioritet(pref[i]) == 4) {
    kon_stack.push(pref[i] - '0');
  } else if (prioritet(pref[i]) < 4) {
    o = kon_stack.get();
    kon_stack.pop();
    p = kon_stack.get();
    kon_stack.pop();
    kon_stack.push(calc(pref[i], o, p));
  }
}
r = kon_stack.get();
return r;
}
