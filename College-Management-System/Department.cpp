#include "Department.h"
#include "Course.h"

Department::Department()
{
	amount_bad_student = 0;
	amount_Course_D = 0;
	amount_Student_D = 0;
}

Department::~Department()
{
	if (studentD)
		delete[]studentD;
	if (courseD)
		delete[]courseD;
	if (Bad_ac_student)
		delete[]Bad_ac_student;
	
}
//אופרטור השמה מצבע השמה של האובייקט המתקבל בין המשתנים הרלוונטים
Department & Department::operator=(const Department&other)
{
	amount_bad_student = other.amount_bad_student;
	amount_Course_D = other.amount_Course_D;
	amount_Student_D = other.amount_Student_D;
	if (amount_bad_student)
	{
		for (int i = 0; i < amount_bad_student; i++)
			Bad_ac_student[i] = other.Bad_ac_student[i];
	}
	if (amount_Course_D)
	{
		for (int i = 0; i < amount_Course_D; i++)
			courseD[i] = other.courseD[i];
	}
	if (amount_Student_D)
	{
		for (int i = 0; i < amount_Student_D; i++)
			studentD[i] = other.studentD[i];
	}
	return *this;
}
//אופרטור פלט המדפיס את פרטי המחלקה, פרטי הקורסים הנמצאים במחלקה, רשימת הסטודנטים הרשומים במחלקה, ורשימת סטודנטים במצב לא תקין
ostream &operator<<(ostream &os, const Department &d)
{
	//פרטי מחלקה
	cout << "Department deatails:\n";
	os << "Name: " << d.NameD << endl;
	os << "Code: " << d.CodeD << endl << endl;
	//פרטי קורסים הנמצאים במחלקה
	cout << "List of Department courses:\n";
	for (int i = 0; i < d.amount_Course_D; i++)
	{
		os << "Course Name : " << d.courseD[i]->getnamec() << endl;
		os << "Course code: " << d.courseD[i]->getcodec() << endl;
		cout << endl;
	}
	//פרטי סטודנטים הרשומים במחלקה
	cout << "List of Students in the Department:\n";
	for (int i = 0; i < d.amount_Student_D; i++)
	{
		os << "Name : " << d.studentD[i]->getname() << endl;
		os << "Id: " << d.studentD[i]->getid() << endl;
		os << "Age: "<< d.studentD[i]->getage() << endl;
		os << "Gender: "<< d.studentD[i]->getgender() << endl;
		cout << endl;
	}
	//פרטי סטודניטים במצב לא תקין במחלקה
	cout << "List of bad academic Students in the Department:\n";
	for (int i = 0; i < d.amount_bad_student; i++)
	{
		os << "Name : " << d.Bad_ac_student[i]->getname() << endl;
		os << "Id: " << d.Bad_ac_student[i]->getid() << endl;
		os << "Age: " << d.Bad_ac_student[i]->getage() << endl;
		os << "Gender: " << d.Bad_ac_student[i]->getgender() << endl;
		cout << endl;
	}
	return os;
}
//רופטור קלט הקולט שם וקוד מחלקה
istream &operator>>(istream &io, Department & d)
{
	cout << "Enter name of Department:\n";
	getline(io, d.NameD);
	cout << "Enter code Department:\n";
	io >> d.CodeD;
	return io;
}

//פונקציה בוליאנית שתפקידה לקבל קוד של קורס ולבדוק שהוא אכן נמצא ברשימה של הקורסים במחלקה

bool Department::check_course_code(int code_course)const
{
	for (int i = 0; i < amount_Course_D; i++)
	{
		if (code_course == courseD[i]->getcodec())
			return true;
	}
	return false;
}

