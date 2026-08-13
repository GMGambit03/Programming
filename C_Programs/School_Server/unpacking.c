#include "Headers/unpacking.h"
#include <netinet/in.h>
#include <stdint.h>

void studentStructunPacking(Student **students, char *userRecv, int *offset, uint32_t studentCount){
    // We first have to make space for all the students
    *students = malloc(studentCount * sizeof(Student));
    // For unpacking we can just go straight into a for loop using the studentCount

    for(uint32_t i = 0; i < studentCount; i++){
        Student *curr = &(*students)[i];

        // first get the student id
        memcpy(&curr->id, userRecv + *offset, sizeof(uint32_t));
        curr->id = ntohl(curr->id);
        *offset += sizeof(uint32_t);

        // Get student classId
        memcpy(&curr->classId, userRecv + *offset, sizeof(uint32_t));
        curr->classId = ntohl(curr->classId);
        *offset += sizeof(uint32_t);

        // Get student age
        memcpy(&curr->age, userRecv + *offset, sizeof(uint32_t));
        curr->age = ntohl(curr->age);
        *offset += sizeof(uint32_t);

        // get student firstName size
        uint32_t firstLen;
        memcpy(&firstLen, userRecv + *offset, sizeof(uint32_t));
        firstLen = ntohl(firstLen);
        *offset += sizeof(firstLen);

        // make space for the first name;
        curr->firstName = malloc(firstLen + 1);

        // get student firstName
        memcpy(curr->firstName, userRecv + *offset, firstLen);
        *offset += firstLen;
        curr->firstName[firstLen] = '\0';   

        // get student lastName size
        uint32_t lastLen;
        memcpy(&lastLen, userRecv + *offset, sizeof(uint32_t));
        lastLen = ntohl(lastLen);
        *offset += sizeof(lastLen);

        // Make space for last name
        curr->lastName = malloc(lastLen + 1);

        // get student lastName
        memcpy(curr->lastName, userRecv + *offset, lastLen);
        *offset += lastLen;
        curr->lastName[lastLen] = '\0';   

        // get student gender
        memcpy(&curr->gender, userRecv + *offset, sizeof(curr->gender));
        *offset += sizeof(curr->gender);
    }
}

classList classStructUnpacking(char *userRecv){
    int offset = 0;
    printf("Unpacking\n");

    classList list;

    // We start unpacking everything by first we creating the thing we're going to unpack it to. IE the thing above us first the count
    memcpy(&list.count, userRecv + offset, sizeof(uint32_t));
    printf("Unpacking: listcount\n");

    // We have to cast network to host to basicaly allow the computer we send it to read what is recieved
    list.count = ntohl(list.count);
    offset += sizeof(uint32_t);

    // Create space so we can unpack our infromation into our new list
    list.classes = malloc((sizeof(Class)) * list.count);

    // Now tha we got the count we have to populate each class using a for loop
    // This where we're going to do the subject, and class_id
    for(uint32_t i = 0; i < list.count; i++){
        printf("Offset: %d\n", offset);
        printf("user recieved data: %zd\n", strlen(userRecv));

        Class *curr = &list.classes[i];
        
        memcpy(&curr->id, userRecv + offset, sizeof(uint32_t));
        curr->id = ntohl(curr->id);
        offset += sizeof(uint32_t);
        printf("Unpacking: Id\n");

        // We next get the sizeof of the subject first
        uint32_t sizeofSubject;
        memcpy(&sizeofSubject, userRecv + offset, sizeof(uint32_t));
        sizeofSubject = ntohl(sizeofSubject);
        offset += sizeof(uint32_t);
        printf("Unpacking: subject\n");

        curr->subject = malloc(sizeofSubject + 1);
        // After we can use that to get the subject itself
        memcpy(curr->subject, userRecv + offset, sizeofSubject);
        offset += sizeofSubject;
        curr->subject[sizeofSubject] = '\0';

        // Next we get the teachers information
        // First sizeof first and last name
        uint32_t firTeachLen;
        uint32_t lstTeachLen;

        // Copy the size over tio our varaibles and make it so the host machine can understand
        memcpy(&firTeachLen, userRecv + offset, sizeof(firTeachLen));
        firTeachLen = ntohl(firTeachLen);
        offset += sizeof(firTeachLen);

        // Make space for our teacher first name
        curr->teacher.firstName = malloc(firTeachLen + 1);

        memcpy(curr->teacher.firstName, userRecv + offset, firTeachLen);
        offset += firTeachLen;
        curr->teacher.firstName[firTeachLen] = '\0'; 
        printf("Unpacking: Teacher names\n");

        // Copy the size over to our varaibles and make it so the host machine can understand
        memcpy(&lstTeachLen, userRecv + offset, sizeof(lstTeachLen));
        lstTeachLen = ntohl(lstTeachLen);
        offset += sizeof(lstTeachLen);

        //make space for our teachers last name
        curr->teacher.lastName = malloc(lstTeachLen + 1);

        memcpy(curr->teacher.lastName, userRecv + offset, lstTeachLen);
        offset += lstTeachLen;
        curr->teacher.lastName[lstTeachLen] = '\0';   
        printf("Unpacking: Teacher names\n");

        // Next we have to get the studentCount and all the students info
        memcpy(&curr->studentCount, userRecv + offset, sizeof(uint32_t));
        curr->studentCount = ntohl(curr->studentCount);
        offset += sizeof(uint32_t);

        // Get student info, we;ll send a pointer of offset to keep track what dat we have 
        // A copy of the data the server sent
        // and the point to the of students
        printf("Unpacking: student\n");
        studentStructunPacking(&curr->students, userRecv, &offset, curr->studentCount);
    }
    
    return list;

}

void clientRecieve(char *userRecv, char *userReq){

    if(!strcmp(userReq, "VIEW_CLASSES")){
        classList list = classStructUnpacking(userRecv);

        for(uint32_t i = 0; i < list.count; i++){
            Class curr = list.classes[i];
            printf("Class Id: %d Subject: %s Teacher First: %s, Teacher Last: %s, StudentCount: %d\n", curr.id, curr.subject, curr.teacher.firstName, curr.teacher.lastName, curr.studentCount);
            for(uint32_t j = 0; j < curr.studentCount; j++){
                Student currStudent = curr.students[j];
                printf("student ID: %d, class id: %d, age: %d, first: %s, last: %s, gender: %c\n", currStudent.id,  currStudent.classId,  currStudent.age,  currStudent.firstName,  currStudent.lastName,  currStudent.gender);
            }
            free(list.classes[i].subject);
        }

        free(list.classes);
        getchar();

        
    }
    return;
}