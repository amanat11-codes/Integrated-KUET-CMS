PRAGMA foreign_keys = ON;

INSERT INTO notices (date, title, intro, details)
VALUES
(
    '2026-10-01',
    'Term Final Examination Notice',
    'Students are requested to collect their examination schedules.',
    'All students must collect their examination schedules and complete the required academic formalities before the term final examination.'
),
(
    '2026-10-05',
    'Term Final Examination Routine Published',
    'The routine for the upcoming term final examination has been published.',
    'Students are requested to follow the examination routine carefully and report to their respective examination halls at least fifteen minutes before the examination.'
),
(
    '2026-10-10',
    'Submission Deadline for Laboratory Reports',
    'Pending laboratory reports must be submitted within the announced deadline.',
    'Students must submit incomplete laboratory reports to their respective course teachers within the announced deadline.'
),
(
    '2026-10-12',
    'Course Registration Notice',
    'Online course registration for the next academic term will begin soon.',
    'Students are instructed to complete their course registration through the university system within the registration period.'
),
(
    '2026-10-18',
    'Hall Seat Confirmation Notice',
    'Students are requested to verify their hall seat information.',
    'Any correction regarding hall seat information should be submitted to the hall office within three working days.'
);

-- Dummy passwords are the corresponding eight-digit student IDs.
INSERT INTO students (student_id, password)
VALUES
    ('52501001', '52501001'), -- CSE
    ('52502002', '52502002'), -- EEE
    ('52503003', '52503003'), -- ME
    ('52504004', '52504004'), -- CE
    ('52505005', '52505005'), -- MSE
    ('52506006', '52506006'), -- ESE
    ('52507052', '52507052'), -- ECE
    ('52508008', '52508008'), -- URP
    ('52509009', '52509009'), -- ARCHI
    ('52510010', '52510010'); -- BECM

INSERT INTO hall_details
    (student_id, hall_name, boarder_no, meal_status, hall_side, feast_date)
VALUES
    ('52501001', 'Amar Ekushey Hall', 'A-101', 1, 'East', '2026-10-25'),
    ('52502002', 'Fazlul Haque Hall', 'F-204', 1, 'East',  '2026-10-25'),
    ('52503003', 'Lalon Shah Hall',    'L-305', 1, 'West', '2026-10-25'),
    ('52504004', 'Shaheed Smrity Hall',   'B-112', 0, 'West',  '2026-10-25'),
    ('52505005', 'Dr. M. A. Wazed Hall','W-218', 1, 'East', '2026-10-25'),
    ('52506006', 'Amar Ekushey Hall', 'A-220', 1, 'West', '2026-10-25'),
    ('52507052', 'Fazlul Haque Hall', 'F-310', 1, 'West',  '2026-10-25'),
    ('52508008', 'Lalon Shah Hall',    'L-118', 0, 'East',  '2026-10-25'),
    ('52509009', 'Shaheed Smrity Hall',   'B-226', 1, 'East', '2026-10-25'),
    ('52510010', 'Dr. M. A. Rashid Hall','W-104', 1, 'West', '2026-10-25');

