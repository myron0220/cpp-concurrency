/*
  transfer of ownership of thread
  std::move() reference: https://medium.com/@lucianoalmeida1/a-little-bit-about-std-move-efd9d554c09a
*/

#include <thread>
#include <iostream>

void some_function() {
  std::cout << "some_function\n";
};

void some_other_function() {
  std::cout << "some_other_function\n";
}

int main() {
  // t1: some_function
  std::thread t1(some_function);

  // t1: null, t2: some_function
  std::thread t2 = std::move(t1); 

  // t1: some_other_function, t2: some_function
  t1 = std::thread(some_other_function);

  // t1: some_other_function, t2: some_function, t3: null
  std::thread t3;

  // t1: some_other_function, t2: null, t3: some_function
  t3 = std::move(t2);

  // error!!!
  // this will calls std::terminate() as 
  // the thread with `some_other_function` are already in t1 and cannot be stopped
  t1 = std::move(t3); 
}
