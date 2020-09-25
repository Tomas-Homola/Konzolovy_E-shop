#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
	FILE *subor;
	PRODUKT produkt[10];
	int ID;
	char nazov[20];
	char vyrobca[20];
	int pocet_kusov;
	float cena;
	int i, pocet_produktov;

	subor = fopen("produkty.txt", "r");
	if (subor == NULL)
		printf("zle otvoreny subor\n");

	fscanf(subor, "%d", &pocet_produktov);

	for (i = 0; i < pocet_produktov; i++)
	{
	fscanf(subor, "%d %s %s %d %f", &ID, nazov, vyrobca, &pocet_kusov, &cena);

	produkt[i].ID = ID;
	strcpy(produkt[i].nazov, nazov);
	strcpy(produkt[i].vyrobca, vyrobca);
	produkt[i].pocet_kusov = pocet_kusov;
	produkt[i].cena = cena;

	printf("Produkt ID: %d, nazov: %s, vyrobca: %s, pocet kusov: %d, cena: %.2f\n", produkt[i].ID, produkt[i].nazov, produkt[i].vyrobca,
	produkt[i].pocet_kusov, produkt[i].cena);
	}






	return 0;
}
