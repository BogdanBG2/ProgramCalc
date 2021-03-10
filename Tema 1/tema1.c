#include <stdio.h>
#include <math.h>

// TetriBit - Buga C. Bogdan - Andrei, grupa 312CB

//Afisarea tablei de joc
void afisare(unsigned long long H)
{
    int i;
    for(i = 63; i >= 0; --i)
    {
        if((H >> i) & 1)
            printf("#");
        else
            printf(".");

        if(i % 8 == 0)
            printf("\n");
    }
    printf("\n");
}

//Numarul de zerouri de pe tabla (util la calcularea scorului)
int nrZero(unsigned long long H)
{
    int k = 64, j;
    for(j = 63; j >= 0; --j)
        if((H >> j) & 1)
            --k;
    return k;
}

// Coliziune jos
int coliziuneJos(unsigned long long p, unsigned long long H)
{
    int colJ = 0, a;

    for(a = 0; a <= 7 && colJ == 0; ++a)
        if((p >> a) & 1)
            colJ = 1;

    for(a = 0; a <= 63 && colJ == 0; ++a)
        if(((p >> 8) >> a) & (H >> a))
            colJ = 1;

    return colJ;
}

// Coliziune la stanga
int coliziuneStanga(unsigned long long p, unsigned long long H)
{
    int colS = 0, a;

    for(a = 7; a <= 63 && colS == 0; a += 8)
        if((p >> a) & 1)
            colS = 1;

    for(a = 0; a <= 63 && colS == 0;a++)
        if((H >> a) & ((p << 1) >> a))
            colS = 1;

    return colS;
}

// Coliziune la dreapta
int coliziuneDreapta(unsigned long long p, unsigned long long H)
{
    int colD = 0, a;

    for(a = 0;a <= 63 && colD == 0; a += 8)
        if((p >> a) & 1)
            colD = 1;

    for(a = 0; a <= 63 && colD == 0; ++a)
        if((H >> a) & ((p >> 1) >> a))
            colD = 1;

    return colD;
}

//Coliziune pe prima linie
int Top(unsigned long long p, unsigned long long H)
{
    int T = 0, a;

    for(a = 56; a < 64 && T == 0; ++a)
        if(((p << 56) >> a) & (H >> a))
            T=1;

    return T;
}

// Linie completa
int linieCompleta(int i, unsigned long long H)
{
    if((H >> (64 - 8 * i)) % 256 == 255)
        return 1;
    else
        return 0;
}

//Scorul final, unde z - nr. zerouri, cl - nr. linii complete
float scor(int z, int cl)
{
    return (sqrt(z) + pow(1.25, cl));
}

int main()
{
    unsigned long long H, p[50], aux;
    int nrLinii = 0, M, m[50][8], E, GameOver = 0, i, j;

    // Citirea lui n (harta initiala)
    scanf("%llu", &H);

    //Citirea numarului de mutari
    scanf("%d", &M);

    for(i = 0; i < M; ++i)
    {
        scanf("%llu", &p[i]); // citirea codurilor pieselor

        for(j = 0; j < 8; ++j)
            scanf("%d", &m[i][j]); // cititea mutarilor
    }

    // Afisarea hartii initiale
    afisare(H);

    // Adaugarea de piese pe tabla de joc
    for(i = 0; i < M && GameOver == 0; ++i)
    {
        if(GameOver == 1)
            break;

        E = 0; // rolul lui E este acela de a indica daca a fost eliminata sau nu macar o linie
        aux = p[i]; // aux este o variabila in care retinem codul piesei pe ultimele 2 linii
        p[i] <<= 56;

        for(j = 0; j < 8 && GameOver == 0; ++j)
        {
            //Terminarea jocului daca piesa nu incape pe tabla de joc
            if(GameOver == 1)
                break;

            //Afisarea piesei complete in cazul in care aceasta ocupa 2 linii
            if(j == 1)
                p[i] = aux << 48;

            if(m[i][j] > 0) // Muatare la dreapta 
            {
                int q = 0;
                while(q < m[i][j])
                    if(coliziuneDreapta(p[i] >> q, H) == 0)
                        ++q;
                    else
                        break;
                aux >>= q;
                p[i] >>= q;
            }
            else if(m[i][j] < 0) // Mutare la stanga
            {
                int q = 0;
                while(q < (-1) * m[i][j])
                    if(coliziuneStanga(p[i] << q, H)==0)
                        ++q;
                    else
                        break;
                aux <<= q;
                p[i] <<= q;
            }

            if(j == 0) // Daca piesa nu poate efectua prima coborare de linie
            {
                if(aux < 255) // daca piesa ocupa doar un rand pe tabla de joc
                {
                    if(Top(aux, H) == 1)
                    {
                        afisare(H);
                        GameOver = 1;
                        break;
                    }
                }
                else // daca piesa ocupa doua randuri pe tabla de joc
                {
                    if(Top(aux, H) == 1)
                    {
                        afisare(H);
                        GameOver = 1;
                        break;
                    }
                    else 
                    {
                        if(Top(aux, H << 8) == 1) // daca nu are coliziune pe prima linie, dar are in schimb pe a doua
                        {
                            H += p[i];
                            afisare(H);
                            afisare(H);
                            GameOver = 1;
                            break;
                        }
                    }
                }
            } // jocul se termina atunci cand GameOver=1

            // Testare daca piesa poate sau nu sa coboare
            if(coliziuneJos(p[i],H) == 0)
            {
                afisare(H + p[i]);
                p[i] >>= 8;
            }
            else
            {
                H += p[i];
                afisare(H);
                break;
            }
        }

        // Eliminarea liniilor complete
        int L;
        for(L = 1; L <= 8; ++L)
            if(linieCompleta(L, H)==1) // if(n >> ((64 - 8 * L)) % 256 == 255)
            {
                unsigned long long r = H >> (64 - 8 * L);
                H -= r << (64 - 8 * L);
                r >>= 8;
                H += r << (64 - 8 * L);
                ++nrLinii; ++E;
            }
        if(E)
            afisare(H); // se afiseaza noua harta daca se elimina cel putin o linie
    }

    // Finalul jocului
    printf("GAME OVER!\nScore:%.2f\n", scor(nrZero(H), nrLinii));

    return 0;
}
