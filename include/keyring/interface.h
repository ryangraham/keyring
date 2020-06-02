#pragma once

#include <string>

namespace keyring {

int set_password(const std::string &service_name, const std::string &account,
                 const std::string &password);

int get_password(const std::string &service_name, const std::string &account,
                 std::string &password);

}  // namespace keyring
