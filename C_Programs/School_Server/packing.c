#include "Headers/packing.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

char *studentStructPacking(Student *student, uint32_t studentCount, int *studentOffset){
    int offset = 0;

    // We'll do the same thing for when we first looped through the classes to get the subject and teachers names and lengths
    // for id, classId, age, and gender we can just add it directly since we know its only one character
    int bufferSize = (studentCount * (sizeof(student->id)) + (studentCount * sizeof(student->classId)) + 
                     (studentCount * sizeof(student->age)) + (studentCount * sizeof(student->gender)) + 
                     (sizeof(studentCount)));

    // We'll just do it for each student and get theyre firstname, lastname
    for(uint32_t i = 0; i < studentCount; i++){
        Student curr = student[i];
        bufferSize += strlen(curr.firstName); // The amount of charcters 
        bufferSize += sizeof(uint32_t); // the network part

        bufferSize += strlen(curr.lastName); // The amount of characters
        bufferSize += sizeof(uint32_t); // netwrok part
    }

    char *buffer = malloc(bufferSize);

    memcpy(buffer + offset, &studentCount, sizeof(studentCount));
    for(uint32_t i = 0; i < studentCount; i++){
        Student curr = student[i];

        memcpy(buffer + offset, &curr.id, sizeof(curr.id));
        offset += sizeof(curr.id);

        memcpy(buffer + offset, &curr.classId, sizeof(curr.classId));
        offset += sizeof(curr.classId);

        memcpy(buffer + offset, &curr.age, sizeof(curr.age));
        offset += sizeof(curr.age);

        uint32_t firstLen = strlen(curr.firstName);
        uint32_t firstNetLen = htonl(firstLen);

        uint32_t lastLen = strlen(curr.lastName);
        uint32_t lastNetLen = htonl(lastLen);

        memcpy(buffer + offset, &firstNetLen, sizeof(firstNetLen));
        offset += sizeof(firstNetLen);

        memcpy(buffer + offset,  curr.firstName, firstLen);
        offset += sizeof(firstLen);
        
        memcpy(buffer + offset, &lastNetLen, sizeof(lastNetLen));
        offset += sizeof(lastNetLen);

        memcpy(buffer + offset,  curr.lastName,lastLen);
        offset += sizeof(firstLen);

        memcpy(buffer + offset, &curr.gender, sizeof(char));
        offset += sizeof(lastLen);
    }
    *studentOffset = offset;
    return buffer;


}

char *classStructPacking(classList list, ssize_t *requestSize){
    // create an offset so we know where we are in the buffer
    int offset = 0;
    int studentOffset = 0;

    // create the buffersize by adding the size of the count, the classes id,
    // and the studentCount of the student array. Later in th loop for each student we're going to go into another function that
    // will get the size of all the students in the student array
    // This function doesnt create the entire class struct, it only sends the class id and subject name;
    // subject name and the teachers first and last name will be added to buffersize later in the loop becuase we have to get the length of each teacher and subject because theyre length is undefinded
    int bufferSize = (sizeof(list.count) + (list.count * sizeof(list.classes->id)) + (list.count * sizeof(uint32_t)));
    int studentBufferSize;
    char *studentBuffer;;

    for(uint32_t i = 0; i < list.count; i++){
        bufferSize += sizeof(uint32_t); // Size of subject length
        bufferSize += strlen(list.classes[i].subject); //length of subject itself

        bufferSize += sizeof(uint32_t); // Size of teacher first name
        bufferSize += strlen(list.classes[i].teacher.firstName); // length of firstname

        bufferSize += sizeof(uint32_t); // Size of teacher last name
        bufferSize += strlen(list.classes[i].teacher.lastName); // length of last name
    }

    // create space for everything we're going to add to the buffer
    char *buffer = malloc(bufferSize);

    uint32_t count = htonl(list.count);

    // we're sending the count part to the buffer at a offset of 0(basically at the beginng of the memory address)
    memcpy(buffer + offset, &count, sizeof(count));
    offset += sizeof(count);

    for(uint32_t i = 0; i < list.count; i++){
        Class curr = list.classes[i];
        // we have to use a function htonl(host to network) becuase how the network send and recieve is different depending on what your doing
        uint32_t id = htonl(curr.id);
        
        // This is where we're getting the length(how many letters does subject have) NetLen(formatting it so the network can understand it)
        uint32_t subjectLen = strlen(curr.subject);
        uint32_t subjectNetLen = htonl(subjectLen);

        uint32_t teachFirstLen = strlen(curr.teacher.firstName);
        uint32_t teachNetFirstLen = htonl(teachFirstLen);

        uint32_t teachLastLen = strlen(curr.teacher.lastName);
        uint32_t teachNetLastLen = htonl(teachLastLen);
        
        // we're sending the id to the buffer at a offset of however big count was
        memcpy(buffer + offset, &id, sizeof(id));
        offset += sizeof(id);

        // we're sending the subject length to the buffer at a offset of however big id was
        memcpy(buffer + offset, &subjectNetLen, sizeof(subjectNetLen));
        offset += sizeof(subjectNetLen);

        // // we're sending the subject itself to the buffer at a offset of however big the subject length was
        memcpy(buffer + offset, list.classes[i].subject, subjectLen);
        offset += subjectLen;

        memcpy(buffer + offset, &teachNetFirstLen, sizeof(teachNetFirstLen));
        offset += sizeof(teachFirstLen);

        memcpy(buffer + offset, &curr.teacher.firstName, teachFirstLen);
        offset += teachFirstLen;
        
        memcpy(buffer + offset, &teachNetFirstLen, sizeof(teachNetLastLen));
        offset += sizeof(teachLastLen);

        memcpy(buffer + offset, &curr.teacher.lastName, teachLastLen);
        offset += teachLastLen;

        studentBuffer = studentStructPacking(curr.students, curr.studentCount, &studentOffset);
        studentBufferSize += strlen(studentBuffer);
        offset += studentOffset;

    }
    *requestSize = offset;
    int newBufferSize = strlen(buffer) + strlen(studentBuffer) + 1;
    char *newBuffer = malloc(newBufferSize);
    snprintf(newBuffer, newBufferSize, "%s%s", buffer, studentBuffer);

    return newBuffer;
}

char *serverRequest(char *userReq, ssize_t *requestSize){

    if(!strcmp(userReq, "VIEW_CLASSES")){
        classList list = getClassList();

        char *packedList = classStructPacking(list, requestSize);

        for(uint32_t i = 0; i < list.count; i++){
            free(list.classes[i].subject);
        }

        free(list.classes);

        return packedList;
        
    }

    return "SOMETHING WENT HORRIBLY WRONG";
}