#pragma once

#include <string>

/**
 * @brief Provides authentication and password security operations.
 */
class AuthService
{
public:
    /**
     * @brief Hashes a user's password using a secure password hashing algorithm.
     *
     * @param password Plain-text password.
     * @return Securely hashed password.
     */
    std::string hashPassword(const std::string& password);

    /**
     * @brief Verifies a password against its stored hash.
     *
     * @param password Plain-text password supplied during login.
     * @param passwordHash Previously stored password hash.
     * @return true if the password matches; otherwise false.
     */
    bool verifyPassword(const std::string& password,
                        const std::string& passwordHash);

    /**
     * @brief Authenticates a user using email and password.
     *
     * @param email User email address.
     * @param password User password.
     * @return true if authentication succeeds; otherwise false.
     */
    bool login(const std::string& email,
               const std::string& password);
};