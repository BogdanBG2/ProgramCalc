#include "task1_si_task2.h"

// Buga C. Bogdan - Andrei, grupa 312 CB

#ifndef task3_si_task4

void hartaInitialaTask3(culoare **tabla, int H, int W)
{
    culoare alb, negru;
    citireCuloare(&alb, 255, 255, 255);
    citireCuloare(&negru, 0, 0, 0);

    int i, j;

    for(i = 0; i < H; i++)
        for(j = 0; j < W; j++)
            if(i < 4)
                tabla[i][j] = alb;
            else
                tabla[i][j] = negru;
}

void identificarePiesa(piesa *p, piesa P[7][4])
{
    int sem = 0, i, j;
    for(i = 0; i < 7 && !sem; i++)
        if(p->nume == P[i][0].nume)
            for(j = 0; j < 4 && !sem; j++)
                if(p->rotatie == P[i][j].rotatie)
                {
                    sem = 1;
                    *p = P[i][j];
                }
}

void coborarePiesa(piesa *p, culoare **tabla, int H)
{
        int j, k,
        W2 = p->latime,
        spatiu[4], nrSpatii, coliziune = 0;

        for(j = 0; j < W2; j++)
            spatiu[j] = p->inaltimeColoana[j];

        while(!coliziune && p->linie < H - 1)
        {
            nrSpatii = 0;
            for(j = p->coloana; j - p->coloana < W2; j++)
            {
                k = j - p->coloana;
                if(SpatiuLiber(tabla[spatiu[k]][j]))
                        nrSpatii++;
            }
            if(nrSpatii != p->latime)
                coliziune = 1;
            else
                p->linie++;

            for(j = 0; j < W2; j++)
                spatiu[j]++;
        }
}

void adaugarePiesaPeTabla(piesa p, culoare **tabla)
{
    int i, j;
    int H2 = p.inaltime,
    W2 = p.latime;

    for(i = 0; i < H2; i++)
        for(j = 0; j < W2; j++)
            if(!SpatiuLiber(p.imagine[i][j]))
                tabla[i + p.linie - H2 + 1][j + p.coloana]
                = p.imagine[i][j];
}

int sfarsitJoc(culoare **tabla, int W)
{
    int i, j, sfarsit = 0;
        for(i = 0; i < 4; i++)
            for(j = 0; j < W; j++)
                if(!SpatiuLiber(tabla[i][j]))
                    sfarsit = 1;
    return sfarsit;
}

int linieCompleta(int i, culoare **tabla, int W)
{
    int j;
    for(j = 0; j < W; j++)
        if(SpatiuLiber(tabla[i][j]))
            return 0;
    return 1;
}

void eliminareLinie(int i, culoare **tabla, int W)
{
    culoare negru;
    citireCuloare(&negru, 0, 0, 0);

    int i2, j2;
    for(i2 = i; i2 >= 4; i2--)
        for(j2 = 0; j2 < W; j2++)
            if(i2 > 4)
                tabla[i2][j2] = tabla[i2-1][j2];
            else
                tabla[i2][j2] = negru;
}

int latimeTask4(FILE *input)
{
    int W = 0, i;
    int A[4];
    char aux[4];

    fseek(input, 18, SEEK_SET);
    fgets(aux, 5, input);
    for(i = 0; i < 4; i++)
    {
        A[i] = (aux[i] + 256) % 256;
        W += (int)A[i] << 8 * i;
    }
    return W;
}

int inaltimeTask4(FILE *input)
{
    int H = 0, i;
    int A[4];
    char aux[4];

    fseek(input, 22, SEEK_SET);
    fgets(aux, 5, input);
    for(i = 0; i < 4; i++)
    {
        A[i] = (aux[i] + 256) % 256;
        H += (int)A[i] << 8 * i;
    }
    return H;
}

#define task3_si_task4
#endif