#include "task1_si_task2.h"
#include "task3_si_task4.h"

// Buga C. Bogdan - Andrei, grupa 312 CB

int main(int argc, char *argv[])
{
// ------------ Predefinirea culorilor ----------
    culoare alb, negru, rosu, portocaliu, galben, verde, albastru, mov, roz;
    citireCuloare(&alb, 255, 255, 255);
    citireCuloare(&negru, 0, 0, 0);
    citireCuloare(&rosu, 255, 0, 0);
    citireCuloare(&portocaliu, 255, 140, 0);
    citireCuloare(&galben, 255, 255, 0);
    citireCuloare(&verde, 0, 255, 0);
    citireCuloare(&albastru, 0, 0, 255);
    citireCuloare(&mov, 130, 0, 255);
    citireCuloare(&roz, 255, 0, 255);

    int i, j, k, r, i2, j2;
    piesa P[7][4];

// --------------------- I ----------------------
    P[0][0].latime = 1;
    P[0][0].inaltime = 4;
    P[0][0].nume = 'I';
// --------------------- O ----------------------
    P[1][0].latime = 2;
    P[1][0].inaltime = 2;
    P[1][0].nume = 'O';
// --------------------- S ----------------------
    P[2][0].latime = 3;
    P[2][0].inaltime = 2;
    P[2][0].nume = 'S';
// --------------------- Z ----------------------
    P[3][0].latime = 3;
    P[3][0].inaltime = 2;
    P[3][0].nume = 'Z';
// --------------------- L ----------------------
    P[4][0].latime = 2;
    P[4][0].inaltime = 3;
    P[4][0].nume = 'L';
// --------------------- J ----------------------
    P[5][0].latime = 2;
    P[5][0].inaltime = 3;
    P[5][0].nume = 'J';
// --------------------- T ----------------------
    P[6][0].latime = 3;
    P[6][0].inaltime = 2;
    P[6][0].nume = 'T';
// ---------------- Piesele rotite --------------
    for(i = 0; i < 7; i++)
    {
        P[i][0].rotatie = 0;
        for(j = 1; j < 4; j++)
        {
            P[i][j].latime = P[i][j - 1].inaltime;
            P[i][j].inaltime = P[i][j - 1].latime;
            P[i][j].nume = P[i][j - 1].nume;
            P[i][j].rotatie = P[i][j - 1].rotatie + 90;
        }
    }

// Setarea dimensiunilor prin alocare dinamica --
    for(k = 0; k < 7; k++) // k = indice de piesa
        for(r = 0; r < 4; r++) // r = indice de rotatie
            P[k][r].imagine =
            alocareMemorie(P[k][r].inaltime, P[k][r].latime);

    for(k = 0; k < 7; k++)
    {
        for(i = 0; i < P[k][0].inaltime; i++)
            for(j = 0; j < P[k][0].latime; j++)
            {
                P[k][0].imagine[i][j] = alb;
                switch(k)
                {
                    case 0: // I
                        P[k][0].imagine[i][j] = albastru;
                        break;
                    case 1: // O
                        P[k][0].imagine[i][j] = galben;
                        break;
                    case 2: // S
                        if((i + j) && (i + j - 3))
                            P[k][0].imagine[i][j] = rosu;
                        break;
                    case 3: // Z
                        if(!(j - i) || !(j - i - 1))
                            P[k][0].imagine[i][j] = verde;
                        break;
                    case 4: // L
                        if(!j || !(i - 2))
                            P[k][0].imagine[i][j] = portocaliu;
                        break;
                    case 5: // J
                        if(!(j - 1) || !(i - 2))
                            P[k][0].imagine[i][j] = roz;
                        break;
                    case 6: // T
                        if(!(j - 1) || !i)
                            P[k][0].imagine[i][j] = mov;
                        break;
                }
            }

        for(r = 1; r < 4; r++)
        {
            int H = P[k][r].inaltime,
            W = P[k][r].latime;

            for(j = 0; j < H; j++)
                for(i = 0; i < W; i++)
                    P[k][r].imagine[j][i] =
                    P[k][r - 1].imagine[W - 1 - i][j];
        }
    }

// Cat de lunga este fiecare coloana a fiecarei piese?
    for(i = 0; i < 7; i++)
        for(j = 0; j < 4; j++)
            for(j2 = 0; j2 < P[i][j].latime; j2++)
                for(i2 = P[i][j].inaltime - 1; i2 >= 0; i2--)
                    if(!SpatiuLiber(P[i][j].imagine[i2][j2]))
                    {
                        P[i][j].inaltimeColoana[j2] = i2 + 1;
                        break;
                    }

//----------------- TASK 1 ----------------------
    if(!strcmp(argv[1], "1"))
    {
        FILE *f[7];
        // Deschiderea fisierelor
        f[0] = fopen("piesa_I.bmp", "wb");
        f[1] = fopen("piesa_O.bmp", "wb");
        f[2] = fopen("piesa_S.bmp", "wb");
        f[3] = fopen("piesa_Z.bmp", "wb");
        f[4] = fopen("piesa_L.bmp", "wb");
        f[5] = fopen("piesa_J.bmp", "wb");
        f[6] = fopen("piesa_T.bmp", "wb");

        for(i = 0; i < 7; i++)
        {
            creareImaginePiesa(P[i][0], f[i]);
            fclose(f[i]);
        }
    }
//----------------- TASK 2 ----------------------
    if(!strcmp(argv[1], "2"))
    {
        FILE *g[7][3];
        g[0][0] = fopen("piesa_I_90.bmp", "wb");
        g[0][1] = fopen("piesa_I_180.bmp", "wb");
        g[0][2] = fopen("piesa_I_270.bmp", "wb");

        g[1][0] = fopen("piesa_O_90.bmp", "wb");
        g[1][1] = fopen("piesa_O_180.bmp", "wb");
        g[1][2] = fopen("piesa_O_270.bmp", "wb");

        g[2][0] = fopen("piesa_S_90.bmp", "wb");
        g[2][1] = fopen("piesa_S_180.bmp", "wb");
        g[2][2] = fopen("piesa_S_270.bmp", "wb");

        g[3][0] = fopen("piesa_Z_90.bmp", "wb");
        g[3][1] = fopen("piesa_Z_180.bmp", "wb");
        g[3][2] = fopen("piesa_Z_270.bmp", "wb");

        g[4][0] = fopen("piesa_L_90.bmp", "wb");
        g[4][1] = fopen("piesa_L_180.bmp", "wb");
        g[4][2] = fopen("piesa_L_270.bmp", "wb");

        g[5][0] = fopen("piesa_J_90.bmp", "wb");
        g[5][1] = fopen("piesa_J_180.bmp", "wb");
        g[5][2] = fopen("piesa_J_270.bmp", "wb");

        g[6][0] = fopen("piesa_T_90.bmp", "wb");
        g[6][1] = fopen("piesa_T_180.bmp", "wb");
        g[6][2] = fopen("piesa_T_270.bmp", "wb");

        for(i = 0; i < 7; i++)
            for(j = 0; j < 3; j++)
            {
                creareImaginePiesa(P[i][j + 1], g[i][j]);
                fclose(g[i][j]);
            }
    }
//----------------- TASK 3 ----------------------
    if(!strcmp(argv[1], "3"))
    {
        culoare **tabla3;
        int H, W, n, coloana[50],
        sfarsit = 0;
        piesa mutare[50];
        char endl[2];

        FILE *task3, *input;
        input = fopen("cerinta3.in", "r");
        if(input == NULL)
        {
            printf("Eroare!\n");
            return -1;
        }

        fscanf(input, "%d", &n);
        fscanf(input, "%d", &H);
        fscanf(input, "%d", &W);
        fgets(endl, 2, input);
        H += 4;
        tabla3 = alocareMemorie(H, W);

        // Harta initiala
        hartaInitialaTask3(tabla3, H, W);

        sfarsit = 0;
        for(i = 0; i < n && !sfarsit; i++)
        {
            fscanf(input, "%c", &mutare[i].nume);

            fscanf(input, "%d", &mutare[i].rotatie);
            fscanf(input, "%d", &coloana[i]);
            fgets(endl, 2, input);

            // Identificarea piesei citite din fisier
            identificarePiesa(&mutare[i], P);

            // Coordonatele de start ale piesei
            mutare[i].coloana = coloana[i];
            mutare[i].linie = mutare[i].inaltime - 1;

            // Cat poate sa coboare piesa?
            coborarePiesa(&mutare[i], tabla3, H);

            // Plasarea piesei pe tabla cand nu mai poate sa coboare
            adaugarePiesaPeTabla(mutare[i], tabla3);

            // Am ajuns la sfarsit de joc?
            sfarsit = sfarsitJoc(tabla3, W);

            // Eliminarea liniilor complete
                for(i2 = 4; i2 < H; i2++)
                    if(linieCompleta(i2, tabla3, W))
                        eliminareLinie(i2, tabla3, W);

        }
        fclose(input);

        task3 = fopen("task3.bmp", "wb");
        creareImagine(tabla3, W, H, task3);
        fclose(task3);

        eliberareMemorie(tabla3, H);
    }
//----------------- TASK 4 ----------------------
    if(!strcmp(argv[1], "4"))
    {
        culoare **tabla4;
        int H, W,
        n, coloana[50],
        sfarsit = 0;
        piesa mutare[50];
        char endl[2];

        FILE *task4, *input, *inputBMP;

        inputBMP = fopen("cerinta4.bmp", "rb");
        if(inputBMP == NULL)
        {
            printf("Eroare!\n");
            return -1;
        }

        printf("Citirea e ok.\n");

        // Citirea dimensiunilor imaginii
        W= latimeTask4(inputBMP);
        H = inaltimeTask4(inputBMP);

        printf("Dimensiunile sunt ok.\n");
        
        // Citirea tablei de joc
        int padding = W % 4, offset = 54, k;
        int color[3];
        char aux[3];

        tabla4 = alocareMemorie(H / 10, W / 10);
        int L, C;

        for(L = H; L > 0; L -= 10)
        {
            for(C = 1; C <= W; C +=10)
            {
                fseek(inputBMP, offset, SEEK_SET);
                fgets(aux, 4, inputBMP);

                for(k = 0; k < 3; k++)
                    color[k] = (aux[k] + 256) % 256;

                i = (L - 1) / 10;
                j = C / 10;
               
                citireCuloare(&tabla4[i][j], color[2], color[1], color[0]);

                offset += 30;
            }

            C = 1;
            offset += 9*3*W + 10*padding;
        }

        // Dimensiunile tablei de joc
        W /= 10;
        H /= 10;
        fclose(inputBMP);

        input = fopen("cerinta4.in", "r");
        if(input == NULL)
        {
            printf("Eroare!\n");
            return -1;
        }

        // Citirea mutarilor si aplicarea pasilor de la task 3
        fscanf(input, "%d", &n);
        fgets(endl, 2, input);
        sfarsit = 0;

        for(i = 0; i < n && !sfarsit; i++)
        {
            fscanf(input, "%c", &mutare[i].nume);

            fscanf(input, "%d", &mutare[i].rotatie);
            fscanf(input, "%d", &coloana[i]);
            fgets(endl, 2, input);

            // Identificarea piesei citite din fisier
            identificarePiesa(&mutare[i], P);

            // Coordonatele de start ale piesei
            mutare[i].coloana = coloana[i];
            mutare[i].linie = mutare[i].inaltime - 1;

            // Cat poate sa coboare piesa?
            coborarePiesa(&mutare[i], tabla4, H);

            // Plasarea piesei pe tabla cand nu mai poate sa coboare
            adaugarePiesaPeTabla(mutare[i], tabla4);

            // Am ajuns la sfarsit de joc?
            sfarsit = sfarsitJoc(tabla4, W);

            // Eliminarea liniilor complete
                for(i2 = 4; i2 < H; i2++)
                    if(linieCompleta(i2, tabla4, W))
                        eliminareLinie(i2, tabla4, W);
        }
        fclose(input);

        task4 = fopen("task4.bmp", "wb");
        creareImagine(tabla4, W, H, task4);
        fclose(task4);

        eliberareMemorie(tabla4, H);
    }

// Eliberare de memorie
    for(k = 0; k < 7; k++)
        for(r = 0; r < 4; r++)
            eliberareMemorie
            (P[k][r].imagine, P[k][r].inaltime);

    return 0;
}
