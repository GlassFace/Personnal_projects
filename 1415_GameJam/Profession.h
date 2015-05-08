
#ifndef PROFESSION_H_INCLUDED
#define PROFESSION_H_INCLUDED

class TProfession : public TVillager
{
public:

	TProfession();
	virtual ~TProfession();


	static void S_InitializeProfessions();

	
	virtual void ProfessionUpdate() = 0;
};

#endif
