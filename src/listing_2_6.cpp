/*
  scoped_thread
*/

#include <thread>
#include <iostream>
#include <string>

class scoped_thread {
  private:
    // as thread `t` is a private field of scoped_thread, scoped_thread takes full control of it
    std::thread t; 

  public:
    // explicit -> avoid:
    /*
      scoped_thread st(variable_of_some_other_type)
    */
    // ------------ note the difference with listing_2_3 ------------
    explicit scoped_thread(std::thread t_)
      : t(std::move(t_)) {} 
    
    ~scoped_thread() {
      t.join();
    }
    // --------------------------------------------------------------

    // disable copy constructor:
    /*
      MyClass obj1; // Create an object
    
      MyClass obj2 = obj1; // Copy constructor is invoked to create 'obj2' as a copy of 'obj1'
    */
    scoped_thread(const scoped_thread&) = delete;

    // disable copy-assignment operator:
    /*
      MyClass obj1; // Create an object
      MyClass obj2; // Create another object

      obj2 = obj1; // Copy-assignment operator is invoked to assign the values of 'obj1' to 'obj2'
    */
    scoped_thread& operator=(const scoped_thread&) = delete;
};

struct func {
  int& i;

  func(int& i_)
    : i(i_) {}

  // functor operator
  /*
    `func(some_local_state)` will be treated as a `function`
  */
  void operator()() {
    for (unsigned j = 0; j < 1000000; ++j) {
      // do_something(i);
      std::cout << i++ << '\n';
    }
  }
};

void f() {
  int some_local_state = 0;
  scoped_thread t(std::thread(func(some_local_state)));

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
}
