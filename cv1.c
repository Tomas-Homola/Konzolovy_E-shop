#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pocet_produktov, pocet_kupenych_produktov = 0; // celkovy pocet produktov
float minute_peniaze = 0.0;

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

ZAKAZNIK *zakaznik;

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

	subor = fopen(filename, "r"); // kontrola otvorenia suboru
	if (subor == NULL)
		return NULL;

	fscanf(subor, "%d", &pocet_produktov); // nacitanie poctu produktov

	produkty = (PRODUKT *)malloc(sizeof(PRODUKT) * pocet_produktov); // alokacia pamate
	
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

	fclose(subor);
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

void produkt_vyber_podla_ID(int vybrane_ID)
{
	int kupit;
	
	produkty += vybrane_ID - 1; // presun na vybrany produkt

	if (produkty->pocet_kusov < 1) // produkt NIE JE na skladke
	{
		printf("Vybrany produkt '%s' momentalne nie je na sklade\n", produkty->nazov);
		produkty -= vybrane_ID - 1;
		main_page();
	}
	else // produkt JE na sklade
	{
		printf("Vybrany produkt '%s' je na sklade, cena: %.2f\n", produkty->nazov, produkty->cena);
		printf("\nZadajte:\n1 - kupit vybrany produkt\n0 - nekupit vybrany produkt\n");
		scanf("%d", &kupit);
		
		if (kupit == 1)
		{
			if (zakaznik->rozpocet > produkty->cena)
			{
			puts("Kupene");
			zakaznik->rozpocet -= produkty->cena;
			strcpy(zakaznik->kupene_produkty[pocet_kupenych_produktov].nazov, produkty->nazov); // zapisanie nazvu
			strcpy(zakaznik->kupene_produkty[pocet_kupenych_produktov].vyrobca, produkty->vyrobca); // zapisanie vyrobcu
			pocet_kupenych_produktov++; // index pre pole kupenych produktov
			minute_peniaze += produkty->cena; // celkova minuta suma penazi
			produkty->pocet_kusov--;
			
			if (produkty->pocet_kusov < 0) // kontrola, aby nebol zaporny pocet kusov
				produkty->pocet_kusov = 0;
			}
			else
				puts("Nedostatok penazi");
		}
		else if (kupit == 0)
			puts("Nekupene");
	}
	
	produkty -= vybrane_ID - 1; // vratenie sa na zaciatok pola produktov
	printf("\n");
	main_page();
}

void produkty_vypis_podla_nazvu(char *hladany_vyraz)
{
	int i, najdene_produkty = 0, vybrane_ID;
	
	printf("\nVysledky pre hladany vyraz '%s':\n", hladany_vyraz);

	for (i = 0; i < pocet_produktov; i++)
	{
		if (strstr(produkty->nazov, strlwr(hladany_vyraz)) != NULL)
		{
			printf("Vyrobca: %s, Nazov produktu: %s, ID: %d\n", produkty->vyrobca, produkty->nazov, produkty->ID);
			produkty++;
			najdene_produkty++;
		}
		else
			produkty++;
	}
	
	produkty -= pocet_produktov; // vratenie smernika na zaciatok allokovanej pamati
	
	if (najdene_produkty > 0)
	{
		printf("\nVyberte si produkt podla jeho ID\n");
		scanf("%d", &vybrane_ID); // tu este pridat podmienku, aby sa dalo vybrat len ID produktov, ktore sa nasli?
		
		produkt_vyber_podla_ID(vybrane_ID);
	}
	else
	{
		puts("Pod hladanym nazvom sa nic nenaslo");
		printf("\n");
	    main_page();
	}
}

void produkty_vypis_podla_vyrobcu(char *hladany_vyraz)
{
	int i, najdene_produkty = 0, vybrane_ID;

	printf("\nVysledky pre hladanie podla vyrobcu '%s':\n", hladany_vyraz);
	
	for (i = 0; i < pocet_produktov; i++)
	{
		if (strstr(produkty->vyrobca, strupr(hladany_vyraz)) != NULL)
		{
			printf("Vyrobca: %s, Nazov produktu: %s, ID: %d\n", produkty->vyrobca, produkty->nazov, produkty->ID);
			produkty++;
			najdene_produkty++;
		}
		else
			produkty++;
	}

	produkty -= pocet_produktov; // vratenie smernika na zaciatok allokovanej pamati
	
	if (najdene_produkty > 0)
	{
		printf("\nVyberte si produkt podla jeho ID\n");
		scanf("%d", &vybrane_ID); // tu este pridat podmienku, aby sa dalo vybrat len ID produktov, ktore sa nasli?

		produkt_vyber_podla_ID(vybrane_ID);
	}
	else
	{
		puts("Pod hladanym nazvom sa nic nenaslo");
		printf("\n");
	    main_page();
	}
}

void main_page()
{
	int volba = 0, i;
	char hladany_vyraz[20] = {};
	
	do
	{
		printf("\nVyberte moznost:\n1 -> pre hladanie podla nazvu produktu\n2 -> hladanie podla vyrobcu\n3 -> pre ukoncenie nakupu\n");
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
	{
		//printf("\nKoniec nakupu, kupene produkty:\n");
		
		printf("\nKoniec nakupu");
		//for (i = 0; i < pocet_kupenych_produktov; i++)
		//	printf("%s od %s\n", zakaznik->kupene_produkty[i].nazov, zakaznik->kupene_produkty[i].vyrobca);
			
		printf("Minute love: %.2f EUR\n", minute_peniaze);
	}
}

int main()
{
	FILE *blok;
	int i;
	
	produkty = produkty_nacitaj_zo_suboru("produkty.txt");
	
	zakaznik = registruj_zakaznika();
	
	printf("\nZakaznik:\n-meno: %s\n-priezvisko: %s\n-rozpocet: %.2f EUR\n", zakaznik->meno, zakaznik->priezvisko, zakaznik->rozpocet);

	main_page();

	blok = fopen("kupene_produkty.txt", "w");
	for (i = 0; i < pocet_kupenych_produktov; i++)
	{
		fprintf(blok, "%s %s\n", zakaznik->kupene_produkty[i].nazov, zakaznik->kupene_produkty[i].vyrobca);
	}
	
	fclose(blok);
	
	return 0;
}