//פונקציה בוליאנית שתפקידה לקבל תעודת זהות ולבדוק שאכן הסטודנט נמצא ברשימתה סטודנטים של המחלקה
bool Department::check_student_id(int id)const
{
	for (int i = 0; i < amount_Student_D; i++)
	{
		if (id == studentD[i]->getid())
			return true;
	}
	return false;
}
// אופרטור פלוס שווה המוסיף קורס למחלקה
Department & Department::operator+=(Course &other)
{
//אם זהו הקורס הראשון שנוסף מתבצעת הוספה של הקורס לתא הראשון במערך והקצאה מתאימה ועדכון כמות הקורסים
	if (!amount_Course_D)
	{
		courseD = new Course*[1];
		courseD[0] = &other;
		amount_Course_D += 1;
		return *this;
	}
	//במידה וזהו לא הקורס הראשון נוצר מערך חדש מסוג קורס אליו מועתק המערך המקורי
	//למערך החדש מוקצה גודל מתאים(פלוס תא אחד) שבתא האחרון מתבצעת השמה של הקורס המתקבל כאובייקאט
	//מתבצעת מחיקה של המערך המקורי ולאחר מכן המערך המקורי מצביע למערך החדש
	//מתבצע עדכון בהתאם לכמות הקורסים במחלקה
	Course **help = new Course *[amount_Course_D + 1];
	for (int i = 0; i < amount_Course_D; i++)
	{
		help[i] = courseD[i];
	}
	delete[]courseD;
	help[amount_Course_D] = &other;
	courseD = help;
	amount_Course_D += 1;
	return *this;
}

//אופרטור פלוס שווה שתפקידו לקבל אוביקט סטודנט ולהוסיף למחלקה
Department & Department::operator+=(Student &other)
{

//במידה וזהו סטודנט ראשון מתבצעת הוספה שלו לתא הראשון במערך
	//מתבצע גם עדכון כמות הסטודנטים
	if (!amount_Student_D)
	{
		studentD = new Student*[1];
		studentD[0] = &other;
		amount_Student_D += 1;
		return *this;
	}
	//במידה וזהו לא הסטודנט הראשון נוצר מערך חדש בגודל מתאים(פלוס תא אחד) אליו מועתק המערך המקורי
	//בתא האחרון של המערך החדש מתבצע הוספה של הסטודנט החדש
	//מתבצעת מחיקה של המערך המקורי שבסופו המערך המקורי מצביע למערך החדש
	//מתבצע עדכון לכמות הסטודנטים הרשומים במחלקה
	Student **help = new Student *[amount_Student_D + 1];
	for (int i = 0; i < amount_Student_D; i++)
	{
		help[i] = studentD[i];
	}
	delete[]studentD;
	help[amount_Student_D] = &other;
	studentD = help;
	amount_Student_D += 1;
	return *this;
}
//פונקציה שתפקידה למלאות את המערך של סטודנטים במצב לא תקין במחלקה
//הפונקציה מקבל אובייט מסוג סטודנט ובעצם בודקת את הציון שלו
//במידה והציון שלו מתחת ל65 הוא נוסף לתוך מערך הסטודנטים שבמצב לא תקין
int Department::Fill_Bad_List(Student &s)
{
	for (int i = 0; i < amount_Course_D; i++)
	{
		if (courseD[i]->get_student_grade(s) < 65)
		{
			//אם זהו סטודנט ראשון הוא נוסף לתא הראשון במערך
			//כמו יש יעדכון של כמות הסטודנטים במצב לא תקין
			if (!amount_bad_student)
			{
				Bad_ac_student = new Student*[1];
				Bad_ac_student[0] = &s;
				amount_bad_student += 1;
				break;
			}
			else
			{
				//אחרת נוצר מערך חדש עם גודל מתאים שאליו מועתק המערך המקורי ונוסף לתא האחרון הסטודנט במצב לא תקין
				//מחיקה של המערך המקורי
				//הצבעה של המערך המקורי למערך החדש
				//עדכון כמות הסטודנטים במצב לא תקין
				Student **newBad = new Student*[amount_bad_student + 1];
				for (int i = 0; i < amount_bad_student; i++)
					newBad[i] = Bad_ac_student[i];
				delete[]Bad_ac_student;
				newBad[amount_bad_student] = &s;
				Bad_ac_student = newBad;
				amount_bad_student += 1;
				break;
			}
		}
	}
	return 1;
}