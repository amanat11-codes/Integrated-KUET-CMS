# Integrated KUET CMS — Workflow Summary

## 1. System overview

Integrated KUET CMS is a C11 console application backed by a local SQLite database.
The current implementation is organized by role and feature:

- **Authentication:** student, teacher, and admin entry points.
- **Student area:** profile, hall, library, academic, and teacher-profile views.
- **Teacher area:** dashboard shell for updating CT and term marks.
- **Admin area:** notice creation, deletion, viewing, and a notifications placeholder.
- **Shared services:** SQLite database opening, input helpers, screen clearing, and display formatting.

The application entry point is [`src/main.c`](src/main.c). It opens
`database/database.db`, then transfers control to the common login menu.

## 2. Main application flow

```mermaid
flowchart TD
    A["Start"] --> B["main"]
    B --> C["Open database/database.db"]
    C --> D["Database opened?"]
    D -- "No" --> E["Print SQLite error and exit"]
    D -- "Yes" --> F["Display login menu"]
    F --> G["User choice"]
    G -- "Student" --> H["studentLoginPage"]
    G -- "Teacher" --> I["teacherLoginPage"]
    G -- "Admin" --> J["adminLoginPage"]
    G -- "Notices" --> K["noticesPage"]
    G -- "Quit" --> L["Close database and exit"]
    H --> F
    I --> F
    J --> F
    K --> F
```

`loginPage()` validates menu input from 1 through 5. Student and teacher login
currently act as placeholders and immediately open their dashboards. Admin login
checks hard-coded credentials (`1001` / `2002`) before opening the admin dashboard.

## 3. Role workflows

```mermaid
flowchart LR
    A["Student login"] --> B["Student dashboard menu"]
    B --> B1["View profile"]
    B --> B2["View hall details"]
    B --> B3["View academic information"]
    B --> B4["View library information"]
    B --> B5["View teacher profile"]
    B1 --> B
    B2 --> B
    B3 --> B
    B4 --> B
    B5 --> B
    B --> B6["Quit and return"]

    C["Teacher login"] --> D["Teacher dashboard"]
    D --> D1["Update CT marks"]
    D --> D2["Update term marks"]

    E["Admin login"] --> F["Admin dashboard"]
    F --> F1["Add notice"]
    F --> F2["Remove notice"]
    F --> F3["View notices"]
    F --> F4["View notifications"]
    F --> F5["Quit"]
```

The student dashboard now presents a selectable menu and returns to that menu
after each page. The academic-information and library-information pages wait for
ENTER before returning. The teacher options are displayed but are not wired to an
input loop. Several student pages display static or placeholder data and do not
query the database.

## 4. Notice workflow

```mermaid
flowchart TD
    A["Open notices"] --> B["Count rows in notices table"]
    B --> C["Load all notices into memory"]
    C --> D["Display ID, date, title and intro"]
    D --> E["Enter notice ID"]
    E -- "0" --> F["Free memory and return"]
    E -- "Valid ID" --> G["Query full notice by ID"]
    G --> H["Display notice details"]
    H --> D
    E -- "Invalid ID" --> I["Ask again"]
    I --> E

    J["Admin: add notice"] --> K["Read title, date and details"]
    K --> L["Generate short intro"]
    L --> M["Parameterized INSERT"]
    M --> N["Notice saved"]

    O["Admin: remove notice"] --> P["Validate notice ID"]
    P --> Q["Parameterized DELETE"]
    Q --> R["Notice removed"]
```

The only defined database table is `notices`, with `notice_id`, `date`, `title`,
`intro`, and `details` fields. [`database/seed.sql`](database/seed.sql) supplies
initial notices. Notice reads and writes use prepared statements and bound
parameters.

## 5. Build and execution workflow

```mermaid
flowchart TD
    A["Source files under src"] --> B["make discovers C files"]
    B --> C["Compile object files"]
    C --> D["Generate dependency files for headers"]
    D --> E["Link executable app or app.exe"]
    E --> F["make run"]
    F --> G["Open SQLite database and start menu"]
    H["make clean"] --> I["Remove build directory and executable"]
```

The [`makefile`](makefile) uses GCC, C11, warnings, debug symbols, automatic
header dependencies, and OS-aware cleanup commands.

## 6. Current implementation status

### Working or substantially implemented

- Common menu loop and input validation.
- SQLite database opening and shutdown.
- Notice listing, detail viewing, addition, and deletion.
- Admin password gate.
- Selectable student dashboard with return-to-menu behavior.
- Academic and library pages with ENTER-to-return prompts.
- Basic display/input utility functions.
- Seed data and a reusable local database file.

### Incomplete or needing attention

- Student and teacher authentication are placeholders.
- Student pages are mostly static demonstrations; no student data tables exist.
- Teacher mark editing is only a display stub.
- Admin notifications are only a placeholder.
- Error handling around several SQLite prepare/bind calls is incomplete.
- `clearScreen()` is Windows-specific (`cls`) despite the makefile supporting
  non-Windows builds.

## 7. Suggested next implementation order

1. Add user, student, teacher, course, marks, and hall/library tables.
2. Replace placeholder login pages with database-backed authentication.
3. Wire the remaining student pages to persistent data.
4. Convert the teacher dashboard into a selectable menu loop.
5. Add complete SQLite error checking and transaction handling.
6. Add targeted tests for authentication, notice CRUD, and invalid input.
