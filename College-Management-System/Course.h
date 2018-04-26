#ifndef _COURSE
#define _COURSE
#include "Student.h"
class Department;
//הכרזה על המחלקה ועל כל המשתנים הרלוונטים פרייבט ועל הפונקציות הנדרשות בפאבליק
class Course{
	string nameofcourse;
	int coursecode;
	Student **student;
	int numofstudents;
	int *grade;
	Department *department;
public:
	Course();
	~Course();
	void Setnamec(string nc){ nameofcourse = nc; }
	string getnamec(){ return nameofcourse; }
	void setcodec(int c){ coursecode = c; }
	void setnofstudents(int n){ numofstudents = n; }
	int getnofstudents(){ return numofstudents; }
	//void setgarade(int g){}
	int getcodec(){ return coursecode; }
	Course &operator=(const Course&other);
	bool operator==(const Course&other)const;
	bool operator>(const Course&other)const;
	friend ostream &operator<<(ostream &, const Course &);
	friend istream &operator>>(istream &, Course &);
	Course & operator +=(Student&);
	Course & operator -=(Student&);
	Student * operator [](const int index)const;
	//פונקציה שהוספתי שהיא בעצם מכניסה ציונים לתוך מערך הציונים
	void grade_();
	//פונקציה בוליאנית שהוספתי שתפקידה לוודא שהסטודנט אכן נמצא וקיים בקורס
	bool get_student_id(int);
	//פונקציה שהוספתי המחזירה ציון של סטודנט
	int get_student_grade(Student &s);//הוספתי עכשיו
};
#endif