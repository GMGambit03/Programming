#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct{
    uint32_t id;
    char grade;
    char *firstName;
    char *lastName;
}Assignment;

typedef struct{
    uint32_t id;
    uint32_t classId;
    uint32_t age;
    char *firstName;
    char *lastName;
    char gender;
    // Assignment *assignments;
}Student;

typedef struct{
    char *firstName;
    char *lastName;
}Teacher;

typedef struct{
    uint32_t id;
    char *subject;
    Teacher teacher;
    uint32_t studentCount;
    Student *students;
}Class;

typedef struct{
    Class *classes;
    uint32_t count;
}classList;

#endif