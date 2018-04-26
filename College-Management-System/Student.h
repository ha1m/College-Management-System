#ifndef _STUDENT
#define _STUDENT
#include <string>
#include <iostream>
using namespace std;
//����� �� ������ ��� ����� ������� ���������� ������ �� ������
//����� ����� �� ������ ������ �� ��� ������� ���� ������ ���� ������� ������� �����
class Course;
class Department;
class Student{
	string name;
	long id;
	int age;
	char gender;
	Course **course;
	int NumofCourses;
	Department *department;
public:
	Student();
	~Student();
	void Setnofcourse(int n){ NumofCourses = n; }
	int Getnofcourse(){ return NumofCourses; }
	void setname(string NAME){ name = NAME; }
	string getname()const{ return name; }
	void setid(long ID){ id = ID; }
	long getid()const{ return id; }
	void setage(int AGE){ age = AGE; }
	int getage()const{ return age; }
	void setgender(char GENDER){ gender = GENDER; }
	char getgender(){ return gender; }
	Student &operator=(const Student&other);
	bool operator==(const Student&other)const;
	bool operator>(const Student&other)const;
	friend ostream &operator<<(ostream &, const Student &);
	friend istream &operator>>(istream &, Student &);
	Student & operator +=( Course &);
	Student & operator -=(Course &);
	Course * operator [](const int index)const;
};
#endif