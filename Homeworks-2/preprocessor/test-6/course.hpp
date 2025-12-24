#pragma once

#include <vector>
#include "student.hpp"

class Student;

class Course {
private:
        std::vector<Student*> students;
};