#include "AuthService.h"
#include <sodium.h>

std::string AuthService::hashPassword(const std::string& password)
{
    if (sodium_init() < 0)
    {
        return "";
    }

    char hash[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(
            hash,
            password.c_str(),
            password.size(),
            crypto_pwhash_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
        return "";
    }

    return std::string(hash);
}

bool AuthService::verifyPassword(
    const std::string& password,
    const std::string& passwordHash)
{
    if (sodium_init() < 0)
    {
        return false;
    }

    return crypto_pwhash_str_verify(
               passwordHash.c_str(),
               password.c_str(),
               password.size()) == 0;
}

bool AuthService::login(
    const std::string& email,
    const std::string& password)
{
    return !email.empty() && !password.empty();
}