INSERT INTO academic_information
(
    student_id, name, session, year, term,
    credit_taken, credit_completed, term_gpa, cgpa,
    course1_no, course1_title, course1_credit, course1_grade_point, course1_letter_grade,
    course2_no, course2_title, course2_credit, course2_grade_point, course2_letter_grade,
    course3_no, course3_title, course3_credit, course3_grade_point, course3_letter_grade,
    course4_no, course4_title, course4_credit, course4_grade_point, course4_letter_grade,
    course5_no, course5_title, course5_credit, course5_grade_point, course5_letter_grade
)
VALUES
(
    '52501001', 'Arafat Hossain', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.75, 3.75,
    'CSE 1101', 'Structured Programming', 3.00, 4.00, 'A+',
    'CSE 1102', 'Structured Programming Lab', 1.50, 3.75, 'A',
    'CSE 1107', 'Discrete Mathematics', 3.00, 3.50, 'A-',
    'CSE 1109', 'Digital Logic Design', 3.00, 3.75, 'A',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.50, 'A-'
),
(
    '52502002', 'Nusrat Jahan', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.60, 3.60,
    'EEE 1101', 'Electrical Circuit Theory', 3.00, 3.75, 'A',
    'EEE 1102', 'Electrical Circuit Laboratory', 1.50, 3.50, 'A-',
    'EEE 1107', 'Electronic Devices', 3.00, 3.50, 'A-',
    'EEE 1109', 'Electrical Measurements', 3.00, 3.75, 'A',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.50, 'A-'
),
(
    '52503003', 'Sabbir Ahmed', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.45, 3.45,
    'ME 1101', 'Engineering Mechanics', 3.00, 3.50, 'A-',
    'ME 1102', 'Engineering Drawing', 1.50, 3.75, 'A',
    'ME 1107', 'Thermodynamics', 3.00, 3.25, 'B+',
    'ME 1109', 'Manufacturing Process', 3.00, 3.50, 'A-',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.25, 'B+'
),
(
    '52504004', 'Mim Akter', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.80, 3.80,
    'CE 1101', 'Engineering Mechanics', 3.00, 4.00, 'A+',
    'CE 1102', 'Civil Engineering Drawing', 1.50, 3.75, 'A',
    'CE 1107', 'Surveying', 3.00, 3.75, 'A',
    'CE 1109', 'Construction Materials', 3.00, 3.75, 'A',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.75, 'A'
),
(
    '52505005', 'Tanvir Hasan', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.55, 3.55,
    'MSE 1101', 'Materials Science', 3.00, 3.50, 'A-',
    'MSE 1102', 'Materials Laboratory', 1.50, 3.75, 'A',
    'MSE 1107', 'Physical Metallurgy', 3.00, 3.25, 'B+',
    'MSE 1109', 'Material Characterization', 3.00, 3.50, 'A-',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.50, 'A-'
),
(
    '52506006', 'Sanjida Islam', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.70, 3.70,
    'ESE 1101', 'Environmental Chemistry', 3.00, 3.75, 'A',
    'ESE 1102', 'Environmental Laboratory', 1.50, 3.50, 'A-',
    'ESE 1107', 'Ecology and Environment', 3.00, 3.75, 'A',
    'ESE 1109', 'Environmental Pollution', 3.00, 3.50, 'A-',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.75, 'A'
),
(
    '52507052', 'Rafiul Karim', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.65, 3.65,
    'ECE 1101', 'Electronic Devices', 3.00, 3.75, 'A',
    'ECE 1102', 'Electronics Laboratory', 1.50, 3.50, 'A-',
    'ECE 1107', 'Signals and Systems', 3.00, 3.50, 'A-',
    'ECE 1109', 'Communication Engineering', 3.00, 3.75, 'A',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.50, 'A-'
),
(
    '52508008', 'Fahmida Noor', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.85, 3.85,
    'URP 1101', 'Introduction to Urban Planning', 3.00, 4.00, 'A+',
    'URP 1102', 'Planning Studio', 1.50, 3.75, 'A',
    'URP 1107', 'Human Settlement Planning', 3.00, 3.75, 'A',
    'URP 1109', 'Urban Sociology', 3.00, 4.00, 'A+',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.75, 'A'
),
(
    '52509009', 'Mahmudul Hasan', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.90, 3.90,
    'ARCHI 1101', 'Architectural Design', 3.00, 4.00, 'A+',
    'ARCHI 1102', 'Architectural Graphics', 1.50, 3.75, 'A',
    'ARCHI 1107', 'History of Architecture', 3.00, 4.00, 'A+',
    'ARCHI 1109', 'Building Materials', 3.00, 3.75, 'A',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 4.00, 'A+'
),
(
    '52510010', 'Jannatul Ferdous', '2025-2026', 'First', 'First',
    13.50, 13.50, 3.50, 3.50,
    'BECM 1101', 'Construction Engineering', 3.00, 3.50, 'A-',
    'BECM 1102', 'Construction Materials Lab', 1.50, 3.25, 'B+',
    'BECM 1107', 'Building Services', 3.00, 3.50, 'A-',
    'BECM 1109', 'Project Planning', 3.00, 3.75, 'A',
    'MATH 1107', 'Differential and Integral Calculus', 3.00, 3.50, 'A-'
);
