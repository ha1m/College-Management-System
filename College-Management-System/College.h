#ifndef _COLLEGE
#define _COLLEGE
#include "Department.h"
//����� �� ������ ��� ����� ������ ��������� ������
class College{
	Department **listD;
	int amount_D;
	Student **All_Students;
	int amount_allS;
	//������ ���� ���� ������� ����� ������ ���������
	College & operator +=(Department &);
	//������� �������� ������ �� ����� �����
	bool Department_exsit(int, Department*);
	//������� �������� ������ �� ���� ���� ������ �������
	bool Course_exsit_in_Department(int, Department*, int );
	//������� �������� ������ �� ������ ���� ������ �������
	bool Student_exsit_in_Department(int, Department*, int);
	//������� ������ �� �� ������� �������
	int amount_of_all_courses(Department *d);

public:
	College();
	~College();

	void menu();
};
#endif // !_COLLEGE
