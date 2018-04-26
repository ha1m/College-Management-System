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
//������� ���� ���� ���� �� �������� ������ ��� ������� ���������
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
//������� ��� ������ �� ���� ������, ���� ������� ������� ������, ����� ��������� ������� ������, ������ �������� ���� �� ����
ostream &operator<<(ostream &os, const Department &d)
{
	//���� �����
	cout << "Department deatails:\n";
	os << "Name: " << d.NameD << endl;
	os << "Code: " << d.CodeD << endl << endl;
	//���� ������ ������� ������
	cout << "List of Department courses:\n";
	for (int i = 0; i < d.amount_Course_D; i++)
	{
		os << "Course Name : " << d.courseD[i]->getnamec() << endl;
		os << "Course code: " << d.courseD[i]->getcodec() << endl;
		cout << endl;
	}
	//���� �������� ������� ������
	cout << "List of Students in the Department:\n";
	for (int i = 0; i < d.amount_Student_D; i++)
	{
		os << "Name : " << d.studentD[i]->getname() << endl;
		os << "Id: " << d.studentD[i]->getid() << endl;
		os << "Age: "<< d.studentD[i]->getage() << endl;
		os << "Gender: "<< d.studentD[i]->getgender() << endl;
		cout << endl;
	}
	//���� ��������� ���� �� ���� ������
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
//������ ��� ����� �� ���� �����
istream &operator>>(istream &io, Department & d)
{
	cout << "Enter name of Department:\n";
	getline(io, d.NameD);
	cout << "Enter code Department:\n";
	io >> d.CodeD;
	return io;
}

//������� �������� ������� ���� ��� �� ���� ������ ���� ��� ���� ������ �� ������� ������

bool Department::check_course_code(int code_course)const
{
	for (int i = 0; i < amount_Course_D; i++)
	{
		if (code_course == courseD[i]->getcodec())
			return true;
	}
	return false;
}

//������� �������� ������� ���� ����� ���� ������ ���� ������� ���� ������� �������� �� ������
bool Department::check_student_id(int id)const
{
	for (int i = 0; i < amount_Student_D; i++)
	{
		if (id == studentD[i]->getid())
			return true;
	}
	return false;
}
// ������� ���� ���� ������ ���� ������
Department & Department::operator+=(Course &other)
{
//�� ��� ����� ������ ����� ������ ����� �� ����� ��� ������ ����� ������ ������ ������ ���� �������
	if (!amount_Course_D)
	{
		courseD = new Course*[1];
		courseD[0] = &other;
		amount_Course_D += 1;
		return *this;
	}
	//����� ���� �� ����� ������ ���� ���� ��� ���� ���� ���� ����� ����� ������
	//����� ���� ����� ���� �����(���� �� ���) ���� ������ ������ ���� �� ����� ������ ���������
	//������ ����� �� ����� ������ ����� ��� ����� ������ ����� ����� ����
	//����� ����� ����� ����� ������� ������
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

//������� ���� ���� ������� ���� ������ ������ ������� ������
Department & Department::operator+=(Student &other)
{

//����� ���� ������ ����� ������ ����� ��� ��� ������ �����
	//����� �� ����� ���� ���������
	if (!amount_Student_D)
	{
		studentD = new Student*[1];
		studentD[0] = &other;
		amount_Student_D += 1;
		return *this;
	}
	//����� ���� �� ������� ������ ���� ���� ��� ����� �����(���� �� ���) ���� ����� ����� ������
	//��� ������ �� ����� ���� ����� ����� �� ������� ����
	//������ ����� �� ����� ������ ������ ����� ������ ����� ����� ����
	//����� ����� ����� ��������� ������� ������
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
//������� ������� ������ �� ����� �� �������� ���� �� ���� ������
//�������� ���� ������ ���� ������ ����� ����� �� ����� ���
//����� ������ ��� ���� �65 ��� ���� ���� ���� ��������� ����� �� ����
int Department::Fill_Bad_List(Student &s)
{
	for (int i = 0; i < amount_Course_D; i++)
	{
		if (courseD[i]->get_student_grade(s) < 65)
		{
			//�� ��� ������ ����� ��� ���� ��� ������ �����
			//��� �� ������ �� ���� ��������� ���� �� ����
			if (!amount_bad_student)
			{
				Bad_ac_student = new Student*[1];
				Bad_ac_student[0] = &s;
				amount_bad_student += 1;
				break;
			}
			else
			{
				//���� ���� ���� ��� �� ���� ����� ����� ����� ����� ������ ����� ��� ������ ������� ���� �� ����
				//����� �� ����� ������
				//����� �� ����� ������ ����� ����
				//����� ���� ��������� ���� �� ����
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