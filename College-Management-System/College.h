#ifndef _COLLEGE
#define _COLLEGE
#include "Department.h"
//הכרזה על המחלקה ועל מתשני פרייבט ופונקציות פאבליק
class College{
	Department **listD;
	int amount_D;
	Student **All_Students;
	int amount_allS;
	//אופטור פלוס שווה שהוספתי בשביל הנוחות והיצרתיות
	College & operator +=(Department &);
	//פונקציה בוליאנית הבודקת אם מחלקה קיימת
	bool Department_exsit(int, Department*);
	//פונקציה בוליאנית הבודקת אם קורס קיים במחלקה ספציפית
	bool Course_exsit_in_Department(int, Department*, int );
	//פונקציה בוליאנית הבדוקת אם סטודנט קיים במחלקה ספציפית
	bool Student_exsit_in_Department(int, Department*, int);
	//פונקציה הסוכמת את כל הקורסים הקיימים
	int amount_of_all_courses(Department *d);

public:
	College();
	~College();

	void menu();
};
#endif // !_COLLEGE
