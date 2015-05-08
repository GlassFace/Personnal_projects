
#ifndef PROFESSION_H_INCLUDED
#define PROFESSION_H_INCLUDED

class TProfession
{
public:

	TProfession();
	virtual ~TProfession();


	static void S_InitializeProfessions();

	
	virtual void ProfessionUpdate(TVillager * pVillager) = 0;
};

#endif
