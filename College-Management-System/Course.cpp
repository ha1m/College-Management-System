#include "Course.h"


Course::Course()
{
	numofstudents = 0;
	grade = new int[1];
}


Course::~Course()
{
	//לבדוק
	if (student)
	 delete[]student;
}
//אופרטור השמה המקבל אובייקט מסוג קורס ומבצע השמה בין המשתנים הרלוונטים
Course & Course::operator =(const Course&other)
{
	nameofcourse = other.nameofcourse;
	coursecode = other.coursecode;
	//student = other.student;
	numofstudents = other.numofstudents;
	grade = other.grade;
	department = other.department;
	if (numofstudents)
	{
		for (int i = 0; i < numofstudents; i++)
		{
			student[i] = other.student[i];
		}
	}
	return *this;
}
//פונקציה בוליאנית המחזירה ערך רלוונטי בבדיקת קוד של קורס
bool Course::operator==(const Course&other)const
{
	return(coursecode == other.coursecode);
}

bool Course::operator>(const Course&other)const/****************/
{
	return(numofstudents > other.numofstudents);
}
//אופרטור פלט שתפקידו להדפיס את פרטי הקורס ואת פרטי הסטודנטים הרשומים לקורס + הציונים שלהם
ostream &operator<<(ostream &os, const Course &c)
{
	float cnt = 0;
	float avg=0;
	//הדפסת פרטי הקורס
	cout << "Course deatailes:\n";
	os <<"Course name: "<< c.nameofcourse << endl << "Course code: " << c.coursecode << endl;
	// הדפסת פרטי הסטודנטים הרשומים לקורס + הציונים שלהם בקורס
	cout << "Students regestied to course:\n";
	for (int i = 0; i < c.numofstudents; i++)
	{
		cout << "Name: ";
		os << c.student[i]->getname() << endl;
		cout << "Id: ";
		os << c.student[i]->getid() << endl;
		cout << "Age: ";
		os << c.student[i]->getage() << endl;
		cout << "Gender: ";
		os << c.student[i]->getgender() << endl;
		cout << "Grade: ";
		//במידה וישנו ציון מתאים יש הדפסה של הציון
		if (c.grade[i] > 0 && c.grade[i] < 101)
		{
			os << c.grade[i] << endl;
			//ספירה של כמות הסטודנטים שיש להם ציון
			cnt++;
			//סכימה של כל הציונים
			avg += c.grade[i];
		}
		cout << endl;
	}
	//במידה ולכל הסטודנטים יש ציון מתבצעת הדפסה של מומצע הציונים של הק'ורס
	if (cnt == c.numofstudents)
		os << "Averge of course grade: " << avg / cnt << endl << endl;
	//*************
	return os;
}
//אופרטור קלט שתפקידו כמובן לקלוט פרטי קורס
istream &operator>>(istream &io, Course &c)
{
	//flushall;
	cout << "Enter name of course:\n";
	getline(io, c.nameofcourse);
	cout << "Enter code course:\n";
	io >> c.coursecode;
	return io;
}
//אופטור פלוס שווה שמקבל אובייקט מסוג סטודנט ותפקידו להוסיך את הסטודנט לקורס
Course & Course::operator+=(Student& other)
{
//במידה וזהו הסטודנט הראשון מתבצעת הוספה של הסטודנט לתא הראשון בצורה מתאימה ומעודכנת הכמות של הסטודנטים
	if (!numofstudents)
	{
		student = new Student*[1];
		student[0] = &other;
		numofstudents += 1;
		cout << "num of students: " << numofstudents << endl;
		return *this;
	}
	//במידה וזהו לא הסטודנט הראשון נוצר מערך חדש מסוג סטודנט שמוקצה לו זיכרון בגודל מתאים(פלוס תא נוסף) ומתבצעת העתקה של המערך המקורי לתוך המערך החדש
	//כאשר בתא האחרון במערך החדש נוסף הסטודנט החדש
	//לאחר מכן מתבצעת מחיקה של המערך המקורי ואז המערך המקורי מצביע למערך החדש
	//כמות הסטודנטים מתעדכנת בהתאם
	Student **help = new Student *[numofstudents + 1];
	for (int i = 0; i < numofstudents; i++)
	{
		help[i] = student[i];
	}
//	for (int i = 0; i < numofstudents; i++)
	//{
		//delete student[i];
	//}
	delete[]student;
	help[numofstudents] = &other;
	student = help;
	numofstudents += 1;
	cout << "num of students: " << numofstudents << endl;
	return *this;
}

