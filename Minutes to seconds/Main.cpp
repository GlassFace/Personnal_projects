#include <stdio.h>


int main()
{
	int minutes = 0, secondes = 0, total = 0;

	do
	{
		printf("Combien de minutes?\n");
		scanf_s("%d", &minutes);

		printf("\nCombien de secondes?\n");
		scanf_s("%d", &secondes);

		total = (minutes * 60) + secondes;
		
		printf("\n%d secondes en tout.\n\n\n", total);
	} while (1);

	return 0;
}