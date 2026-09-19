#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
#include <random>
#include <sstream>
#include <iomanip>

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
        std::random_device rd;
        std::mt19937_64 generator(rd());

        std::uniform_int_distribution<unsigned long long>
            distribution;

        std::stringstream stream;

        for (int i = 0; i < 4; ++i)
        {
            stream
                << std::hex
                << std::setw(16)
                << std::setfill('0')
                << distribution(generator);
        }

        return stream.str();
    }

    std::unordered_map<std::string, int> sessions_;

    std::mutex mutex_;
};