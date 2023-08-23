/*student.h*/

//
// student class for keeping track of grades.  Uses a dynamically
// allocated character array for storing grades.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class student
{
private:
    string Name;
    int    UIN;
    //char* Grades;   // C-style array of characters
    //int   N;        // # of grades in array
    //int   ArrayCap; // total capacity of array

public:
    //
    // NOTE: Grades is public *only* for grading purposes, normally
    // this would be private.  Likewise for N and ArrayCap.
    //
    char* Grades;   // C-style array of characters
    int   N;        // # of grades in array
    int   ArrayCap; // total capacity of array

    //
    // constructor:
    //
    student(string name, int uin)
    {
        Name = name;
        UIN = uin;

        Grades = new char[4];  // empty array of capacity 4:
        N = 0;
        ArrayCap = 4;
    }

    //
    // copy constructor:
    //
    student(const student& other)
    {
        Name = other.Name;
        UIN = other.UIN;

        ArrayCap = other.ArrayCap;
        N = other.N;

        // Allocate a new character array for Grades
        Grades = new char[ArrayCap];

        // Copy the elements from the other Grades array to this Grades array
        for (int i = 0; i < N; i++) {
            Grades[i] = other.Grades[i];
        }
    }

    //
    // addGrade:
    //
    // Adds another grade to the Grades array, growing dynamically if
    // necessary (by doubling the capacity).
    //
    void addGrade(char grade)
    {
        if (N == ArrayCap)  // array is full, have to double in size
        {
            char* newGrades = new char[ArrayCap * 2];
            for (int i = 0; i < ArrayCap; i++) {
                newGrades[i] = Grades[i];
            }
            delete[] Grades;  // delete old one
            Grades = newGrades;  // point old to new
            ArrayCap = ArrayCap * 2;  // update the capacity
        }

        Grades[N] = grade;  // add the grade to the array
        N++;
    }

    //
    // GPA:
    //
    // returns GPA for this student, based on their grades.  Returns 0.0
    // if the student has no grades.
    //
    double GPA()
    {
        //
        // TODO: loop through the Grades vector and compute the GPA.  Note
        // that if the vector is empty, return 0.0.
        //
        int gradeSum = 0;
        if (N == 0) {
            return 0.0;
        }
        else{
            for (int i = 0; i < N; i++){
                char holder =  Grades[i];
                if (holder == 'A'){
                    gradeSum += 4;
                }
                else if (holder == 'B'){
                    gradeSum += 3;
                }
                else if (holder == 'C'){
                    gradeSum += 2;
                }
                else if (holder == 'D'){
                    gradeSum += 1;
                }
                else if (holder == 'F' || holder == 'W'){ //redundant
                    gradeSum += 0;
                }
            }
        }
        double GPAholder = static_cast<double>(gradeSum) / N;
        return GPAholder;
    }

    //
    // getName
    //
    string getName()
    {
        return Name;
    }

    //
    // getUIN
    //
    int getUIN()
    {
        return UIN;
    }

};

