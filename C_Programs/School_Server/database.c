#include "Headers/database.h"
#include <sqlite3.h>
#include <stdint.h>

classList getClassList(){
    sqlite3 *db;
    char *fileName = "pineforest.db";

    classList list;
    list.classes = NULL;
    list.count = 0;
    uint32_t capacity = 0;

    if (sqlite3_open(fileName, &db) != SQLITE_OK){
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    }
    const char *sql = "SELECT class_id, class_name, teacher_id FROM classes";
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "Prepare sql failed: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    while(sqlite3_step(stmt) == SQLITE_ROW){
        if(list.count == capacity){
            capacity = capacity == 0 ? 8 : capacity * 2;
            list.classes = realloc(list.classes, sizeof(Class) * capacity);
        }

        // class id
        Class *c = &list.classes[list.count];
        c->id = sqlite3_column_int(stmt, 0);

        // class name
        const unsigned char *subject = sqlite3_column_text(stmt, 1);
        c->subject = strdup((const char *)subject);

        int teacherId = sqlite3_column_int(stmt, 2);

        sqlite3_stmt *teacherStmt;
        const char *teacherSql = "SELECT first_name, last_name FROM teachers WHERE teacher_id = ?";
        if(sqlite3_prepare_v2(db, teacherSql, -1, &teacherStmt, NULL) == SQLITE_OK){
            sqlite3_bind_int(teacherStmt, 1, teacherId);

            if(sqlite3_step(teacherStmt)){
                const unsigned char *teachFirst = sqlite3_column_text(teacherStmt, 0);
                const unsigned char *teachLast = sqlite3_column_text(teacherStmt, 1);
    
                c->teacher.firstName = strdup((const char *)teachFirst);
                c->teacher.lastName = strdup((const char *)teachLast);
    
            }
            sqlite3_finalize(teacherStmt);
        }


        c->students = NULL;
        c->studentCount = 0;
        list.count++;
    }
    sqlite3_finalize(stmt);

    const char *enrollmentSql = "SELECT student_id, class_id FROM enrollments";
    sqlite3_stmt *enrollmentStmt;
    if(sqlite3_prepare_v2(db, enrollmentSql, -1, &enrollmentStmt, NULL) != SQLITE_OK){
        fprintf(stderr, "Prepare sql failed: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    while(sqlite3_step(enrollmentStmt) == SQLITE_ROW){
        uint32_t id, classId, age;
        const unsigned char *studentFirst, *studentLast, *gender;
        id = sqlite3_column_int(enrollmentStmt, 0);
        classId = sqlite3_column_int(enrollmentStmt, 1);

        sqlite3_stmt *studentStmt;
        const char *studentSql = "SELECT first_name, last_name, age, gender FROM students WHERE student_id = ?";
        if(sqlite3_prepare_v2(db, studentSql, -1, &studentStmt, NULL) == SQLITE_OK){
            sqlite3_bind_int(studentStmt, 1, id);

            if(sqlite3_step(studentStmt)){
                studentFirst = sqlite3_column_text(studentStmt, 0);
                studentLast = sqlite3_column_text(studentStmt, 1);
                age = sqlite3_column_int(studentStmt, 2);
                gender = sqlite3_column_text(studentStmt, 3);
    
            }
            sqlite3_finalize(studentStmt);
        }


        for(uint32_t i = 0; i < list.count; i++){
            uint32_t studentCapacity = list.classes[i].studentCount;            
            if(classId == list.classes[i].id){
                if(list.classes[i].studentCount == studentCapacity){
                    studentCapacity = studentCapacity == 0 ? 8 : studentCapacity * 2;
                    list.classes[i].students = realloc(list.classes[i].students, sizeof(Student) * studentCapacity);
                }
                Student *student = &list.classes[i].students[list.classes[i].studentCount];

                student->firstName = strdup((const char *)studentFirst);
                student->lastName = strdup((const char *)studentLast);
                student->id = id;
                student->classId = classId;
                student->age = age;
                student->gender = gender[0];
                // student->assignments = NULL;
                list.classes[i].studentCount++;
            }
        }
        // sqlite3_finalize(studentStmt);
        
    }  
    sqlite3_finalize(enrollmentStmt);
    
    sqlite3_close_v2(db);
    return list;
}