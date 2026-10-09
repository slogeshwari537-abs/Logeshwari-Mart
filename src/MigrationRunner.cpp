#include "MigrationRunner.h"

#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace
{
    std::string readFile(const std::filesystem::path& path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            throw std::runtime_error(
                "Unable to open migration file: " + path.string()
            );
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }
}

void runMigrations()
{
    auto client = drogon::app().getDbClient();

    client->execSqlSync(
        "CREATE TABLE IF NOT EXISTS schema_migrations ("
        "version VARCHAR(255) PRIMARY KEY,"
        "applied_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP"
        ")"
    );

    const std::filesystem::path migrationsPath =
        "db/migrations";

    if (!std::filesystem::exists(migrationsPath))
    {
        throw std::runtime_error(
            "Migration directory not found: " +
            migrationsPath.string()
        );
    }

    std::vector<std::filesystem::path> migrations;

    for (const auto& entry :
         std::filesystem::directory_iterator(migrationsPath))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".sql")
        {
            migrations.push_back(entry.path());
        }
    }

    std::sort(
        migrations.begin(),
        migrations.end()
    );

    for (const auto& migration : migrations)
    {
        const std::string version =
            migration.filename().string();

        auto result = client->execSqlSync(
            "SELECT version "
            "FROM schema_migrations "
            "WHERE version = $1",
            version
        );

        if (!result.empty())
        {
            spdlog::info(
                "Migration already applied: {}",
                version
            );

            continue;
        }

        spdlog::info(
            "Applying migration: {}",
            version
        );

       const std::string sql = readFile(migration);

std::stringstream statements(sql);
std::string statement;

while (std::getline(statements, statement, ';'))
{
    if (statement.find_first_not_of(" \t\n\r") == std::string::npos)
        continue;

    client->execSqlSync(statement);
}

        client->execSqlSync(
            "INSERT INTO schema_migrations(version) "
            "VALUES ($1)",
            version
        );

        spdlog::info(
            "Migration applied successfully: {}",
            version
        );
    }

    spdlog::info("Database migrations completed.");
}
