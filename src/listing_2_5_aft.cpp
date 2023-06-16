/*
  transfer thread ownership to function
*/

#include <thread>

void f(std::thread t); // pass the ownership of a thread `t` to function `f`

void g() {
  void some_function();

  // create a unnamed thread and pass its ownership to function `f` by implicit move
  f(std::thread(some_function));

  // create a named thread `t` and pass its ownership to function `f` by using `std::move()`
  std::thread t(some_function);
  f(std::move(t));
}

