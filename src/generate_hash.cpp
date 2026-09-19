#include <iostream>
#include <cstring>
#include <sodium.h>

int main()
{
    if (sodium_init() < 0)
    {
        std::cout << "Sodium initialization failed";
        return 1;
    }

    const char* password = "Admin@123";

    char hash[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(
            hash,
            password,
            strlen(password),
            crypto_pwhash_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
        std::cout << "Hash generation failed";
        return 1;
    }

    std::cout << hash << std::endl;

    return 0;
}