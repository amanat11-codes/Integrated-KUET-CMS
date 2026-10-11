PRAGMA foreign_keys = ON;

CREATE TABLE notices (
    "notice_id" INTEGER NOT NULL,
    "date" TEXT NOT NULL,
    "title" TEXT NOT NULL,
    "intro" TEXT NOT NULL,
    "details" TEXT NOT NULL,
    PRIMARY KEY ("notice_id" AUTOINCREMENT)
);

-- Student table
CREATE TABLE students (
    student_id TEXT PRIMARY KEY,
    password TEXT NOT NULL
);

-- Hall details table
CREATE TABLE hall_details (
    student_id TEXT PRIMARY KEY,
    hall_name TEXT NOT NULL,
    boarder_no TEXT,
    meal_status BOOLEAN,
    hall_side TEXT,
    feast_date TEXT,
    FOREIGN KEY (student_id)
        REFERENCES students(student_id)
);

-- One academic-information record per student
CREATE TABLE academic_information (
    student_id TEXT PRIMARY KEY,
	name TEXT NOT NULL,
    session TEXT NOT NULL,
    year TEXT NOT NULL,
    term TEXT NOT NULL,
    credit_taken REAL NOT NULL DEFAULT 0.0,
    credit_completed REAL NOT NULL DEFAULT 0.0,
    term_gpa REAL NOT NULL DEFAULT 0.0,
    cgpa REAL NOT NULL DEFAULT 0.0,
    course1_no TEXT,
    course1_title TEXT,
    course1_credit REAL,
    course1_grade_point REAL,
    course1_letter_grade TEXT,
    course2_no TEXT,
    course2_title TEXT,
    course2_credit REAL,
    course2_grade_point REAL,
    course2_letter_grade TEXT,
    course3_no TEXT,
    course3_title TEXT,
    course3_credit REAL,
    course3_grade_point REAL,
    course3_letter_grade TEXT,
    course4_no TEXT,
    course4_title TEXT,
    course4_credit REAL,
    course4_grade_point REAL,
    course4_letter_grade TEXT,
    course5_no TEXT,
    course5_title TEXT,
    course5_credit REAL,
    course5_grade_point REAL,
    course5_letter_grade TEXT,

    FOREIGN KEY (student_id)
        REFERENCES students(student_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,

    CHECK (credit_taken >= 0),
    CHECK (credit_completed >= 0 AND credit_completed <= credit_taken),
    CHECK (term_gpa BETWEEN 0.0 AND 4.0),
    CHECK (cgpa BETWEEN 0.0 AND 4.0)
);
