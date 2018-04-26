#include "College.h"
static int print_i_d = 0;
College::College()
{
	amount_allS = 0;
	amount_D = 0;
}

College::~College()
{
	if (listD)
		delete[]listD;
	if (All_Students)
		delete[]All_Students;
}
//מוסיף מחלקה לקולג'
College & College::operator+=(Department & d)
{
	if (!amount_D)
	{
		listD = new Department*[1];
		listD[0] = &d;
		amount_D += 1;
		return *this;
	}
	Department **help = new Department *[amount_D + 1];
	for (int i = 0; i < amount_D; i++)
	{
		help[i] = listD[i];
	}
	delete[]listD;
	help[amount_D] = &d;
	listD = help;
	amount_D += 1;
	return *this;
}
//פונקציה המקבלת קוד ומצביע למחלקה
//בודקת בעצם באיזה אינדקס נמצאת המחלקה המתבקשת ומעדכנת משתנה סטטי אל האינדקס המתבקש
bool College::Department_exsit(int code, Department *d)
{
	for (int i = 0; i < amount_D; i++)
	{
		if (code == d[i].get_CodeD())
		{
			print_i_d = i;
			return true;
		}
			
	}
	return false;
}

//פונקציה המקבלת קוד מחלקה, מצביע למחלקה, וקוד של קורס
//בודקת אם קורס מסוים נמצא במחלקה ספציפית
bool College::Course_exsit_in_Department(int code_d, Department *d, int code_c)
{
	int x=0;
	for (int i = 0; i < amount_D; i++)
	{
		if (code_d == d[i].get_CodeD())
		{
			x = i;
			break;
		}
	}
	if (d[x].check_course_code(code_c))
		return true;

	return false;
}

//פונקציה המקבלת קוד מחלקה, מצביע למחלקה, ותעודת זהות
//הפונקציה בודקת האם סטודנט מסוים קיים בתוך מחלקה ספציפית
bool College::Student_exsit_in_Department(int code_d, Department *d, int id)
{
	int x=0;
	for (int i = 0; i < amount_D; i++)
	{
		if (code_d == d[i].get_CodeD())
		{
			x = i;
			break;
		}
	}
	if (d[x].check_student_id(id))
		return true;

	return false;
}
//פונקציה הסוכמת את כל הקורסים הקיימים
int College::amount_of_all_courses(Department *d)
{
	int cnt = 0;
	for (int i = 0; i < amount_D; i++)
	{
		cnt += d[i].get_a_courseD();
	}
	return cnt;
}

