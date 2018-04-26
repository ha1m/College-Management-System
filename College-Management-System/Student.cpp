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

//������� ����. ���� ������� ���� ������ ����� ���� ��� ������� ���������
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
//������� �������� ���� ������� ������ ������ ��� ����� �� �� ����� �.� ������ �� ��� ������� ���� ������
bool Student::operator==(const Student&other)const
{
	return(id == other.id);
}
//������� ��� ������ �� ���� ������� ��� ���� ������� ����� ���� �������
ostream &operator<<(ostream &os, const Student &s)
{
	//����� ���� �������
	cout << "Student deatailes:\n";
	os <<"Name: "<< s.name << endl << "id: " << s.id << endl << "age: " << s.age << endl << "gender: " << s.gender << endl;
	cout << "Student courses:\n";
	//����� ���� ������� ����� ������� ����
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
//������� ��� ����� �� ����� �� ������� ����� ���� ������� ���� ������
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
//������� ���� ���� ������� ���� ������� ���� ���� ������� ���� ������ ������� �� ������� ����� ��� ����
Student & Student::operator+=(Course & other)
{
//����� �� �� ����� ������ ����� ������ ������ ��� ����� ����� ������	
	if (!NumofCourses)
	{
		course = new Course*[1];
		course[0] = &other;
		NumofCourses += 1;
		return *this;
	}
	//����� ���� �� ����� ������ ����� ������, ������ ����� �� �� ������� ���� ���� ��� ���� ����� ���� ����� ���� ����� (���� �� ����)�� ��� ������
	//��� ����� ���� ������ �� ����� ������ ��������
	//���� ��� ������ ����� �� ����� ������ ��� ����� ������ ����� �� ����� ����
	//����� ����� ����� �������
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
//������� ����� ���� ����� ������� ���� ���� ������� ����� �� ����� ������ ������� �� �������
Student & Student::operator-=(Course & other)
{
	
	int box = NumofCourses;
	int k = 0;
//����� ��� ��� �� ���� ��� ������ ������ ����� ��� ������ ���� �������
	if (NumofCourses == 1)
	{
		delete[]this->course;
		course = NULL;
		NumofCourses = 0;
		return *this;
	}
	//����� ��� ���� ����� ���, ����� ����� ��� ����� ������� ������ �����
	//���� ���� ��� ����� �����(���� �� ���) ������� ����� �� �� ������� ���� ����� ���� ��� ������ ����� ���� �����
	//�� ����� ���� ��� �� ������� ���������. ���� ��� ������ ����� �� ����� ������ ���� ���� ����� ������ ����� ����� ����
	//��� ����� ����� ������� 
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

//������� ������ ���� ������� ������ �� ����� ������� ������
Course * Student::operator[](const int index)const
{
	if (index >=  0 && index <NumofCourses)
	return course[index];
}