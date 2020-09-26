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

PRODUKT *produkty;

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

	subor = fopen(filename, "r"); //kontrola otvorenia suboru
	if (subor == NULL)
		return NULL;

	fscanf(subor, "%d", &pocet_produktov); //nacitanie poctu produktov

	produkty = (PRODUKT *)malloc(sizeof(PRODUKT) * pocet_produktov); //alokacia pamate
	
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
	
	produkty = produkty - pocet_produktov;


	return produkty;
}

ZAKAZNIK *registruj_zakaznika()
{
	ZAKAZNIK *zakaznik;
	char meno[20];
	char priezvisko[20];
	float rozpocet;
	
	zakaznik = malloc(sizeof(ZAKAZNIK));
	
	printf("Zadaj meno zakaznika:\n");
	scanf("%s", meno);
	
	printf("Zadaj priezvisko zakaznika:\n");
	scanf("%s", priezvisko);

	printf("Zadaj rozpocet zakaznika:\n");
	scanf("%f", &rozpocet);
	
	strcpy(zakaznik->meno, meno);
	strcpy(zakaznik->priezvisko, priezvisko);
	zakaznik->rozpocet = rozpocet;
	
	return zakaznik;
}

void produkty_vypis_podla_nazvu(char *hladany_vyraz)
{
	int i;
	
	for (i = 0; i < pocet_produktov; i++)
	{
		printf("Produkt ID: %d, nazov: %s, pocet kusov: %d, cena: %.2f EUR\n\n", produkty->ID, produkty->nazov, produkty->pocet_kusov, produkty->cena);
		
		produkty++;
	}
	
	produkty -= pocet_produktov;
	
	main_page();
}

void produkty_vypis_podla_vyrobcu(char *hladany_vyraz)
{
	int i;

	for (i = 0; i < pocet_produktov; i++)
	{
		printf("Produkt ID: %d, vyrobca: %s, pocet kusov: %d, cena: %.2f EUR\n\n", produkty->ID, produkty->vyrobca, produkty->pocet_kusov, produkty->cena);

		produkty++;
	}
	
	produkty -= pocet_produktov;
	
	main_page();
}

void main_page()
{
	int volba = 0;
	char hladany_vyraz[20];
	
	do
	{
		printf("Vyberte moznost:\n1 -> pre hladanie podla nazvu produktu\n2 -> hladanie podla vyrobcu\n3 -> pre ukoncenie nakupu\n");
		scanf("%d", &volba);
		if (volba > 3)
			printf("Zle zadana moznost\n");
			
	} while (volba > 3);
	
	if (volba == 1)
		puts("Hladat:")
		scanf("%s", hladany_vyraz);
		
		produkty_vypis_podla_nazvu(hladany_vyraz);
	else if (volba == 2)
		puts("Hladat:")
		scanf("%s", hladany_vyraz);

		produkty_vypis_podla_vyrobcu(hladany_vyraz);
	else if (volba == 3)
		puts("koniec nakupu");
}

int main()
{
	FILE *subor;
	ZAKAZNIK *zakaznik;
	
	produkty = produkty_nacitaj_zo_suboru("produkty.txt");
	
	//zakaznik = registruj_zakaznika();
	
	//printf("meno: %s\npriezvisko: %s\nrozpocet: %.2f EUR\n", zakaznik->meno, zakaznik->priezvisko, zakaznik->rozpocet);

	main_page();



	return 0;
}
