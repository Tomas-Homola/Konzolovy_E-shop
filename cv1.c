#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pocet_produktov;

typedef struct
{
	int ID;
	char nazov[20];
	char vyrobca[20];
	int pocet_kusov;
	float cena;
} PRODUKT;

typedef struct
{
	char meno[20];
	char priezvisko[20];
	float rozpocet;
	PRODUKT kupene_produkty[50];
} ZAKAZNIK;

PRODUKT *produkty_nacitaj_zo_suboru(char *filename)
{
	PRODUKT *produkty;
	FILE *subor;
	int ID;
	char nazov[20];
	char vyrobca[20];
	int pocet_kusov;
	float cena;
	int i;

	subor = fopen(filename, "r");
	if (subor == NULL)
		return NULL;

	fscanf(subor, "%d", &pocet_produktov);

	produkty = (PRODUKT *)malloc(sizeof(PRODUKT) * pocet_produktov);
	
	for (i = 0; i < pocet_produktov; i++)
	{
	fscanf(subor, "%d %s %s %d %f", &ID, nazov, vyrobca, &pocet_kusov, &cena);

	produkty->ID = ID;
	strcpy(produkty->nazov, nazov);
	strcpy(produkty->vyrobca, vyrobca);
	produkty->pocet_kusov = pocet_kusov;
	produkty->cena = cena;

	//printf("Produkt ID: %d, nazov: %s, vyrobca: %s, pocet kusov: %d, cena: %.2f\n", produkty->ID, produkty->nazov, produkty->vyrobca, produkty->pocet_kusov, produkty->cena);
	
	produkty++;
	}
	
	produkty = produkty - 10;


	return produkty;
}

void produkty_vypis(PRODUKT *produkty)
{
	int i;
	
	for (i = 0; i < pocet_produktov; i++)
	{
		printf("Produkt ID: %d, nazov: %s, vyrobca: %s, pocet kusov: %d, cena: %.2f\n", produkty->ID, produkty->nazov, produkty->vyrobca, produkty->pocet_kusov, produkty->cena);
		
		produkty++;
	}
}

int main()
{
	FILE *subor;
	PRODUKT *produkty;
	
	produkty = produkty_nacitaj_zo_suboru("produkty.txt");

	produkty_vypis(produkty);





	return 0;
}
