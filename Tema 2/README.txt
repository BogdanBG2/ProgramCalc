Buga C. Bogdan - Andrei, grupa 312CB

Pentru inceput, am creat cateva functii:
1) operatieValida - verifica valabilitatea operatiei s si ce fel de operatie
este:
	* 1 - Wrap (W / w)
	* 2 - Center (C / c)
	* 3 - Align left (L / l)
	* 4 - Align Right (R / r)
	* 5 - Justify (J / j)
	* 6 - Paragraph (P / p)
	* 7 - List (I / i)
	* 8 - Ordered list (O / o)
	* 0 - operatie invalida
2) listaValida - verifica valabilitatea unei liste s si ce fel de lista este:
 	* 1 - n (numerica)
	* 2 - a (alfabetica cu litere mici)
	* 3 - A (alfabetica cu litere mari)
	* 4 - B (cu un singur caracter special)
	* 0 - lista invalida
3) mutareDreapta - muta sirul s cu "nrSpatii" spatii la dreapta
4) aliniereStanga - aliniaza sirul s la stanga
5) tipLinie - verifica ce fel de linie este linia i din textul s[1000][1000]
cu "dim" randuri: 
	*1 - inceput de paragraf
	*2 - sfarsit de paragraf 
	*0 - linie obisnuita
	*-1 - linie goala

In functia main, am folosit urmatoarele variabile:

VARIABILE DE TIP CHAR:
buffer[1000] - pentru citirea din fisier
original[1000][1000] - textul original, linie cu linie
rezultat[1000][1000] - textul obtinut dupa aplicarea operatiilor
p - pentru separarea comenzilor si a argumentelor
comanda[10] - pentru retinerea comenzilor
operatie[10] - pentru retinerea operatiilor
argument[10][10] - pentru retinerea argumentelor fiecarei comenzi
tipLista[10] - pentru retinerea tipului de lista a unei comenzi (pentru I si O)
caracterSpecial[10] - pentru retinerea caracterului special (pentru I si O)
ordonare[10] - pentru retinerea felului in care ordonam liniile din fisier
(Pentru O)
aux - pentru retinerea unor linii (pentru W si O)

VARIABILE DE TIP INT:
liniiOriginal - numarul de linii din fisierul de intrare
liniiRezultat - numarul de linii din fisierul de iesire
i - indice de parcurgere a comenzilor
c - indice de parcurgere a liniilor
j si k - indici de pargurgere a caracterelor dintr-un sir de caractere 
n - numarul de randuri (pentru W)
start[10] - linia de la care se incepe efectuarea operatiei
final[10] - linia pana la care are loc efectuarea operatiei
distanta[1000] - distanta de la capatul unei linii la capatul celei mai 
lungi linii din fisier (pentru C)
indent - cu cat trebuie mutata piesa la dreapta (pentru C)
max[10] - lungimea celei mai lungi linii din text (pentru C, R si J) sau
lungimea maxima a unei linii (pentru W)
tab[10] - lungimea unui tab (pentru P)
nrComenzi - numarul de comenzi
nrArgumente[10] - numarul de argumente al fiecarei comenzi
eroare - 0 daca toate operatiile sunt valide, 1 daca avem macar o operatie
invalida, 2 daca nu poate face wrap la un cuvant


Dupa citirea textului rand cu rand din fisierul de intrare, retinem comenzile
separate prin virgula si argumentele fiecarei comenzi, separate printr-unul sau
mai multe spatii. Apoi verificam validitatea sirului de operatii. Daca avem
macar o comanda invalida, textul de iesire va fi acelasi cu cel de intrare.

In cazul in care se pot efectua toate comenzile, acestea vor fi efectuate in
ordinea in care apar in linia de comanda a terminalului:

1) Wrap - Luam textul cuvant cu cuvant. Daca lungimea sirului rezultat, 
impreuna cu lungimea cuvantului pe care vrem sa-l adaugam in sir, este mai mica
sau egala cu lungimea maxima posibila, atunci cuvantul este adaugat in sir. 
Altfel, este trecut pe randul urmator si n creste cu 1. 
Daca o linie din sirul original este goala, n creste cu 2, iar linia n-1 este 
goala.


2) Centrare - Mutam fiecare rand din intervalul [start,final]
la dreapta cu jumatate din distanta dintre 
lungimea randului respectiv si lungimea celui mai lung rand din text.

3) Aliniere la stanga - Mutam la stanga din intervalul [start,final] fiecare 
rand care incepe cu cel putin un spatiu aplicand functia definita la inceputul
programului.

4) Aliniere la dreapta - Mutam fiecare rand din intervalul [start,final]
la dreapta cu distanta dintre lungimea randului respectiv si lungimea 
celui mai lung rand din text.

5) Justify - Aliniem la stanga fiecare linie din intervalul [start,final] si
adaugam spatii intre spatii si cuvinte pana cand lungimea randului prelucrat
devine egala cu lungimea celei mai lungi linii din tot textul.

6) Paragrafe - Mutam la dreapta cu "tab" spatii fiecare rand din intervalul 
[start,final] care are inaintea sa un rand gol.

7) Liste - Dupa alinierea la stanga a randurilor din intervalul [start,final],
am adaugat, in functie de tipul de lista, numere sau litere si caractere 
speciale la inceputul fiecarui rand din intervalul mentionat mai devreme.

8) Liste ordonate - Analog ca la liste, cu deosebirea ca randurile din intervalul 
[start,final] au fost sortate lexicografic(A-Z: "a" sau Z-A: "z") inainte de 
alinierea la stanga.

Dupa efectuarea operatiei, am inlaturat trailing whitespace-urile de pe 
fiecare rand, apoi am actualizat originalul pentru a putea efectua urmatoarele
operatii.

La finalul programului, se va afisa in fisierul de iesire textul rezultat in 
urma efectuarii tuturor operatiilor.
