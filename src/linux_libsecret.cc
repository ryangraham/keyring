#ifdef __linux__

#include <libsecret/secret.h>

#include <string>

namespace keyring {

const SecretSchema *keyring_schema(void) {
  static const SecretSchema schema = {
      "org.keyring.Password",
      SECRET_SCHEMA_DONT_MATCH_NAME,
      {{"service_name", SECRET_SCHEMA_ATTRIBUTE_STRING},
       {"account", SECRET_SCHEMA_ATTRIBUTE_STRING}}};
  return &schema;
}

int set_password(const std::string &service_name, const std::string &account,
                 const std::string &password) {
  GError *error = NULL;
  std::string label = service_name + "-" + account;
  secret_password_store_sync(keyring_schema(), SECRET_COLLECTION_DEFAULT,
                             label.c_str(), password.c_str(), NULL, &error,
                             "service_name", service_name.c_str(), "account",
                             account.c_str(), NULL);

  if (error != NULL) {
    // TODO?
    g_error_free(error);
    return -1;
  }

  return 0;
}

int get_password(const std::string &service_name, const std::string &account,
                 std::string &password) {
  GError *error = NULL;
  gchar *tmp_password = secret_password_lookup_sync(
      keyring_schema(), NULL, &error, "service_name", service_name.c_str(),
      "account", account.c_str(), NULL);

  if (error != NULL) {
    g_error_free(error);
    return -1;
  }

  // Password not found
  if (tmp_password == NULL) return -1;

  password = std::string(tmp_password);
  secret_password_free(tmp_password);
  return 0;
}

}  // namespace keyring

#endif
