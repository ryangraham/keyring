#include <keyring/keyring.h>

#include <iostream>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// int main() {
//   std::string service_name = "foo";
//   std::string account = "bar";
//   std::string password_input = "password";
//   std::string password_output = "";
//   keyring::set_password(service_name, account, password_input);

//   keyring::get_password(service_name, account, password_output);

//   std::cout << password_output << std::endl;

//   return 0;
// }

TEST_CASE("store -> retrieve") {
  std::string service_name = "foo";
  std::string account = "bar";
  std::string password_input = "password";
  std::string password_output = "";
  keyring::set_password(service_name, account, password_input);

  keyring::get_password(service_name, account, password_output);

  CHECK(password_input == password_output);
}
