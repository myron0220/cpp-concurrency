/*
  RAII (Resource Acquisition Is Initialization) i.e. thread_guard
*/

#include <iostream>
#include <thread>
#include <string>

class thread_guard {
  private:
    std::thread& t;

  public:
    // disable implicit conversion e.g. thread_guard (200)
    explicit thread_guard(std::thread& t_)
      :t(t_) {}

    ~thread_guard() {
      if (t.joinable()) {
        t.join();
      }
    }

    // to avoid outlive the scope of thread:
    // 1. disable copy constructor
    thread_guard(const thread_guard&) = delete;
    // 2. disable copy-assignment operator
    thread_guard& operator=(const thread_guard&) = delete;
};

struct func {
  int& i;

  func(int& i_)
    :i(i_) {}

  // functor operator
  void operator()() {
    for (unsigned j = 0; j < 1000; ++j) {
      // do_something(i);
      std::string thread_output = "from thread [" + std::to_string(i++) + "]" + '\n';
      std::cout << thread_output;
    }
  }
};

void f() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);

  // do_something_in_current_thread();
  for (int m = 0; m < 100; ++m) {
    std::string main_output = "from main (thread) [" + std::to_string(m) + "]" + '\n';
    std::cout << main_output;
  }

  // MAGIC HERE: 
  // when exiting, the local objects are destroyed (using deconstructor) in reverse order of construction.
}

int main() {
  f();
  return 0;
}
