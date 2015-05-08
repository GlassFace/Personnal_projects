
#ifndef PROFESSION_H_INCLUDED
#define PROFESSION_H_INCLUDED

class TProfession
{
public:

	TProfession();
	TProfession(TVillager * pLinkedVillager);
	virtual ~TProfession();


	static void S_InitializeProfessions();

	
	virtual void ProfessionUpdate() = 0;

protected:

	TVillager * m_pLinkedVillager;
};

#endif
