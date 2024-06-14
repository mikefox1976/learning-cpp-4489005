// Learning C++ 
// Challenge 06_03
// Upgrade to work with files, by Eduardo Corpeño 

#include <iostream>
#include <vector>
#include "records.h"


int main(){
    int id;
    StudentRecords SR;
    
    SR.initialize_from_files("students.txt","grades.txt","courses.txt");

    std::cout << "Enter a student ID: " << std::flush;
    std::cin >> id;

    SR.report_card_to_file(id,"report.txt");
    
    std::cout << std::endl << std::endl;
    return (0);
}