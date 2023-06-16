/*
  returning a std::thread from a function
*/

#include <thread>

std::thread f() {
  void some_function();
  return std::thread(some_function);
}

std::thread g() {
  void some_other_function(int);
  std::thread t(some_other_function, 42);
  return t;
}
