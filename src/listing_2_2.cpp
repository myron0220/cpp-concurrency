/*
  not ideal way to wait for a thread to finish
*/

#include <thread>
#include <iostream>

struct func {
  int& i;

  func(int& i_)
    :i(i_) {}

  // functor operator
  void operator()() {
    for (unsigned j = 0; j < 1000000; ++j) {
      // do_something(i);
      std::cout << i++ << '\n';
    }
  }
};

void f() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try {
    // do_something_in_current_thread();
    for (int i = 0; i < 1000; ++i) {
      some_local_state += 1000000000000000000;
    }
  } catch(...) {
    t.join();
    throw;
  }
  t.join();
}

int main() {
  f();
}
