#include "records.h"
#include <iostream>
#include <fstream>

Student::Student(int the_id, std::string the_name){
    id = the_id;
    name = the_name;
}
int Student::get_id() const{
    return id;
}
std::string Student::get_name() const{
    return name;
}

Course::Course(int the_id, std::string the_name, unsigned char the_credits){
    id = the_id;
    name = the_name;
    credits = the_credits;
}
int Course::get_id() const{
    return id;
}
std::string Course::get_name() const{
    return name;
}
int Course::get_credits() const{
    return credits;
}


Grade::Grade(int sid, int cid, char grd){
    student_id = sid;
    course_id = cid;
    grade = grd;
}
int Grade::get_student_id() const{
    return student_id;
}
int Grade::get_course_id() const{
    return course_id;
}
char Grade::get_grade() const{
    return grade;
}

void StudentRecords::add_student(int sid, std::string sname){
    students.push_back(Student(sid, sname));
}

void StudentRecords::add_course(int cid, std::string cname, unsigned char ccredits){
    courses.push_back(Course(cid, cname, ccredits));
}

void StudentRecords::add_grade(int sid, int cid, char grade){
    grades.push_back(Grade(sid, cid, grade));
}

float StudentRecords::get_num_grade(char letter) const{
    float num_grd;          // float for the numeric grade
    switch (letter){
        case 'A': num_grd = 4.0f;
            break;
        case 'B': num_grd = 3.0f;
            break;
        case 'C': num_grd = 2.0f;
            break;
        case 'D': num_grd = 1.0f;
            break;
        default:  num_grd = 0.0f;
            break;
    };
    return num_grd;
}

std::string StudentRecords::get_student_name(int sid) const{
    int i = 0;
    while (i < students.size() && students[i].get_id() != sid)
        i++;
    return students[i].get_name();
}

unsigned char StudentRecords::get_course_credits(int cid) const{
    int j = 0;
    while (j < courses.size() && courses[j].get_id() != cid)
        j++;
    return courses[j].get_credits();
}

float StudentRecords::get_GPA(int sid) const{
    float points = 0.0f, credits = 0.0f;
    for (const Grade& grd : grades)
        if (grd.get_student_id() == sid){
            // calculate total credits and points
            unsigned char current_credits = get_course_credits(grd.get_course_id());
            credits += current_credits;
            points += get_num_grade(grd.get_grade()) * current_credits;
        }
    return (points / credits);
}

std::string StudentRecords::get_course_name(int cid) const{
    int j = 0;
    while (j < courses.size() && courses[j].get_id() != cid)
        j++;
    return courses[j].get_name();
}

void StudentRecords::report_card(int sid){
    float points = 0.0f, credits = 0.0f;
    std::cout << std::endl << "Report Card for " << get_student_name(sid) << std::endl;
    for (Grade& grd : grades)
        if (grd.get_student_id() == sid){
            std::cout << get_course_name(grd.get_course_id()) << ": " << grd.get_grade() << std::endl;
            unsigned char current_credits = get_course_credits(grd.get_course_id());
            credits += current_credits;
            points += get_num_grade(grd.get_grade()) * current_credits;
        }
    std::cout << "GPA: " << (points / credits) << std::endl;
}

void StudentRecords::write_report_card_to_file(int sid,std::string output_file){
  std::ofstream outFile;
    float a = 4.333f, b = 5.302f;

    outFile.open(output_file);
    if (outFile.fail())
        std::cout << std::endl << "Couldn't open the file!" << std::endl;
    else
    {
        float points = 0.0f, credits = 0.0f;
        outFile<< "Report Card for " << get_student_name  (sid) << std::endl;
        for (Grade& grd : grades)
        if (grd.get_student_id() == sid){
            outFile << get_course_name(grd.get_course_id()) << ": " << grd.get_grade() << std::endl;
            unsigned char current_credits = get_course_credits(grd.get_course_id());
            credits += current_credits;
            points += get_num_grade(grd.get_grade()) * current_credits;
        }
        outFile << "GPA: " << (points / credits) << std::endl;
        outFile.close();
        std::cout << "File written successfully!" << std::endl;
    }
    
    
}

bool StudentRecords::initialize_from_files(std::string students_file,std::string grades_file,std::string courses_file)
{
    std::ifstream inFile;
    std::string str;

    inFile.open(students_file);
    if (inFile.fail())
        std::cout << std::endl << "File not found!" << std::endl;
    else{
        while (!inFile.eof()){
            getline(inFile, str);
            int student_id = stoi(str);
            std::string student_name_str;
            getline(inFile, student_name_str);
            add_student(student_id,student_name_str);
        }
        inFile.close();
    }

inFile.open(grades_file);
    if (inFile.fail())
        std::cout << std::endl << "File not found!" << std::endl;
    else{
        while (!inFile.eof()){
            getline(inFile, str);
            int student_id = stoi(str);
            getline(inFile, str);
            int cource_id = stoi(str);
            getline(inFile, str);
            char grade=str[0];
            add_grade(student_id,cource_id,grade);
        }
        inFile.close();
    }

inFile.open(courses_file);
    if (inFile.fail())
        std::cout << std::endl << "File not found!" << std::endl;
    else{
        while (!inFile.eof()){
            getline(inFile, str);
            int course_id = stoi(str);
            getline(inFile, str);
            std::string course_name=str;
            getline(inFile, str);
            unsigned char credits = stoi(str);
            add_course(course_id,course_name,credits);
        }
        inFile.close();
    }



    return(true);

}