#include "Course.h"


Course::Course()
{
	numofstudents = 0;
	grade = new int[1];
}


Course::~Course()
{
	//�����
	if (student)
	 delete[]student;
}
//������� ���� ����� ������� ���� ���� ����� ���� ��� ������� ���������
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
//������� �������� ������� ��� ������� ������ ��� �� ����
bool Course::operator==(const Course&other)const
{
	return(coursecode == other.coursecode);
}

bool Course::operator>(const Course&other)const/****************/
{
	return(numofstudents > other.numofstudents);
}
//������� ��� ������� ������ �� ���� ����� ��� ���� ��������� ������� ����� + ������� ����
ostream &operator<<(ostream &os, const Course &c)
{
	float cnt = 0;
	float avg=0;
	//����� ���� �����
	cout << "Course deatailes:\n";
	os <<"Course name: "<< c.nameofcourse << endl << "Course code: " << c.coursecode << endl;
	// ����� ���� ��������� ������� ����� + ������� ���� �����
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
		//����� ����� ���� ����� �� ����� �� �����
		if (c.grade[i] > 0 && c.grade[i] < 101)
		{
			os << c.grade[i] << endl;
			//����� �� ���� ��������� ��� ��� ����
			cnt++;
			//����� �� �� �������
			avg += c.grade[i];
		}
		cout << endl;
	}
	//����� ���� ��������� �� ���� ������ ����� �� ����� ������� �� ��'���
	if (cnt == c.numofstudents)
		os << "Averge of course grade: " << avg / cnt << endl << endl;
	//*************
	return os;
}
//������� ��� ������� ����� ����� ���� ����
istream &operator>>(istream &io, Course &c)
{
	//flushall;
	cout << "Enter name of course:\n";
	getline(io, c.nameofcourse);
	cout << "Enter code course:\n";
	io >> c.coursecode;
	return io;
}
//������ ���� ���� ����� ������� ���� ������ ������� ������ �� ������� �����
Course & Course::operator+=(Student& other)
{
//����� ���� ������� ������ ������ ����� �� ������� ��� ������ ����� ������ �������� ����� �� ���������
	if (!numofstudents)
	{
		student = new Student*[1];
		student[0] = &other;
		numofstudents += 1;
		cout << "num of students: " << numofstudents << endl;
		return *this;
	}
	//����� ���� �� ������� ������ ���� ���� ��� ���� ������ ������ �� ������ ����� �����(���� �� ����) ������� ����� �� ����� ������ ���� ����� ����
	//���� ��� ������ ����� ���� ���� ������� ����
	//���� ��� ������ ����� �� ����� ������ ��� ����� ������ ����� ����� ����
	//���� ��������� ������� �����
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

//������� ����� ���� ������� ����� ������ �����
Course & Course::operator-=(Student & other)
{
	int box = numofstudents;
	int k = 0;
//����� ��� ��� �� ������ ��� ������ ����� ��� ����� �������� ����� �� ���������
		if (numofstudents == 1)
		{
			delete[]this->student;
			student = NULL;
			numofstudents=0;
			return *this;
		}
//����� ��� ��� ���� ������� ��� ����� ����� ��� ������� ������ ����� ����� �����
		//���� ���� ��� ������ �� ���� �����(���� �� ���) ����� ������� �� ��������� ��������� ��� �������� ������ �����
		//�� ����� ���� ��� ��� ������� �������� �����
		//������ ����� �� ����� ������ ������ ��� ����� �� ����� ����
		//����� ����� ����� ��������� �����
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
//������� ������ ������ �� ������� ������� ������
Student * Course::operator[](const int index)const
{
	if (index >= 0 && index <numofstudents)
		return student[index];
}
//������� ����� ����� ������ ������ ���� ���� ������� �� �������
void Course::grade_()
{
	int Grade = 0;
	//����� ����� ������� ����� �� ���� ���������
	grade = new int[numofstudents];
	//����� ������ ��������� ������� �����
	cout << "Enter grade for foloowing student (ids)\n";
	for (int i = 0; i < numofstudents; i++)
	{
		cout << student[i]->getid()<<": ";
		cin >> Grade;
		grade[i] = Grade;
		cout << endl;
	}

}
//������� �������� ������� ���� ����� ���� �� ������ ������ ���� ��� ���� ������ �� ��������� �����
bool Course::get_student_id(int id)
{
	for (int i = 0; i < numofstudents; i++)
	{
		if (id == student[i]->getid())
			return true;
	}
	return false;
}
//������� ������ ������� ���� ������ ����� �� ������� ��� ������ �� ��������� ������� �� ����� ���
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