//פונקציה המפעילה את כל ה אפשרויות המוצגות למשתמש
void College::menu()
{
	//הכרזה על משתנים נחוצים
	int choice, i = 1, k = 1, index = 0, code, in = 0, dep_not_exsit = 0;// exsit = 0;
	Department *d1 = new Department[80];
	Course c1, *temp = new Course[80];
	Student *s1 = new Student [80], s2;
	College c;
	//לולאת דו וייל המתבצעת עד לבחירת יציאה של המשתמש
	do
	{
		cout << "Please enter your choice:\n";
		cout << " 1 - Add Department\n";
		cout << " 2 - Add course to department\n";
		cout << " 3 - Add student to department\n";
		cout << " 4 - Register student to course\n";
		cout << " 5 - Grading students in course\n";
		cout << " 6 - Print course information\n";
		cout << " 7 - Print student information\n";
		cout << " 8 - Print department information\n";
		cout << " 9 - Find students with bad academic status\n";
		cout << "10 - Remove student from course\n";
		cout << "11 - Exit\n";
		cin >> choice;
		switch (choice)
		{
			//קליטה של מחלקה
		case 1:
		{
			//קליטה של מחלקה
			getchar();
			cin >> d1[in];
			//בדיקה שהמחלקה אכן לא קיימת
			for (int i = 0; i < in; i++)
			{
				if (d1[in].get_CodeD() != d1[i].get_CodeD())
					dep_not_exsit = i + 1;
			}
			//במידה והמחלקה לא קיימת היא נוספת לקולג
			//עדכון כמות המחלקות
			if (!(amount_D) || dep_not_exsit)
			{

				c += d1[in];
				amount_D++;
				//cout << d1[in];
				in++;
				//delete[]temp;
			}
			//אחרת מודפסת הודעה בהתאם
			else
			{
				cout << "Department already exsit!\n";
			}
		}
			break;
			//הוספת קורס למחלקה ספציפית
		case 2:
		{
			//קליטת קוד מחלקה ובדיקה שהיא אכן קיימת
			cout << "Enter Department Code:\n";
			cin >> code;
			for (int i = 0; i < amount_D; i++)
			{
				if (code == d1[i].get_CodeD())
					index = i + 1;
			}
			//במידה והיא קיימת מתבצעת קליטה לאובייקט מסוג קורס
			//מתבצעת בדיקה שהקורס לא קיים
			//במידה והוא לא קיים מתבצעת הוספה של הקורס למחלקה המתבקשת
			if (index)
			{
				int exsit = 0;
				getchar();
				cin >> temp[i - 1];
				for (int j = 0; j < d1[index - 1].get_a_courseD(); j++)
				{
					if (i - 1)
					{
						if (i - 1 == j)
							continue;
						if (temp[i - 1].getcodec() == temp[j].getcodec())
							exsit = 1;
					}
				}
				if (!(exsit))
				{
					d1[index - 1] += temp[i - 1];
					i++;
					//cout << d1[index - 1];
					//delete[]temp;
				}
				else cout << "Course already exsit!!\n";
			}
			else
			{
				cout << "Department does not exsit!\n";
			}
		}
			break;
			//הוספת סטודנט למחלקה ספציפית
		case 3:
		{
			//בקשת קוד מחלקה ובדיקה שהיא אכן קיימת
			cout << "Enter Department Code:\n";
			int index2 = 0;
			cin >> code;
			for (int i = 0; i < amount_D; i++)
			{
				if (code == d1[i].get_CodeD())
					index2 = i + 1;
			}
			//במידה והיא קיימת מתבצע קלט לאובייקט מסוג סטודנט
			//מתבצעת בדיקה שהסטודנט אכן לא קיים במערכת
			//במידה והוא לא קיים מתבצעת הוספת של סטודנט למחלקה המתבקשת
			//במידה וקיים מודפסת הודעה בהתאם
			if (index2)
			{
				int exsit1 = 0;
				getchar();
				cin >> s1[k - 1];
				for (int j = 0; j < d1[index2 - 1].get_a_studentD(); j++)
				{
					if (k - 1)
					{
						if (k - 1 == j)
							continue;
						if (s1[k - 1].getid() == s1[j].getid())
							exsit1 = 1;
					}
				}
				if (!(exsit1))
				{
					d1[index2 - 1] += s1[k - 1];
					//delete[]s1;
					//cout << d1[index2 - 1];
					k++;
					amount_allS++;
				}
				else cout << "Student already exsit!!\n";
			}
			else
			{
				cout << "Department does not exsit!\n";
			}
		}
			break;
			//רישום סטודנט לקורס ספציפי
		case 4:
		{
			//בקשת קוד מחלקה , קוד קורס, ותעודת זהות של הסטודנט
			cout << "Enter code of Department, code of Course, and id of student:\n"; //id_s should be long type
			int code_c, id_s , x=0 , y=0,z=0;
			cin >> code >> code_c >> id_s;
			//בדיקה שהמחלקה קיימת ובמידה וכן מציאת האינדקס שלה במערך 
			for (int i = 0; i < amount_D; i++)
			{
				if (code == d1[i].get_CodeD())
				{
					y = i;
					//cout << "Y=" << y << endl;
					break;
				}
			}
			//בדיקה שהקורס קיים ובמידה וכן מציאת האינדקס שלו במערך
			for (int i = 0; i < amount_of_all_courses(d1); i++)
			{
				if (code_c == temp[i].getcodec())
				{
					x = i;
					//cout << "X=" << x << endl;
					break;
				}
			}
			//בדיקה שהסטודנט קיים ובמידה וכן מציאת האינדקס שלו במערך
			for (int i = 0; i < amount_allS; i++)
			{
				if (id_s == s1[i].getid())
				{
					z = i;
					//cout << "Z=" << x << endl;
					break;
				}
			}
			//במידה והמחלקה קיים וגם בקורס קיים וגם הסטודנט קיים מתבצע רישום של הסטודנט לקורס
			//מתבצעת הוספה של הסטודנט לקורס
			//מתבצעת הוספה של הקורס לסטודנט
			if (Department_exsit(code, d1) && Course_exsit_in_Department(code, d1, code_c) && Student_exsit_in_Department(code,d1,id_s))
			{
				temp[x] += s1[z];
				s1[z] += temp[x];
				//cout << temp[x]<<"*************\n";
				//cout << s1[z]<<"*--------------********----------\n";
				//cout << d1[y];
			}
			else
			{
				//במידה ואחד התנאים לא מתקיים מודפסת הודעה מתאימה
				if (!Department_exsit(code, d1))
				{
					cout << "Department does not exsit!\n";
					break;
				}
				if (!Course_exsit_in_Department(code, d1, code_c))
				{
					cout << "Course does not exsit in Department!\n";
					break;
				}
				if (!Student_exsit_in_Department(code, d1, id_s))
				{
					cout << "Student does not exsit in Department!\n";
					break;
				}
			}
		}
			break;
			//רישום ציונים לסטודנט בקורס ספציפי
		case 5:
		{
			//קליטת קוד קורס ובדיקה שהוא אכן קיים
			int inDex = EOF,p=EOF;
			cout << "Enter Course code:\n";
			cin >> code;
			for (int i = 0; i < amount_D; i++)
			{
				if (d1[i].check_course_code(code))
					p = i;
			}
			//במידה והוא קיים מתבצעת בדיקה באיזה אינדקס נמצא הקורס הספציפי
			if (p != EOF)
			{
				for (int i = 0; i < amount_of_all_courses(d1); i++)
				{
					if (code == temp[i].getcodec())
					{
						inDex = i;
						break;
					}
				}
			}
			//במידה והוא קיים מופעלת הפונקציה שמכניסה ציונים לתוך הסטודנטים הרשומים בקורס הספציפי
			if (inDex != EOF)
				temp[inDex].grade_();
			//אחרת מודפסת הודעה בהתאם
			else cout << "Course does not exsit\n";
		}
		break;
		//הדפסה של פרטי קורס
		case 6:
		{
			//קליטת קוד קורס ובדיקה שהוא אכן קיים ומציאת המחלקה שהוא נמצא בה
			int inDex_c = EOF, index_d=EOF;
			cout << "Enter Course code:\n";
			cin >> code;
			for (int i = 0; i < amount_D; i++)
			{
				if (d1[i].check_course_code(code))
					index_d = i;
			}
			//במידה והוא קיים, מציאת האינדקס שלו במערך
			if (index_d != EOF)
			{
				for (int i = 0; i < amount_of_all_courses(d1); i++)
				{
					if (code == temp[i].getcodec())
					{
						inDex_c = i;
						break;
					}
				}
			}
			/*
						for (int i = 0; i < amount_D; i++)
			{
				for (int j = 0; j < d1[i].get_a_courseD()+d1[i-1].get_a_courseD(); j++)
				{
					if (code == temp[j].getcodec())
					{
						
						index_d = i;
						inDex_c = j;
						break;
					}
				}
				if (index_d == i && inDex_c != EOF)
					break;
			}
			
			*/
			//במידה והוא קיים הדפסת פרטי הקורס המבוקש כולל המחלקה שבה הוא נמצא
			//אחרת מודפסת הודעה בהתאם
			if (inDex_c != EOF)
			{
				cout << "Course found in Department: ";
				cout << d1[index_d].get_NameD()<<endl;
				cout << "Code Department: ";
				cout << d1[index_d].get_CodeD()<<endl;
				cout << temp[inDex_c];
			}				
			else cout << "Course does not exsit\n";
		}
		break;
		//הדפסת פרטי הסטודנט המתבקש
		case 7:
		{
			//קליטת תעודת זהות של סטודנט ובדיקה שהוא אכן קיים
			//מציאת המחלקה שהוא רשום בה
			cout << "Enter student id: ";
			long s_id,inDex_d=EOF,inDex_s=EOF;
			cin >> s_id;

			for (int i = 0; i < amount_D; i++)
			{
				if (d1[i].check_student_id(s_id))
					inDex_d = i;
			}
			//במידה והוא קיים במחלקה נמצא את האינדקס של הסטודנט במערך
			if (inDex_d != EOF)
			{
				for (int i = 0; i < amount_allS; i++)
				{
					if (s_id == s1[i].getid())
					{
						inDex_s = i;
						break;
					}
				}
			}
	//הדפסת פרטי המחלקה שבה נמצא הסטודנט וכמובן פרטי הסטודנט
			//אחרת מודפסת הודעה בהתאם
			if (inDex_s != EOF)
			{
				cout << "Student found in Department: ";
				cout << d1[inDex_d].get_NameD() << endl;
				cout << "Code Department: ";
				cout << d1[inDex_d].get_CodeD() << endl;
				cout << s1[inDex_s];
			}
			else cout << "Student does not exsit\n\n";
		}
		break;
		//הדפסת מידע על מחלקה ספציפית
		case 8:
		{
			//קליטת קוד מחלקה
			cout << "Enter Department code:\n";
			cin >> code;
			//בדיקה שהמחלקה אכן קיימת והדפסת המחלקה המתבקשת
			//אחרת מודפסת הודעה בהתאם
			if (Department_exsit(code, d1))
				cout << d1[print_i_d];
			else cout << "Department does not exsit!!\n";

		}
		break;
		//מציאת הסטודנטים במצב לא תקין ושמירתם בתוך מערך המיועד להם
		case 9:
		{
			//קליטת קוד מחלקה
			cout << "Enter Department code:\n";
			cin >> code;
			//בדיקת שהמחלקה אכן קיימת
			//במידה והיא קיימת מופעלת פונקציה המקבלת אובייקט סטודנט בודקת את הציון שלו ובמידה והציון שלו מתחת ל65 הוא נכנס למערך המיועד לו
			//אחרת מודפסת הודעה בהתאם
			if (Department_exsit(code, d1))
			{
				for (int i = 0; i < amount_allS; i++)
				{
					d1[print_i_d].Fill_Bad_List(s1[i]);
				}
			}
			else cout << "Department does not exsit!!\n";
		}
		break;
		//מחיקת סטודנט מקורס
		case 10:
		{
			//קליטת תעודת זהות של סטודנט וקוד של קורס
			cout << "Enter Course code and Student id:\n";
			long id;
			int check_course = 0, x,y,z,check_student=0;
			cin >> code >> id;
			//בדיקה שהקורס אכן קיים ובאיזה מחלקה
			for (int i = 0; i < amount_D; i++)
			{
				if (d1[i].check_course_code(code))
				{
					check_course = 1;
					x = i;
				}
					
			}
			//אם הקורס קיים מתבצעת בדיקה האם הסטודנט רשום לקורס
			if (check_course)
			{
				for (int i = 0; i < d1[x].get_a_courseD(); i++)
				{
					if (temp[i].get_student_id(id))
					{
						check_student = 1;
						y = i;
					}
				}
			}
			else
			{
				cout << "Course does not exsit!\n";
				break;
			}
				//מציאת האינדקס של הסטודנט במידה והוא אכן רשום לקורס
			if (check_student)
			{
				for (int i = 0; i < amount_allS; i++)
				{
					if (id == s1[i].getid())
					{
						z = i;
						break;
					}
				}
				//מחיקת הסטודנט מהקורס
				//מחיקת הקורס מרשימת הקורסים של הסטודנט
				temp[y] -= s1[z];
				s1[z] -= temp[y];
			}
			else cout << "Student does not exsit in this course!\n";
		}
		break;
			//default:cout << "Wrong choice try again\n";
		}
	} while ( choice!= 11);
	//delete[]d1;
	//delete[]temp;
	//delete[]s1;

}