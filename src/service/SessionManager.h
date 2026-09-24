#pragma once

#include <mutex>
#include <string>
#include <unordered_map>

#include <sodium.h>

/**
 * @brief Manages authenticated user sessions.
 *
 * Provides thread-safe session creation, validation,
 * user lookup, and session removal.
 */
class SessionManager
{
public:
    /**
     * @brief Returns the singleton SessionManager instance.
     *
     * @return Reference to the SessionManager singleton.
     */
    static SessionManager& getInstance()
    {
        static SessionManager instance;
        return instance;
    }

    /**
     * @brief Creates a new authenticated session.
     *
     * @param userId ID of the authenticated user.
     * @return Random session token, or an empty string on failure.
     */
    std::string createSession(int userId)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        std::string token = generateToken();

        if (token.empty())
        {
            return "";
        }

        sessions_[token] = userId;

        return token;
    }

    /**
     * @brief Checks whether a session token is valid.
     *
     * @param token Session token to validate.
     * @return true if the session exists; otherwise false.
     */
    bool isValidSession(const std::string& token)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        return sessions_.find(token)
               != sessions_.end();
    }

    /**
     * @brief Retrieves the user ID associated with a session.
     *
     * @param token Session token.
     * @return User ID, or -1 if the session is invalid.
     */
    int getUserId(const std::string& token)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = sessions_.find(token);

        if (it == sessions_.end())
        {
            return -1;
        }

        return it->second;
    }

    /**
     * @brief Removes an authenticated session.
     *
     * @param token Session token to remove.
     */
    void removeSession(const std::string& token)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        sessions_.erase(token);
    }

private:
    SessionManager() = default;

    /**
     * @brief Generates a cryptographically secure session token.
     *
     * @return Random hexadecimal session token.
     */
    std::string generateToken()
    {
        if (sodium_init() < 0)
        {
            return "";
        }

        constexpr size_t TOKEN_BYTES = 32;

        unsigned char randomBytes[TOKEN_BYTES];

        randombytes_buf(
            randomBytes,
            TOKEN_BYTES
        );

        static const char hex[] =
            "0123456789abcdef";

        std::string token;
        token.reserve(TOKEN_BYTES * 2);

        for (size_t i = 0; i < TOKEN_BYTES; ++i)
        {
            token.push_back(
                hex[(randomBytes[i] >> 4) & 0x0F]
            );

            token.push_back(
                hex[randomBytes[i] & 0x0F]
            );
        }

        return token;
    }

    std::unordered_map<std::string, int> sessions_;

    std::mutex mutex_;
};