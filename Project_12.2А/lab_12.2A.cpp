#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Speciality { CS, IT, MECH, ELECTRONICS, MATH };
wstring specialityStr[] = { L"Computer Science", L"Information Technology", L"Mechanics", L"Electronics", L"Mathematics" };


// Структура для збереження даних про студента
struct Student {
    int id;                 // Порядковий номер студента у групі
    char surname[50];       // Прізвище
    int course;             // Курс
    Speciality speciality;
    // Спеціальність (індекс у масиві)
    int physics;            // Оцінка з фізики
    int math;               // Оцінка з математики
    int informatics;        // Оцінка з інформатики
};

// Функція для створення файлу студентів
void CreateFile(const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Error: Unable to create file." << endl;
        return;
    }

    char choice;
    int idCounter = 1; // Лічильник для автоматичного встановлення id
    do {
        Student student;
        student.id = idCounter++;
        cout << "Enter student data:\n";
        cout << "Surname: ";
        cin.ignore();
        cin.getline(student.surname, sizeof(student.surname));
        cout << "Course: ";
        cin >> student.course;
        int specialityIndex;
        wcout << L"Speciality (0 - Computer Science, 1 - Information Technology, 2 - Mechanics, 3 - Electronics, 4 - Mathematics):";
        wcin >> specialityIndex;
        student.speciality = static_cast<Speciality>(specialityIndex);

        cout << "Physics grade: ";
        cin >> student.physics;
        cout << "Math grade: ";
        cin >> student.math;
        cout << "Informatics grade: ";
        cin >> student.informatics;

        fout.write((char*)&student, sizeof(Student));

        cout << "Add another student? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    fout.close();
}

// Функція для виводу студентів у вигляді таблиці
void PrintFile(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    Student student;

    cout << string(104, '=') << endl;
    cout << setw(5) << "ID" << setw(3)
        << "|" << setw(15) << "Surname" << setw(3)
        << "|" << setw(10) << "Course" << setw(3)
        << "|" << setw(20) << "Speciality" << setw(3)
        << "|" << setw(10) << "Physics" << setw(3)
        << "|" << setw(10) << "Math" << setw(3)
        << "|" << setw(15) << "Informatics" << setw(3)
        << endl;

    while (fin.read((char*)&student, sizeof(Student))) {
        cout << string(104, '-') << endl;
        wcout << setw(5) << student.id << setw(3)
            << "|" << setw(15) << student.surname << setw(3)
            << "|" << setw(10) << student.course << setw(3)
            << "|" << setw(20) << student.speciality << setw(3) // Виводимо назву спеціальності
            << "|" << setw(10) << student.physics << setw(3)
            << "|" << setw(10) << student.math << setw(3)
            << "|" << setw(15) << student.informatics << setw(3)
            << endl;
    }
    cout << string(104, '=') << endl;

    fin.close();
}

// Функція для пошуку студентів, які вчаться на відмінно
void FindExcellentStudents(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    Student student;
    cout << "Students with excellent grades:\n";

    while (fin.read((char*)&student, sizeof(Student))) {
        if (student.physics == 5 && student.math == 5 && student.informatics == 5) {
            cout << student.surname << endl;
        }
    }

    fin.close();
}

// Функція для обчислення відсотка студентів із середнім балом більше 4.5
void CalculateHighAveragePercentage(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }


    Student student;
    int totalStudents = 0;
    int highAverageCount = 0;

    while (fin.read((char*)&student, sizeof(Student))) {
        totalStudents++;
        double average = (student.physics + student.math + student.informatics) / 3.0;
        if (average > 4.5) {
            highAverageCount++;
        }
    }

    fin.close();

    if (totalStudents > 0) {
        double percentage = (highAverageCount * 100.0) / totalStudents;
        cout << "Percentage of students with an average grade > 4.5: " << percentage << "%" << endl;
    }
    else {
        cout << "No students in the file." << endl;
    }
}

int main() {

    SetConsoleCP(1251);        // Встановлює кодову сторінку для вводу
    SetConsoleOutputCP(1251);  // Встановлює кодову сторінку для виводу

    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Create file (add students)\n";
        cout << "2. Print file (print table with students)\n";
        cout << "3. Find excellent students\n";
        cout << "4. Calculate percentage of students with average grade > 4.5\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1:
            CreateFile(filename);
            break;
        case 2:
            PrintFile(filename);
            break;
        case 3:
            FindExcellentStudents(filename);
            break;
        case 4:
            CalculateHighAveragePercentage(filename);
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
