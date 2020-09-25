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
