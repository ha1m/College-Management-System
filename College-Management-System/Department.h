#ifndef _DEPARTMENT
#define _DEPARTMENT
#include "Course.h"
#include "Student.h"
//הכרזה על המחלקה ועל כל משתני הפרייבט והפונקציות פאבליק
class Department{
	string NameD;
	int CodeD;
	Course **courseD;
	int amount_Course_D;
	Student **studentD;
	int amount_Student_D;
	Student **Bad_ac_student;
	int amount_bad_student;
public:
	Department();
	~Department();
	void set_NameD(string n){ NameD = n; }
	string get_NameD(){ return NameD; }
	void set_CodeD(int code){ CodeD = code; }
	int get_CodeD(){ return CodeD; }
	void set_amount_CourseD(int amount){ amount_Course_D = amount; }
	int get_a_courseD(){ return amount_Course_D; }
	void set_amount_s_D(int amount){ amount_Student_D = amount; }
	int get_a_studentD(){ return amount_Student_D; }
	void set_amount_bad(int amount){ amount_bad_student = amount; }
	int get_a_badStudent(){ return amount_bad_student; }
	Department &operator=(const Department&other);
	bool operator>(const Department&other)const;
	friend ostream &operator<<(ostream &, const Department &);
	friend istream &operator>>(istream &, Department &);
	Department & operator +=(Course &);
	Department & operator +=(Student &);
	//פונקציה שהוספתי תפקיד לבדוק האם הקורס נמצא במחלקה
	bool check_course_code(int)const;
	//פונקציה שהוספתי תפקידה לבדוק האם הסטודנט נמצא במחלקה
	bool check_student_id(int)const;
	//פונקציה שממלאת את המערך של סטודנטים במצב אקדמי לא תקין
	int Fill_Bad_List(Student &);

};
#endif // !_DEPARTMENT
