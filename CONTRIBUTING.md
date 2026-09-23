# Contributing to Logeshwari Mart

Thank you for contributing to Logeshwari Mart.

## Development Requirements

- Use C++20.
- Follow the existing project folder structure.
- Use Drogon for HTTP/API development.
- Use PostgreSQL for database operations.
- Use parameterized SQL queries.
- Never commit API keys, passwords, database credentials, or `.env` files.
- Keep authentication and authorization checks enabled for protected routes.
- Follow the existing coding style and `.clang-format` configuration.

## Before Committing

1. Build the project successfully.
2. Run the GoogleTest test suite.
3. Check that changed features work correctly.
4. Do not commit generated build files or secrets.

## Commit Guidelines

Use clear commit messages that briefly describe the change.

Examples:

- `Add product image URL support`
- `Fix duplicate review prevention`
- `Add Gemini chatbot integration`
- `Improve authentication handling`

## Pull Requests

Pull requests should:

- Clearly describe the change.
- Mention important files or features modified.
- Include testing performed.
- Avoid unrelated changes.
- Ensure the project builds successfully before submission.