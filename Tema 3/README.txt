Bogdan - Andrei Buga, grupa 312 CB

----------------------------------- HEADERE ----------------------------------


In headerul task1_si_task2.h am definit structurile culoare: 3 variabile
intregi pentru rosu, verde si albastru si piesa, definita prin: latime,
inaltime, rotatie nume, linia si coloana pe care se afla piesa pe tabla 
de joc, reprezentarea piesei pe o imagine 4 X 4 si inaltimea fiecarei 
coloane a piesei.

Functiile din primul header:

* citireCuloare(color, R, G, B)
	- atribuie culorii "color" R la rosu, G la verde si B la albastru

* alocareMemorie(L, C)
	- returneaza o matrice de culori alocata dinamic cu L linii si 
	C coloane

* eliberareMemorie(imagine, L)
	- elibereaza memoria matricei de culori "imagine" cu L randuri

* Header(latime, inaltime, output)
	- creaza File Header-ul si Info Header-ul unei imagini de dimensiuni
	"latime" * 10 si "inaltime" * 10 in fisierul "output"

* creareImagine(tabla, W, H, output)
	- creaza un header de bitmap pentru o imagine de dimensiuni 10 * H	
	si 10 * W cu  apelul functiei Header, descrisa mai sus
	- genereaza imaginea bitmap a "tablei" de culori de dimensiuni H si 
	W in fisierul output 

* creareImaginePiesa(piesa, output)
	- genereaza imaginea piesei "piesa" (inconjurata de un chenar alb) 
	in fisierul "output"
	- la inceput, trebuie sa aplicam 
	Header(latime + 2, inaltime + 2, output),
	deoarece trebuie incluse si marginile chenarului
	
	- dupa alocarea dinamica a unei matrice de culori "imagine" de 
	dimensiuni piesa.inaltime + 2 si piesa.latime + 2, am setat 
	aceasta matrice astfel:
		imagine[i][j] = - alb,
				i in multimea {0, piesa.inaltime + 1},
				j in multimea {0, piesa.latime + 1}.

				- piesa.imagine[i-1][j-1],
				i in multimea [1, piesa.inaltime],
				j in multimea [1, piesa.latime].
	- am generat imaginea bitmap a acestei matrice de culori, apoi am
	eliberat memoria alocata dinamic.

* comparareCuloare(A, B)
	- 0, in cazul in care culorile "A" si "B" sunt identice
	- 1, in caz contrar

* SpatiuLiber(A)
	- 1, in situatia culoarea "A" este fie alba, fie neagra
	- 0 , altfel

	
Functiile din "task3_si_task4.h":

* hartaInitialaTask3(tabla, H, W)
	- intializeaza tabla de joc de dimensiuni "H" * "W" astfel:
		- primele 4 linii sunt complet albe
		- celelalte linii sunt complet negre
		
* identificarePiesa(p, P[7][4])
	- identifica piesa "p" din setul (matricea) de piese "P" 
	
* coborarePiesa(p, tabla, H)
	- dupa setarea coordonatelor initiale ale piesei "p" (acestea trebuie
	setate in main), piesa coboara cate o linie cat timp are spatiu liber
	sub fiecare coloana pe care se intinde piesa sau pana cand ajunge pe
	ultima linie
	
* adaugarePiesaPeTabla(p, tabla)
	- patraticile care nu sunt albe sau negre vor fi adaugate pe tabla de 
	joc dupa efectuarea functiei precedente

* sfarsitJoc(tabla, W)
	- 1, daca exista cel putin o patratica care nu este alba in primele 
	4 linii ale tablei de joc, caz in care jocul nu mai poate continua
	- 0, in caz contrar

* linieCompleta(i, tabla, W)
	- 0, daca exista cel putin un spatiu liber pe linia i a unei table cu 
	W coloane
	- 1, in caz contrar
	
* eliminareLinie(i, W)
	- coboara toate liniile din partea neagra a tablei de joc de la linia
 	in sus cu o linie
	
* latimeTask4(input)
	- extrage latimea imaginii BitMap a fisierului input
	(de la offset-ul 18)

* inaltimeTask4(input)
	- extrage inaltimea imaginii BitMap a fisierului input
	(de la offset-ul 22)

------------------------------------- MAIN -----------------------------------

Dupa definirea culorilor si a celor 28 de piese intr-o matrice de 7 x 4 de tip
"piesa" (tip definit in primul header), am inceput rezolvarea celor 4
task-uri.

Cum au fost definite piesele:
P[i][j]
i = 0 -> I
i = 1 -> O
i = 2 -> S
i = 3 -> Z
i = 4 -> L
i = 5 -> J
i = 6 -> T

j = 0 -> Piesa rotita la 0 grade
j = 1 -> Piesa rotita la 90 grade
j = 2 -> Piesa rotita la 180 grade
j = 3 -> Piesa rotita la 270 grade


Dupa definirea dimensiunilor fiecarei piese, am alocat dinamic imaginea fiecarei
piese in functie de dimensiunile acesteia si am atribuit valorile necesare
fiecarui element al matricei de pixeli. Am tinut cont de faptul ca la finalul
programului memoria alocata dinamic trebuie eliberata.

Task 1: In fisierele cerute am creat imagini BitMap pentru P[i][0],
i fiind in intervalul [0, 7).

Task 2: In fisierele cerute am creat imagini BitMap pentru P[i][j],
i fiind in intervalul [0, 7), iar j in intervalul [1, 3].

La task-urile 3 si 4, dupa initializarea tablei de joc, am efectuat
urmatorii pasi:

1) Am citit numarul de mutari (si dimensiunile partii negre pentru task-ul 3).

2) 	a) La task 3:
		Dupa citirea dimensiunilor si alocarea dinamica a memoriei
	tablei de joc, am initializat tabla de joc cu functia
	hartaInitialaTask3.
	
	b) La task 4:
		Dupa citirea din fisierul cerinta4.bmp a dimensiunilor imaginii
	tablei de joc, am alocat dinamic tabla de joc si am inceput atribuirea 
	culorilor de la ultima linie la	prima, de la stanga la dreapta. Cand am
	ajuns la sfarsitul liniei, trecem la urmatoarea linie si incepem de la
	prima coloana a acesteia. Dupa citirea tablei de joc, tinem cont ca o 
	patratica are dimensiunea 10 x 10 si impartim dimensiunile obtinute 
	la 10.
	
3) Am citit numele si rotatia piesei, precum si coloana pe care asezam piesa.

4) Cautam piesa in matricea P[7][4] setata la inceputul programului cu functia
"identificarePiesa".

5) Coboram piesa citita prin intermediul functiei "coborarePiesa".	

6) Dupa ce am coborat piesa, actualizam tabla de joc cu pozitia finala a 
piesei ("adaugarePiesaPeTabla").

7) Verificam daca am ajuns la sfarsitul jocului ("sfarsitJoc").

8) Daca avem o linie din intervalul [4, H - 1] ce trebuie eliminata, aceasta
va fi eliminata ("eliminareLinie").

9) Dupa efecctuarea tuturor mutarilor posibile, transpunem tabla de joc
intr-o imagine BitMap denumita "task3.bmp" (pentru task-ul 3) sau 
"task4.bmp" (pentru task-ul 4).
