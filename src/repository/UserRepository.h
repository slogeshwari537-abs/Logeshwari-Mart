#pragma once

#include <optional>
#include <string>

#include "../model/User.h"

/**
 * @brief Provides database operations for user accounts.
 */
class UserRepository
{
public:
    /**
     * @brief Checks whether a user exists with the given email.
     *
     * @param email User email address.
     * @return true if the user exists; otherwise false.
     */
    bool userExists(
        const std::string& email
    );

    /**
     * @brief Registers a new user in the database.
     *
     * @param name User's display name.
     * @param email User email address.
     * @param passwordHash Securely hashed password.
     * @param role User role.
     * @return true if registration succeeds; otherwise false.
     */
    bool registerUser(
        const std::string& name,
        const std::string& email,
        const std::string& passwordHash,
        const std::string& role
    );

    /**
     * @brief Retrieves the stored password hash for an email.
     *
     * @param email User email address.
     * @return Stored password hash, or an empty string if not found.
     */
    std::string getPasswordHash(
        const std::string& email
    );

    /**
     * @brief Retrieves a user by email address.
     *
     * @param email User email address.
     * @return User details when found; otherwise std::nullopt.
     */
    std::optional<User> getUserByEmail(
        const std::string& email
    );

    /**
     * @brief Retrieves a user by user ID.
     *
     * @param userId Unique user ID.
     * @return User details when found; otherwise std::nullopt.
     */
    std::optional<User> getUserById(
        int userId
    );
};