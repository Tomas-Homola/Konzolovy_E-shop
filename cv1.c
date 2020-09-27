#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pocet_produktov; // celkovy pocet produktov

typedef struct
{
	int ID;
	char nazov[20];
	char vyrobca[20];
	int pocet_kusov;
	float cena;
} PRODUKT;

PRODUKT *produkty; // smernik, ktory bude ukazovat na miesto, kde budu jednotlive produkty ulozene

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
	
	zakaznik = (ZAKAZNIK *)malloc(sizeof(ZAKAZNIK));
	
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
	
	printf("Vysledky pre hladany vyraz '%s':\n", hladany_vyraz);

	for (i = 0; i < pocet_produktov; i++)
	{
		if (strstr(produkty->nazov, strlwr(hladany_vyraz)) != NULL)
		{
			printf("Nazov produktu: %s, ID: %d\n", produkty->nazov, produkty->ID);
			produkty++;
		}
		else
			produkty++;
	}
	
	produkty -= pocet_produktov; // vratenie smernika na zaciatok allokovanej pamati
	
	//printf()

	printf("\n");
	main_page();
}

void produkty_vypis_podla_vyrobcu(char *hladany_vyraz)
{
	int i;

	printf("Vysledky pre hladanie podla vyrobcu '%s':\n", hladany_vyraz);
	
	for (i = 0; i < pocet_produktov; i++)
	{
		if (strstr(produkty->vyrobca, strupr(hladany_vyraz)) != NULL)
		{
			printf("Nazov produktu: %s, ID: %d\n", produkty->nazov, produkty->ID);
			produkty++;
		}
		else
			produkty++;
	}

	produkty -= pocet_produktov; // vratenie smernika na zaciatok allokovanej pamati


	printf("\n");
	main_page();
}

void produkt_vyber_podla_ID()
{
	
}

void main_page()
{
	int volba = 0;
	char hladany_vyraz[20];
	
	do
	{
		printf("Vyberte moznost:\n1 -> pre hladanie podla nazvu produktu\n2 -> hladanie podla vyrobcu\n3 -> pre ukoncenie nakupu\n");
		scanf("%d", &volba);
		if (volba > 3 || volba < 1)
			printf("Zle zadana moznost\n");
			
	} while (volba > 3 || volba < 1);
	
	if (volba == 1)
	{
		puts("Hladat podla:");
		scanf("%s", hladany_vyraz);
		
		produkty_vypis_podla_nazvu(hladany_vyraz);
	}
	else if (volba == 2)
	{
		puts("Hladat podla:");
		scanf("%s", hladany_vyraz);

		produkty_vypis_podla_vyrobcu(hladany_vyraz);
	}
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
