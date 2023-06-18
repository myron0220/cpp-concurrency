/*
  spawn some threads and wait for them to finish
*/

#include <vector>
#include <thread>
#include <iostream>
#include <string>

void do_work(unsigned id) {
  std::string message = "this is from thread: [" + std::to_string(id) + "].\n";
  std::cout << message;
}

void f() {
  std::vector<std::thread> threads;
  
  for (unsigned i = 0; i < 20; ++i) {
    threads.push_back(std::thread(do_work, i));
  }

  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main() {
  f();
  std::cout << "----------- main end ----------" << std::endl;
}
