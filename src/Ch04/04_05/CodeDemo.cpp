// Learning C++ 
// Challenge 04_05
// Calculate a GPA, by Eduardo Corpeño 

#include <iostream>
#include <vector>
#include "records.h"
float ZamienLitereNaOcene(char letter_grade){
    float result=0.0f;
    switch (letter_grade)
    {
    case 'A':
        result=4.0f;
        break;
    case 'B':
        result=3.0f;
        break;
    case 'C':
        result=2.0f;
        break;
    case 'D':   
        result=1.0f;
        break;
    case 'F':
        result=0.0f;
        break;
    default:
        result=0.0f;
        break;
    }
    return result;
}
int main()
{
    float GPA = 0.0f;
    int id;
    
    std::vector<Student> students = {Student(1, "George P. Burdell"),
                                    Student(2, "Nancy Rhodes")};

    std::vector<Course> courses = {Course(1, "Algebra", 5),
                                Course(2, "Physics", 4),
                                Course(3, "English", 3),
                                Course(4, "Economics", 4)};

    std::vector<Grade> grades = {Grade(1, 1, 'B'), Grade(1, 2, 'A'), Grade(1, 3, 'C'),
                                Grade(2, 1, 'A'), Grade(2, 2, 'A'), Grade(2, 4, 'B')};

    std::cout << "Enter a student ID: " << std::flush;
    std::cin >> id;
    float total_points=0.0f;
    int total_credits=0;
    std::string student_str;
    for(auto s:students)
    {
        if(s.get_id()==id)
        {
            student_str=s.get_name();
            for(auto g:grades)
            {
                if(g.get_student_id()==id)
                {
                    for(auto c:courses)
                    {
                        if(c.get_id()==g.get_course_id())
                        {
                            float grade_digit=0.0f;
                            grade_digit=ZamienLitereNaOcene(g.get_grade());
                            int credit=c.get_credits();
                            total_points+=grade_digit*credit;
                            total_credits+=credit;

                        }
                
                    }
                }
            }
        }

    
    
    }
    GPA=total_points/(float)total_credits;
    std::cout << "The GPA for " << student_str << " is " << GPA << std::endl;
    std::cout << std::endl << std::endl;
    return (0);
}
