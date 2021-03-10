#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Buga C. Bogdan - Andrei, grupa 312CB

int operatieValida(char *s)
{
    if(strcmp(s, "W") == 0 || strcmp(s, "w") == 0)
        return 1;
        
    if(strcmp(s, "C") == 0 || strcmp(s, "c") == 0)
        return 2;

    if(strcmp(s, "L") == 0 || strcmp(s, "l") == 0)
        return 3;

    if(strcmp(s, "R") == 0 || strcmp(s, "r") == 0)
        return 4;

    if(strcmp(s, "J") == 0 || strcmp(s, "j") == 0)
        return 5;

    if(strcmp(s, "P") == 0 || strcmp(s, "p") == 0)
        return 6;

    if(strcmp(s, "I") == 0 || strcmp(s, "i") == 0)
        return 7;

    if(strcmp(s, "O") == 0 || strcmp(s, "o") == 0)
        return 8;

    return 0;
}

int listaValida(char *s)
{
    if (strcmp(s, "n") == 0)
        return 1;
    if (strcmp(s, "a") == 0)
        return 2;
    if (strcmp(s, "A") == 0)
        return 3;
    if (strcmp(s, "b") == 0)
        return 4;    
    return 0;
}

void mutareDreapta(char* s, int nrSpatii)
{
    int k;
    int D = strlen(s) + nrSpatii;
    for(k = D; k >= nrSpatii; k--)
        s[k] = s[k - nrSpatii];
    for(k = nrSpatii - 1; k >= 0; k--)
        s[k] = ' ';
}

void aliniereStanga(char* s)
{
    int nrSpatii = 0, k;
    for(k = 0; s[k] == ' ' || s[k] == '\t'; k++)
        nrSpatii++;

    for(k = 0; k < strlen(s); k++)
        s[k] = s[k + nrSpatii];
    for(k = strlen(s) - 1; s[k] == ' ' || s[k] == '\t'; k--)
        s[k] = '\0';
}

int tipLinie(char s[1000][1000], int dim, int i)
{
    if(i == 0 || (strcmp(s[i-1], "\n") == 0 && strcmp(s[i], "\n")))
        return 1; // inceput de paragraf

    if(i == dim - 1 || (strcmp(s[i+1], "\n") == 0 && strcmp(s[i], "\n")))
        return 2; // sfarsit de paragraf

    if(strcmp(s[i], "\n") == 0)
        return -1; // linie goala 

    return 0; // linie obisnuita
}

