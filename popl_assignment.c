#include <iostream.h>
#include <fstream.h>
#include <vector.h>
#include <string.h>

using namespace std;

// Base class for Employee
class Employee {
protected:
    int EMPLOYEE_ID;
    double PAY;

public:
    void getdata(ifstream& file) {
        file >> EMPLOYEE_ID >> PAY;
    }

    void putdata(ofstream& file) {
        file << "EMPLOYEE_ID: " << EMPLOYEE_ID << ", PAY: " << PAY << endl;
    }
};

// Base class for Student
class Student {
protected:
    int STUDENT_ID;
    string STUDENT_NAME;
    double FEES_PAID;
    string COURSES_STUDYING;

public:
    void getdata(ifstream& file) {
        file >> STUDENT_ID >> STUDENT_NAME >> FEES_PAID >> COURSES_STUDYING;
    }

    void putdata(ofstream& file) {
        file << "STUDENT_ID: " << STUDENT_ID << ", STUDENT_NAME: " << STUDENT_NAME
             << ", FEES_PAID: " << FEES_PAID << ", COURSES_STUDYING: " << COURSES_STUDYING << endl;
    }

    int getStudentID() const {
        return STUDENT_ID;
    }

    bool isStudyingCourses() const {
        return !COURSES_STUDYING.empty();
    }
};

// Derived class for Instructor who inherits both Employee and Student
class Instructor : public Employee, public Student {
public:
    void listInstructorStudents(const vector<Student>& students) {
        cout << "Instructors who are also students: " << endl;
        for (const auto& student : students) {
            if (student.getStudentID() == STUDENT_ID) {
                if (student.isStudyingCourses()) {
                    cout << "Instructor ID: " << STUDENT_ID << ", Name: " << STUDENT_NAME << endl;
                    cout << "Courses Teaching: " << COURSES_STUDYING << endl;
                }
            }
        }
    }

    static void listNonInstructorStudents(const vector<Student>& students, const vector<Instructor>& instructors) {
        cout << "Students who are not instructors: " << endl;
        for (const auto& student : students) {
            bool isStudentAnInstructor = false;
            for (const auto& instructor : instructors) {
                if (student.getStudentID() == instructor.getStudentID()) {
                    isStudentAnInstructor = true;
                    break;
                }
            }
            if (!isStudentAnInstructor) {
                cout << "Student ID: " << student.getStudentID() << ", Name: " << student.STUDENT_NAME << endl;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Usage: " << argv[0] << " input_employee.txt input_instructor.txt input_student.txt output.txt" << endl;
        return 1;
    }

    ifstream employeeFile(argv[1]);
    ifstream instructorFile(argv[2]);
    ifstream studentFile(argv[3]);
    ofstream outputFile(argv[4], ios::app);

    if (!employeeFile || !instructorFile || !studentFile || !outputFile) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    // Read data for employees
    vector<Employee> employees;
    Employee emp;
    while (!employeeFile.eof()) {
        emp.getdata(employeeFile);
        employees.push_back(emp);
    }

    // Read data for instructors
    vector<Instructor> instructors;
    Instructor instr;
    while (!instructorFile.eof()) {
        instr.getdata(instructorFile);
        instructors.push_back(instr);
    }

    // Read data for students
    vector<Student> students;
    Student stud;
    while (!studentFile.eof()) {
        stud.getdata(studentFile);
        students.push_back(stud);
    }

    // Output employees, instructors, students to file
    for (const auto& emp : employees) {
        emp.putdata(outputFile);
    }

    for (const auto& instr : instructors) {
        instr.putdata(outputFile);
    }

    for (const auto& stud : students) {
        stud.putdata(outputFile);
    }

    // Additional logic for listing instructors who are also students and non-instructor students
    for (const auto& instructor : instructors) {
        instructor.listInstructorStudents(students);
    }

    Instructor::listNonInstructorStudents(students, instructors);

    // Close all file streams
    employeeFile.close();
    instructorFile.close();
    studentFile.close();
    outputFile.close();

    return 0;
}
