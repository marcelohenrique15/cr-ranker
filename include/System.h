#pragma once

#include <iostream>
#include <vector>
#include <cstdio>   
#include <memory>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <algorithm> 
#include <cctype>    


#include "BST.h"
#include "Hashtable.h"
#include "Queue.h"
#include "Student.h"
#include "Subject.h"

class AcademicSystem
{
    private:
        BST students;
        std::vector<Student> studentsList;
        std::vector<Subject*> subjectsList;
        Hashtable subjects;

        Queue<Student> approvedStudents;

        void merge(std::vector<Student>& arr, int left, int mid, int right);
        void mergeSort(std::vector<Student>& arr, int left, int right);

    public:
        AcademicSystem();

        void menu();
        void registerStudent();
        void showStudents();
        void registerSubject();
        void showSubjects();
        void sort(std::vector<Student>& arr);
        void showApprovedStudents();
        void proccessRanking();
};