//אופרטור מינוס שווה שתפקידו למחוק סטודנט מקורס
Course & Course::operator-=(Student & other)
{
	int box = numofstudents;
	int k = 0;
//במידה ויש לנו רק סטודנט אחד מתבצעת מחיקה שלו בהתאם ומעודכנת הכמות של הסטודנטים
		if (numofstudents == 1)
		{
			delete[]this->student;
			student = NULL;
			numofstudents=0;
			return *this;
		}
//במידה ויש לנו יותר מסטודנט אחד מתבצע חיפוש אחר הסטודנט המתאים שאותו רוצים למחוק
		//נוצר מערך חדש שמוקצה לו גודל מתאים(פחות תא אחד) לתוכו מועתקים כל הסטודנטים הרלוונטים חוץ מהסטודנט שביקשו למחוק
		//כך שנוצר מערך חדש ללא הסטודנט שהתבקשנו למחוק
		//מתבצעת מחיקה של המערך המקורי ובסימו הוא מצביע על המערך החדש
		//מתבצע עדכון לכמות הסטודנטים בהתאם
		for (int i = 0; i < numofstudents; i++)
		{
			if (student[i] == &other)
			{
				Student **help = new Student *[numofstudents - 1];
				for (int j = 0; j < numofstudents; j++)
				{
					if (j == i && i != numofstudents - 1)
					{
						k++;
						numofstudents--;
						i = EOF;
					}
					if (i == numofstudents - 1)
					{
						numofstudents--;
						i = 0;
					}
						
					help[j] = student[k++];
				}
			//	for (int i = 0; i < numofstudents; i++)
			//	{
				//	delete student[i];
			//	}
				delete[]student;
				student = help;
				if (box != numofstudents)
					break;
				//numofstudents -= 1;
				//break;
			}
		}
		cout << "Students: " << numofstudents << endl;

	
}
//אופרטור אינדקס מחזירה את הסטודנט באינדקס המתבקש
Student * Course::operator[](const int index)const
{
	if (index >= 0 && index <numofstudents)
		return student[index];
}
//פונקציה שדרכה אנחנו קולטים ציונים לתוך מערך הציונים של הסטודנט
void Course::grade_()
{
	int Grade = 0;
	//הקצאה למערך הציונים בגודל של כמות הסטודנטים
	grade = new int[numofstudents];
	//הכנסת ציונים לסטודנטים הרשומים לקורס
	cout << "Enter grade for foloowing student (ids)\n";
	for (int i = 0; i < numofstudents; i++)
	{
		cout << student[i]->getid()<<": ";
		cin >> Grade;
		grade[i] = Grade;
		cout << endl;
	}

}
//פונקציה בוליאנית שתפקידה לקבל תעודת זהות של סטודנט ולבדוק שהוא אכן קיים ברשימה של הסטודנטים בקורס
bool Course::get_student_id(int id)
{
	for (int i = 0; i < numofstudents; i++)
	{
		if (id == student[i]->getid())
			return true;
	}
	return false;
}
//פונקציה המקבלת אובייקט מסוג סטודנט מבררת מה האינדקס שלו ברשימה של הסטודנטים ומחזירה את הציון שלו
int Course::get_student_grade(Student &s)
{
	int index=EOF;
	for (int i = 0; i < numofstudents; i++)
	{
		if (s.getid() == student[i]->getid())
			index = i;
	}
	if (index != EOF)
		return grade[index];
}