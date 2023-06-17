/*
  avoid using reference to local variable
  OR 
  make sure the thread is guaranteed to finish before the function exits
*/

#include <iostream>
#include <thread>

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

void oops() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.join();
}

int main() {
  oops();
}
