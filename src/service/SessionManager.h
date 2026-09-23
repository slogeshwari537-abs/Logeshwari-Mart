#pragma once

#include <string>
#include <unordered_map>
#include <mutex>

#include <sodium.h>

class SessionManager
{
public:

    static SessionManager& getInstance()
    {
        static SessionManager instance;
        return instance;
    }

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

    bool isValidSession(const std::string& token)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        return sessions_.find(token)
               != sessions_.end();
    }

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

    void removeSession(const std::string& token)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        sessions_.erase(token);
    }

private:

    SessionManager() = default;

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