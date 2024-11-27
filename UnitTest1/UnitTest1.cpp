#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\admin\source\repos\Project_12.2А\Project_12.2А\lab_12.2A.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest122
{
    TEST_CLASS(UnitTest122)
    {
    public:

        // Тест для перевірки правильної кількості студентів з відмінними оцінками
        TEST_METHOD(TestFindExcellentStudents)
        {
            string filename = "students.dat";

            // Створюємо файл з тестовими студентами
            Student students[3] = {
                { 1, "Вишинська", 1, IT, 5, 5, 5 },
                { 2, "Пащук", 2, ELECTRONICS, 4, 5, 5 },
                { 3, "Булик", 2, CS, 5, 4, 5 }
            };

            ofstream fout(filename, ios::binary);
            for (int i = 0; i < 3; ++i) {
                fout.write((char*)&students[i], sizeof(Student));
            }
            fout.close();

            // Перевіряємо кількість студентів з оцінками 5
            int expectedCount = 1;
            int actualCount = 0;

            ifstream fin(filename, ios::binary);
            Student student;
            while (fin.read((char*)&student, sizeof(Student))) {
                if (student.physics == 5 && student.math == 5 && student.informatics == 5) {
                    ++actualCount;
                }
            }

            Assert::AreEqual(expectedCount, actualCount, L"Перевірка кількості студентів, які вчаться на \"відмінно\"");

        }
    };
}
