#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buga C. Bogdan - Andrei, grupa 312 CB

#ifndef task1_si_task2
typedef struct
{
    int r, g, b;
} culoare;

typedef struct
{
    int inaltime, latime,
    rotatie, inaltimeColoana[4];
    culoare **imagine;
    char nume;
    int linie, coloana;

} piesa;

void citireCuloare(culoare *C, int R, int G, int B)
{
    C->r = R;
    C->g = G;
    C->b = B;
}

culoare** alocareMemorie(int nrLinii, int nrColoane)
{
    int i;
    culoare **imagine;
    imagine = (culoare**)malloc(nrLinii * sizeof(culoare*));
    for(i = 0; i < nrLinii; i++)
        imagine[i] = (culoare*)calloc(nrColoane, sizeof(culoare));

    return imagine;
}

void eliberareMemorie(culoare **imagine, int nrLinii)
{
    int i;
    for(i = 0; i < nrLinii; i++)
        free(imagine[i]);
    free(imagine);
}

void Header(int latime, int inaltime, FILE *out)
{
    int j, k, W, H, dimensiune, marime, padding = 0;

    if(latime % 2 == 1)
        padding = 2;

    // Dimensiunea matricei de pixeli (este inclus si padding-ul)
    W = 30 * latime + padding;
    H = 10 * inaltime;
    marime = W * H;
    dimensiune = marime + 54;

// ------------------- FILE HEADER --------------
    fputs("BM", out);

    // Dimensiunea fisierului
    for(j = 0; j < 4; j++)
        fputc(dimensiune >> 8 * j, out);

    // "Reserved"
    for(k = 1; k <= 4; k++)
        fputc(0, out);

    // Offset
    fputc(54, out);
    for(k = 1; k <= 3; k++)
        fputc(0, out);

// -------------------- INFO HEADER -------------
    //Dimensiunea Info Header-ului
    fputc(40, out);
    for(k = 1; k <= 3; k++)
        fputc(0, out);

    // Latimea si inaltimea matricei de pixeli
    for(j = 0; j < 4; j++)
        fputc((10 * latime) >> 8 * j, out);
    for(j = 0; j < 4; j++)
        fputc((10 * inaltime) >> 8 * j, out);

    fputc(1, out);
    fputc(0, out);
    fputc(24, out);
    for(k = 1; k <= 5; k++)
        fputc(0, out);

    // Dimensiunea matricei de pixeli (este inclus si padding-ul)
    for(j = 0; j < 4; j++)
        fputc(marime >> 8 * j, out);

    for(k = 38; k < 54; k++)
        fputc(0, out);
}

void creareImagine(culoare **tabla, int W, int H, FILE *out)
{
    int i, j, N;
    Header(W, H, out);
    for(i = 10 * H - 1; i >= 0; i--)
    {
        for(j = 0; j < W; j++)
            for(N = 1; N <= 10; N++)
            {
                fputc(tabla[i / 10][j].b, out);
                fputc(tabla[i / 10][j].g, out);
                fputc(tabla[i / 10][j].r, out);
            }
        if(W % 2 == 1)
            for(j = 0; j < 2; j++)
                fputc(0, out);
    }
}

void creareImaginePiesa(piesa p, FILE *out)
{
    culoare alb;
    citireCuloare(&alb, 255, 255, 255);

    int i, j;
    culoare **imagine;
    imagine = alocareMemorie(p.inaltime + 2, p.latime + 2);

    // Marginile chenarului
    for(i = 0; i < p.inaltime + 2; i++)
    {
        imagine[i][0] = alb; // marginea din stanga
        imagine[i][p.latime + 1] = alb; // marginea din dreapta
    }

    for(j = 0; j < p.latime + 2; j++)
    {
        imagine[0][j] = alb; // marginea de sus
        imagine[p.inaltime + 1][j] = alb; // marginea de jos
    }

    // Interiorul chenarului
    for(i = 1; i < p.inaltime + 1; i++)
        for(j = 1; j < p.latime + 1; j++)
            imagine[i][j] = p.imagine[i - 1][j - 1];

    creareImagine(imagine, p.latime + 2, p.inaltime + 2, out);
    eliberareMemorie(imagine, p.inaltime + 2);
}

int comparareCuloare(culoare A, culoare B)
{
    if(A.r == B.r && A.g == B.g && A.b == B.b)
        return 0;
    return 1;
}

int SpatiuLiber(culoare A)
{
    culoare alb, negru;
    citireCuloare(&alb, 255, 255, 255);
    citireCuloare(&negru, 0, 0, 0);

    if(comparareCuloare(A, alb) == 0
       || comparareCuloare(A, negru) == 0)
        return 1;
    return 0;
}

#define task1_si_task2
#endif
