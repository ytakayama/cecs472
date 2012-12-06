#include <iostream>
#include <string>
#include "echo_service.cc"
#include "do_echo.cc"
int main() {
  Echo_ptr Echo_Instance = new Echo;
  return do_Echo(Echo_Instance);
}
