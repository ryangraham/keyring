#pragma once

#ifdef __APPLE__
#include <Security/Security.h>

#include <string>

namespace keyring {

int set_password(const std::string &service_name, const std::string &account,
                 const std::string &password) {
  return SecKeychainAddGenericPassword(
      nullptr, service_name.size(), service_name.c_str(), account.size(),
      account.c_str(), password.size(), password.c_str(), nullptr);
}

int get_password(const std::string &service_name, const std::string &account,
                 std::string &password) {
  UInt32 pw_len;
  char *buffer;

  auto ret = SecKeychainFindGenericPassword(
      nullptr, service_name.size(), service_name.c_str(), account.size(),
      account.c_str(), &pw_len, reinterpret_cast<void **>(&buffer), nullptr);

  if (ret == 0) {
    password = std::string(buffer, pw_len);
    SecKeychainItemFreeContent(nullptr, buffer);
  }

  return ret;
}

}  // namespace keyring

#endif