.PHONY: all run clean

all: app.exe

app.exe: build/app.o build/admin/addNoticePage.o build/admin/adminDashboardPage.o build/admin/removeAccountPage.o build/admin/removeNoticePage.o build/authentication/adminLoginPage.o build/authentication/adminRegistrationPage.o build/authentication/loginPortal.o build/authentication/mainMenu.o build/authentication/registrationPortal.o build/authentication/studentLoginPage.o build/authentication/studentRegistrationPage.o build/authentication/teacherLoginPage.o build/authentication/teacherRegistrationPage.o build/notices/noticesPage.o build/student/academicInfoPage.o build/student/ctMarksPage.o build/student/hallDetailsPage.o build/student/libraryInfoPage.o build/student/studentDashboard.o build/student/studentProfilePage.o build/student/termMarksPage.o build/student/teacherProfilePage.o build/student/updateStudentProfile.o build/teacher/teacherDashboard.o build/teacher/updatePersonalInfo.o build/utility/utility.o
	gcc -Wall -Wextra -std=c11 -g -o app.exe build/app.o build/admin/addNoticePage.o build/admin/adminDashboardPage.o build/admin/removeAccountPage.o build/admin/removeNoticePage.o build/authentication/adminLoginPage.o build/authentication/adminRegistrationPage.o build/authentication/loginPortal.o build/authentication/mainMenu.o build/authentication/registrationPortal.o build/authentication/studentLoginPage.o build/authentication/studentRegistrationPage.o build/authentication/teacherLoginPage.o build/authentication/teacherRegistrationPage.o build/notices/noticesPage.o build/student/academicInfoPage.o build/student/ctMarksPage.o build/student/hallDetailsPage.o build/student/libraryInfoPage.o build/student/studentDashboard.o build/student/termMarksPage.o build/student/studentProfilePage.o build/student/teacherProfilePage.o build/student/updateStudentProfile.o build/teacher/teacherDashboard.o build/teacher/updatePersonalInfo.o build/utility/utility.o

build/app.o: src/app.c
	if not exist "build" mkdir "build"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/app.c -o build/app.o

build/admin/addNoticePage.o: src/admin/addNoticePage.c
	if not exist "build\admin" mkdir "build\admin"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/admin/addNoticePage.c -o build/admin/addNoticePage.o

build/admin/adminDashboardPage.o: src/admin/adminDashboardPage.c
	if not exist "build\admin" mkdir "build\admin"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/admin/adminDashboardPage.c -o build/admin/adminDashboardPage.o

build/admin/removeAccountPage.o: src/admin/removeAccountPage.c
	if not exist "build\admin" mkdir "build\admin"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/admin/removeAccountPage.c -o build/admin/removeAccountPage.o

build/admin/removeNoticePage.o: src/admin/removeNoticePage.c
	if not exist "build\admin" mkdir "build\admin"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/admin/removeNoticePage.c -o build/admin/removeNoticePage.o

build/authentication/adminLoginPage.o: src/authentication/adminLoginPage.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/adminLoginPage.c -o build/authentication/adminLoginPage.o

build/authentication/adminRegistrationPage.o: src/authentication/adminRegistrationPage.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/adminRegistrationPage.c -o build/authentication/adminRegistrationPage.o

build/authentication/loginPortal.o: src/authentication/loginPortal.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/loginPortal.c -o build/authentication/loginPortal.o

build/authentication/mainMenu.o: src/authentication/mainMenu.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/mainMenu.c -o build/authentication/mainMenu.o

build/authentication/registrationPortal.o: src/authentication/registrationPortal.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/registrationPortal.c -o build/authentication/registrationPortal.o

build/authentication/studentLoginPage.o: src/authentication/studentLoginPage.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/studentLoginPage.c -o build/authentication/studentLoginPage.o

build/authentication/studentRegistrationPage.o: src/authentication/studentRegistrationPage.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/studentRegistrationPage.c -o build/authentication/studentRegistrationPage.o

build/authentication/teacherLoginPage.o: src/authentication/teacherLoginPage.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/teacherLoginPage.c -o build/authentication/teacherLoginPage.o

build/authentication/teacherRegistrationPage.o: src/authentication/teacherRegistrationPage.c
	if not exist "build\authentication" mkdir "build\authentication"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/authentication/teacherRegistrationPage.c -o build/authentication/teacherRegistrationPage.o

build/notices/noticesPage.o: src/notices/noticesPage.c
	if not exist "build\notices" mkdir "build\notices"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/notices/noticesPage.c -o build/notices/noticesPage.o

build/student/academicInfoPage.o: src/student/academicInfoPage.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/academicInfoPage.c -o build/student/academicInfoPage.o

build/student/ctMarksPage.o: src/student/ctMarksPage.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/ctMarksPage.c -o build/student/ctMarksPage.o

build/student/hallDetailsPage.o: src/student/hallDetailsPage.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/hallDetailsPage.c -o build/student/hallDetailsPage.o

build/student/libraryInfoPage.o: src/student/libraryInfoPage.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/libraryInfoPage.c -o build/student/libraryInfoPage.o

build/student/studentDashboard.o: src/student/studentDashboard.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/studentDashboard.c -o build/student/studentDashboard.o

build/student/studentProfilePage.o: src/student/studentProfilePage.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/studentProfilePage.c -o build/student/studentProfilePage.o

build/student/termMarksPage.o: src/student/termMarksPage.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/termMarksPage.c -o build/student/termMarksPage.o

build/student/teacherProfilePage.o: src/student/teacherProfilePage.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/teacherProfilePage.c -o build/student/teacherProfilePage.o

build/student/updateStudentProfile.o: src/student/updateStudentProfile.c
	if not exist "build\student" mkdir "build\student"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/student/updateStudentProfile.c -o build/student/updateStudentProfile.o

build/teacher/teacherDashboard.o: src/teacher/teacherDashboard.c
	if not exist "build\teacher" mkdir "build\teacher"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/teacher/teacherDashboard.c -o build/teacher/teacherDashboard.o

build/teacher/updatePersonalInfo.o: src/teacher/updatePersonalInfo.c
	if not exist "build\teacher" mkdir "build\teacher"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/teacher/updatePersonalInfo.c -o build/teacher/updatePersonalInfo.o

build/utility/utility.o: src/utility/utility.c
	if not exist "build\utility" mkdir "build\utility"
	gcc -Wall -Wextra -std=c11 -g -Iheaders -Iheaders/admin -Iheaders/authentication -Iheaders/notices -Iheaders/student -Iheaders/teacher -Iheaders/utility -c src/utility/utility.c -o build/utility/utility.o

run: app.exe
	.\app.exe

clean:
	if exist "build" rmdir /s /q "build"
	if exist "app.exe" del /q "app.exe"