int main(int argc, char *argv[])
{
    char buffer[1000],  // buffer folosit pentru citirea din fisier
    original[1000][1000], // textul original, linie cu linie
    rezultat[1000][1000], // textul obtinut dupa aplicarea operatiilor
    wrap[1000][1000]; 

    int liniiOriginal = 0, // numarul de linii din fisierul de intrare
    liniiRezultat = 0,   // numarul de linii din fisierul de iesire
    i, j, c, k, n, start[10], final[10],
    distanta[1000], indent, max[10], tab[10],
    nrComenzi = 0, nrArgumente[10],
    eroare = 0;

    char *p, 
    *comanda[10], *operatie[10], *argument[10][10],
    *tipLista[10], *caracterSpecial[10], *ordonare[10], 
    aux[1000];

    if (argc != 4) // numar invalid de argumente
    {
        fprintf(stderr,
        "Usage: %s operations_string input_file output_file\n",
        argv[0]);
        return -1;
    }

    // Deschiderea fisierului de intrare pentru citire
    FILE *input_file = fopen(argv[2], "r");

    if (input_file == NULL)
    {
        fprintf(stderr, "File \"%s\" not found\n", argv[2]);
        return -2;
    }

    // Citirea datelor in fisier linie cu linie
    while (fgets(buffer, 1000, input_file))
    {
        strcpy(original[liniiOriginal], buffer);
        liniiOriginal++;
    }
    fclose(input_file);


    // Separarea comenzilor
    p = strtok(argv[1], ",");
    while(p != NULL)
    {
        comanda[nrComenzi] = p;
        nrComenzi++;
        p = strtok(NULL, ",");
    }

    // Executam doar primele 10 comenzi daca avem mai mult de 10 comenzi
    if(nrComenzi > 10)
    {
        printf("Too many operations! Only the first 10 will be applied.\n");
        nrComenzi = 10;
    }

    // Verificarea comenzilor
    for(i = 0; i < nrComenzi && eroare == 0; i++)
    {
        // Initializarea rezultatului cu textul original
        for (c = 0; c < liniiOriginal; c++)
            strcpy(rezultat[c], original[c]);
        liniiRezultat = liniiOriginal;
        
        
        nrArgumente[i] = 0;
        p = strtok(comanda[i], " ");
        while(p != NULL)
        {
            argument[i][nrArgumente[i]] = p;
            p = strtok(NULL, " ");
            nrArgumente[i]++;
        }

        operatie[i] = argument[i][0];

        if(operatieValida(operatie[i]) == 0)
            eroare = 1; 
        
        // Wrap
        else if(operatieValida(operatie[i]) == 1)
        {
            if(nrArgumente[i] > 2)
                eroare = 1;
            else
            {
                max[i] = (int)atoi(argument[i][1]);
                for(c = 0; c < liniiRezultat; c++)
                {
                    p = strtok(rezultat[i], "\n");
                    if(p != NULL)
                    {
                        strcpy(aux, p);
                        p = strtok(aux, " ");
                        while(p != NULL)
                        {
                            if(strlen(p) > max[i])
                                {
                                    eroare = 2;
                                    break;
                                }
                            p = strtok(NULL, " ");
                        }
                    }
                }
            }
        }

        // Centrare, alinierile si justify
        else if(operatieValida(operatie[i]) >= 2
        && operatieValida(operatie[i]) <= 5)
        {
            start[i] = 0;
            final[i] = liniiRezultat;

            if(nrArgumente[i] > 3)
                {
                    eroare = 1;
                    break;
                }
            else if(nrArgumente[i] >= 2 && nrArgumente[i] <=3)
            {
                start[i] = (int)atoi(argument[i][1]);
                if(nrArgumente[i] == 2 && start[i] > final[i])
                    continue;
                if(nrArgumente[i] == 3)
                {
                    final[i] = (int)atoi(argument[i][2]);
                    if(final[i] > liniiRezultat)
                        final[i] = liniiRezultat;
                    if(start[i] > final[i] || start[i] < 0)
                    {
                        eroare = 1;
                        break;
                    }
                }
            }
        }

        // Paragrafe
        else if(operatieValida(operatie[i]) == 6)
        {
            start[i] = 0;
            final[i] = liniiRezultat;
            
            if(nrArgumente[i] > 4 || nrArgumente[i] < 2)
            {
                eroare = 1;
                break;
            }

            else
            {
                tab[i] = (int)atoi(argument[i][1]);
                if(nrArgumente[i] >= 3)
                {
                    start[i] = (int)atoi(argument[i][2]);
                    final[i] = liniiRezultat;
                    if(nrArgumente[i] == 3 && start[i] > final[i])
                        continue;
                    if(nrArgumente[i] == 4)
                    {
                        final[i] = (int)atoi(argument[i][3]);
                        if(final[i] > liniiRezultat)
                            final[i] = liniiRezultat;
                            
                        if(start[i] > final[i] || start[i] < 0)
                        {
                            eroare = 1;
                            break;
                        }
                    }
                }
            }
        }

        // Lista
        else if(operatieValida(operatie[i]) == 7)
        {
            start[i] = 0;
            final[i] = liniiRezultat;
            
            if(nrArgumente[i] > 5 || nrArgumente[i] < 3)
            {
                eroare = 1;
                break;
            }

            else
            {
                tipLista[i] = argument[i][1];
                caracterSpecial[i] = argument[i][2];

                if(listaValida(tipLista[i]) == 0)
                {
                    eroare = 1;
                    break;
                }

                if(strlen(caracterSpecial[i]) > 1)
                {
                    eroare = 1;
                    break;
                }
                    
                if(nrArgumente[i] >= 4)
                {
                    start[i] = (int)atoi(argument[i][3]);
                    if(nrArgumente[i] == 4 && start[i] > final[i])
                        continue;
                    
                    if(nrArgumente[i] == 5)
                    {
                        final[i] = (int)atoi(argument[i][4]);

                        if(final[i] > liniiRezultat)
                            final[i] = liniiRezultat;

                        if(start[i] > final[i] || start[i] < 0)
                        {
                            eroare = 1;
                            break;
                        }
                    }
                }
            }
        }
        
        // Lista ordonata
        else if(operatieValida(operatie[i]) == 8)
        {
            start[i] = 0;
            final[i] = liniiRezultat;
            if(nrArgumente[i] > 6 || nrArgumente[i] < 4)
            {
                eroare = 1;
                break;
            }

            else
            {
                tipLista[i] = argument[i][1];
                caracterSpecial[i] = argument[i][2];
                ordonare[i] = argument[i][3];
                
                if(listaValida(tipLista[i]) == 0)
                {
                    eroare = 1;
                    break;
                }

                if(strlen(caracterSpecial[i]) > 1)
                {
                    eroare = 1;
                    break;
                }

                if(strcmp(ordonare[i], "a") && strcmp(ordonare[i], "z"))
                {
                    eroare = 1;
                    break;
                }
                    
                if(nrArgumente[i] >= 5)
                {
                    start[i] = (int)atoi(argument[i][4]);
                    if(nrArgumente[i] == 5 && start[i] > final[i])
                        continue;
                    
                    if(nrArgumente[i] == 6)
                    {
                        final[i] = (int)atoi(argument[i][5]);
                        if(final[i] > liniiRezultat)
                            final[i] = liniiRezultat;
                            
                        if(start[i] > final[i] || start[i] < 0)
                        {   
                            eroare = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    if(eroare == 1)
    {
        printf("Invalid operation!\n");
        for (c = 0; c < liniiOriginal; c++)
            strcpy(rezultat[c], original[c]);
        liniiRezultat = liniiOriginal;
    }
    
    else if(eroare == 2)
    {
        printf("Cannot wrap!\n");
        for (c = 0; c < liniiOriginal; c++)
            strcpy(rezultat[c], original[c]);
        liniiRezultat = liniiOriginal;
    }
    
    else if(eroare == 0)// Executarea comenzilor
        for(i = 0; i < nrComenzi; i++)
        {
            for (c = 0; c < liniiOriginal; c++)
                strcpy(rezultat[c], original[c]);
            liniiRezultat = liniiOriginal;
            
            //Wrap
            if(operatieValida(operatie[i]) == 1)
            {
                n=0; // numarul nou de linii
                for(c = 0; c < liniiRezultat; c++)
                {
                    if(tipLinie(rezultat, liniiRezultat, c) >= 0)
                    {
                        p = strtok(rezultat[c], "\n");
                        strcpy(aux, p);
                        p = strtok(aux, " ");
                        
                        if(tipLinie(rezultat, liniiRezultat, c) == 1)
                            for(j = 0; rezultat[c][j] == ' '; j++)
                                strcat(wrap[n], " ");
                        
                        while(p != NULL)
                        {
                            if(strlen(wrap[n]) + strlen(p) <= max[i])
                            {
                                strcat(wrap[n], p);
                                strcat(wrap[n], " ");
                            }
                            else
                            {
                                strcat(wrap[n], "\n");
                                n++;
                                strcpy(wrap[n], "");
                                
                                if(strlen(p) < max[i])
                                {
                                    strcat(wrap[n], p);
                                    strcat(wrap[n], " ");                                    
                                }
                            }
                            p = strtok(NULL, " ");   
                        }
                    }
                    
                    else
                    {
                        strcpy(wrap[n + 1], "\n");
                        n += 2;
                        strcpy(wrap[n], "");
                    }
                }
            

                liniiRezultat = n + 1;
                for(c = 0; c < liniiRezultat; c++)
                    strcpy(rezultat[c], wrap[c]);
            }
            // Centrarea
            if(operatieValida(operatie[i]) == 2)
            {
                //Algoritm de determinare a celei mai lungi linii din text
                max[i] = strlen(rezultat[0]);
                for(c = 0; c < liniiRezultat; c++)
                    if (max[i] <= strlen(rezultat[c]))
                        max[i] = strlen(rezultat[c]);
                    
                for(c = start[i]; c <= final[i]; c++)
                {
                        distanta[c] = max[i] - strlen(rezultat[c]);
                        if(distanta[c] % 2 == 0)
                            indent = distanta[c] / 2;
                        else
                            indent = distanta[c] / 2 + 1;
                    
                        if(tipLinie(rezultat, liniiRezultat, c) >= 0)
                            mutareDreapta(rezultat[c], indent);
                }
            }
        
            // Alinierea la stanga
            else if(operatieValida(operatie[i]) == 3)
            {
                for(c = start[i]; c <= final[i]; c++)
                    aliniereStanga(rezultat[c]);
            }
            
            // Alinierea la dreapta
            else if(operatieValida(operatie[i]) == 4)
            {
                //Algoritm de determinare a celei mai lungi linii din text
                max[i] = strlen(rezultat[0]);
                for(c = 0; c < liniiRezultat; c++)
                    if (max[i] <= strlen(rezultat[c]))
                        max[i] = strlen(rezultat[c]);

                for(c = start[i]; c <= final[i]; c++)
                {
                    distanta[c] = max[i] - strlen(rezultat[c]);
                    if(tipLinie(rezultat, liniiRezultat, c) >= 0)
                        mutareDreapta(rezultat[c], distanta[c]);
                }
            }
            
            // Justify
            else if(operatieValida(operatie[i]) == 5)
            {
                if(final[i] == liniiRezultat)
                    final[i]--;
                for(c = start[i]; c <= final[i]; c++)
                {
                        aliniereStanga(rezultat[c]);

                        max[i] = strlen(rezultat[0]);
                        for(j = 0; j < liniiRezultat; j++)
                            if (max[i] <= strlen(rezultat[j]))
                                max[i] = strlen(rezultat[j]);

                        if(tipLinie(rezultat, liniiRezultat, c) >= 0 
                        && tipLinie(rezultat, liniiRezultat, c) < 2)
                            while(strlen(rezultat[c]) < max[i])
                                for(j = 0; strlen(rezultat[c]) < max[i]
                                && j < strlen(rezultat[c]); j++)
                                    {
                                        if(rezultat[c][j] == ' ' 
                                        && rezultat[c][j + 1] != ' ')
                                        {                                        
                                            for(k = max[i]; k >= j + 1; k--)
                                                rezultat[c][k] 
                                                = rezultat[c][k - 1];
                                            rezultat[c][j + 1] = ' ';
                                            j++;
                                        }
                                        if(j == strlen(rezultat[c]) - 1 
                                        && strlen(rezultat[c]) < max[i])
                                            j = 0;                                
                                    }
                        else
                            continue;
                }               
            }
            
            // Paragrafe
            else if(operatieValida(operatie[i]) == 6)
            {
                for(c = start[i]; c <= final[i]; c++)
                    if(tipLinie(rezultat, liniiRezultat, c) == 1)
                        mutareDreapta(rezultat[c], tab[i]);             
            }
            
            // Liste
            else if(operatieValida(operatie[i]) == 7)
            {
                for(c = start[i]; c <= final[i]; c++)
                    aliniereStanga(rezultat[c]);


                if(listaValida(tipLista[i]) == 4)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        mutareDreapta(rezultat[c], 2);
                        rezultat[c][1] = ' ';
                        rezultat[c][0] = caracterSpecial[i][0];
                    }

                else if(listaValida(tipLista[i]) == 1)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        if(c - start[i] < 9)
                        {
                            mutareDreapta(rezultat[c], 3);
                            rezultat[c][2] = ' ';
                            rezultat[c][1] = caracterSpecial[i][0];
                            rezultat[c][0] = '1' + (c - start[i]);
                        }
                        
                        else if(c - start[i] >= 9 && c - start[i] < 100)
                        {
                            mutareDreapta(rezultat[c], 4);
                            rezultat[c][3] = ' ';
                            rezultat[c][2] = caracterSpecial[i][0];
                            rezultat[c][1] = '0' + (c - start[i] + 1) % 10;
                            rezultat[c][0] = (c - start[i] + 1) / 10 + 48;
                        }
                    }

                else if(listaValida(tipLista[i]) == 2)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        mutareDreapta(rezultat[c], 3);
                        rezultat[c][2] = ' ';
                        rezultat[c][1] = caracterSpecial[i][0];
                        rezultat[c][0] = 'a' + (c - start[i]);
                    }

                else if(listaValida(tipLista[i]) == 3)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        mutareDreapta(rezultat[c], 3);
                        rezultat[c][2] = ' ';
                        rezultat[c][1] = caracterSpecial[i][0];
                        rezultat[c][0] = 'A' + (c - start[i]);
                    }
            }
            
            // Liste ordonate
            else if(operatieValida(operatie[i]) == 8)
            {
                if(strcmp(ordonare[i], "a") == 0)
                {
                    if(final[i] == liniiRezultat)
                        final[i]--;
                    for(c = final[i]; c > start[i]; c--)
                        for(j = c - 1; j >= start[i]; j--)
                            if (strcmp(rezultat[c], rezultat[j]) < 0)
                            {
                                strcpy(aux, rezultat[c]);
                                strcpy(rezultat[c], rezultat[j]);
                                strcpy(rezultat[j], aux);
                            }
                }    
                else if(strcmp(ordonare[i], "z") == 0)
                {
                    for(c = final[i]; c > start[i]; c--)
                        for(j = c - 1; j >= start[i]; j--)
                            if (strcmp(rezultat[c], rezultat[j]) > 0)
                            {
                                strcpy(aux, rezultat[c]);
                                strcpy(rezultat[c], rezultat[j]);
                                strcpy(rezultat[j], aux);
                            }
                }
            
                for(c = start[i]; c <= final[i]; c++)
                    aliniereStanga(rezultat[c]);

                if(listaValida(tipLista[i]) == 4)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        mutareDreapta(rezultat[c], 2);
                        rezultat[c][1] = ' ';
                        rezultat[c][0] = caracterSpecial[i][0];
                    }

                else if(listaValida(tipLista[i]) == 1)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        if(c - start[i] < 9)
                        {
                            mutareDreapta(rezultat[c], 3);
                            rezultat[c][2] = ' ';
                            rezultat[c][1] = caracterSpecial[i][0];
                            rezultat[c][0] = '1' + (c - start[i]);
                        }
                        
                        else if(c - start[i] >= 9 && c - start[i] < 100)
                        {
                            mutareDreapta(rezultat[c], 4);
                            rezultat[c][3] = ' ';
                            rezultat[c][2] = caracterSpecial[i][0];
                            rezultat[c][1] = '0' + (c - start[i] + 1) % 10;
                            rezultat[c][0] = (c - start[i] + 1) / 10 + 48;
                        }
                    }

                else if(listaValida(tipLista[i]) == 2)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        mutareDreapta(rezultat[c], 3);
                        rezultat[c][2] = ' ';
                        rezultat[c][1] = caracterSpecial[i][0];
                        rezultat[c][0] = 'a' + (c - start[i]);
                    }

                else if(listaValida(tipLista[i]) == 3)
                    for(c = start[i]; c <= final[i]; c++)
                    {
                        mutareDreapta(rezultat[c], 3);
                        rezultat[c][2] = ' ';
                        rezultat[c][1] = caracterSpecial[i][0];
                        rezultat[c][0] = 'A' + (c - start[i]);
                    }
            }
        
        // Inlaturarea trailing whitespace-urilor
        for(c = 0; c < liniiRezultat; c++)
        {
                int index;
                if(c == liniiRezultat)
                    index = strlen(rezultat[c]) - 1;
                else
                    index = strlen(rezultat[c]) - 2;

                for(j = index; rezultat[c][j] == ' ' 
                || rezultat[c][j] == '\t'; j--);

                if(c == liniiRezultat)
                    rezultat[c][j + 1] = '\0';
                else
                {
                    rezultat[c][ j+ 1] = '\n';
                    rezultat[c][j + 2] = '\0';
                }
        }

    // Actualizarea originalului in cazul in care executam cel putin 2 comenzi
        for (c = 0; c < liniiRezultat; c++)
            strcpy(original[c], rezultat[c]);
        liniiOriginal = liniiRezultat;
        }

    // Deschiderea fisierului de iesire pentru scriere
    FILE *output_file = fopen(argv[3], "w");

    if (output_file == NULL)
    {
        fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
        return -2;
    }

    // Scrierea rezultatului in fisierul de iesire
    for (i = 0; i < liniiRezultat; i++)
        fputs(rezultat[i], output_file);

    fclose(output_file);
    return 0;
}