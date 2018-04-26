#include "Student.h"
#include "Course.h"

Student::Student()
{
	NumofCourses = 0;
}



Student::~Student()
{
	if (course)
		delete[]course;
}

//אופרטור השמה. מקבל אובייקט מסוג סטודנט ומבצע השמה לכל המשתנים הרלוונטים
Student & Student::operator =(const Student&other)
{
	name = other.name;
	id = other.id;
	age = other.age;
	gender = other.gender;
	//course = other.course;
	NumofCourses = other.NumofCourses;
	department = other.department;
	if (NumofCourses)
	{
		//course = new Course*[NumofCourses];
		for (int i = 0; i < NumofCourses; i++)
		{
			course[i] = other.course[i];
		}
			
	}


	return *this;
}
//פונקציה בוליאנית מסוג אופרטור שיווין מחזירה ערך מתאים על פי בדיקת ת.ז המתקבל על ידי אובייקט מסוג סטודנט
bool Student::operator==(const Student&other)const
{
	return(id == other.id);
}
//אופרטור פלט המדפיס את פרטי הסטודנט ואת פרטי הקורסים עליהם רשום הסטודנט
ostream &operator<<(ostream &os, const Student &s)
{
	//הדפסת פרטי הסטודנט
	cout << "Student deatailes:\n";
	os <<"Name: "<< s.name << endl << "id: " << s.id << endl << "age: " << s.age << endl << "gender: " << s.gender << endl;
	cout << "Student courses:\n";
	//הדפסת פרטי הקורסים עליהם הסטודנט רשום
	for (int i = 0; i < s.NumofCourses; i++)
	{
		cout << "Course name:\n";
		os << s.course[i]->getnamec() << endl;
		cout << "Course code\n";
		os << s.course[i]->getcodec() << endl;
		cout << endl; 
	}
	return os;
}
//אופרטור קלט המבקש את פרטיו של הסטודנט וקולט לתוך אובייקט מסוג סטודנט
istream &operator>>(istream &io, Student &s)
{
	cout << "Enter name:\n";
	getline(io, s.name);
	cout << "Enter id:\n";
	io >> s.id;
	cout << "Enter age:\n";
	io >> s.age;
	do
	{
		cout << "Enter gender M/F:\n";
		io >> s.gender;
	} while (s.gender != 'M' && s.gender != 'm' && s.gender != 'F' && s.gender != 'f');

	return io;
}
//אופרטור פלוס שווה שתפקידו לקבל אובייקט מסוג קורס ולהוסיף אותו לרשימת הקורסים של הסטודנט עליהם הוא רשום
Student & Student::operator+=(Course & other)
{
//בדיקה אם זה הקורס הראשון שנוסף לרשימה ובמידה וכן הוספה בצורה מתאימה	
	if (!NumofCourses)
	{
		course = new Course*[1];
		course[0] = &other;
		NumofCourses += 1;
		return *this;
	}
	//במידה וזהו לא הקורס הראשון שנוסף לרשימה, מתבצעת העתקה של כל הקורסים לתוך מערך חדש כאשר למערך החדש מוקצה גודל מתאים (פלוס תא נוסף)על מנת להכניס
	//בתא הנוסף שהוא האחרון את הקורס המתקבל כאובייקט
	//לאחר מכן מתבצעת מחיקה של המערך המקורי ואז המערך המקורי מצביע על המערך החדש
	//מתבצע עדכון למספר הקורסים
	Course **help = new Course *[NumofCourses + 1];
	for (int i = 0; i < NumofCourses; i++)
	{
		help[i] = course[i];
	}
	delete[]course;
	help[NumofCourses] = &other;
	course = help;
	NumofCourses += 1;
	return *this;
}
//אופרטור מינוס שווה המקבל אובייקט מסוג קורס ותפקידו למחוק את הקורס מרשימת הקורסים של הסטודנט
Student & Student::operator-=(Course & other)
{
	
	int box = NumofCourses;
	int k = 0;
//במידה ויש לנו רק קורס אחד ברשימה מתבצעת מחיקה שלו ועדכון כמות הקורסים
	if (NumofCourses == 1)
	{
		delete[]this->course;
		course = NULL;
		NumofCourses = 0;
		return *this;
	}
	//במידה ויש יותר מקורס אחד, מתבצע חיפוש אחר הקורס הספציפי שעלינו למחוק
	//נוצר מערך חדש בגודל מתאים(פחות תא אחד) ומתבצעת העתקה של כל הקורסים לתוך המערך החדש חוץ מהקורס שאותו צריך למחוק
	//כך שנוצר מערך חדש עם הקורסים הרלוונטים. לאחר מכן מתבצעת מחיקה של המערך המקורי כאשר בסוף המערך המקורי מצביע למערך החדש
	//ויש עדכון לכמות הקורסים 
	for (int i = 0; i < NumofCourses; i++)
	{
		if (course[i] == &other)
		{
			Course **help = new Course *[NumofCourses - 1];
			for (int j = 0; j < NumofCourses; j++)
			{
				if (j == i && i != NumofCourses - 1)
				{
					k++;
					NumofCourses--;
					i = EOF;
				}
				if (i == NumofCourses - 1)
				{
					NumofCourses--;
					i = 0;

				}
				help[j] = course[k++];
			}
			delete[]course;
			course = help;
			if (box != NumofCourses)
				break;
		}
	}

}

//אופרטור אינדקס מקבל אינדדקס ומחזיר את הקורס באינדקס המתבקש
Course * Student::operator[](const int index)const
{
	if (index >=  0 && index <NumofCourses)
	return course[index];
}