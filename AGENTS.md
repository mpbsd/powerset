## Build, Lint, and Test Commands

- **Build:** `make build`
- **Run:** The build command also runs the executable.
- **Memory Check:** `make chase` (runs valgrind)
- **Clean:** `make clean`
- **Testing:** There is no dedicated test suite.

## Code Style Guidelines

- **Language:** C (C89 standard)
- **Formatting:**
  - Indentation: 2 spaces.
  - Braces: Opening brace on the same line for functions.
  - Spacing: Use spaces around operators.
- **Naming Conventions:**
  - Functions: `lowercase_with_underscores` (e.g., `poweroftwo`).
  - Variables: `lowercase` (e.g., `powerset`).
  - Constants: `UPPERCASE` (e.g., `N`).
- **Error Handling:**
  - Check the return value of `malloc` and handle allocation failures.
- **Comments:**
  - The codebase uses `/*{{{*/` and `/*}}}*/` for code folding. This is not a strict requirement.
