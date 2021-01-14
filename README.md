# Printf function implementation
Functia "iocla_printf" simuleaza comportamentul functiei printf din biblioteca
standard C. In implementarea acesteia au fost construite multiple functii ajutatoare:
* `print_int` -> Functia afiseaza un element de tip "int". In cazul unui element negativ
	functia afiseaza caracterul '-', iar apoi este folosita valoarea absoluta a
	numarului dat. In continuare, elementul este inversat pentru a putea fi 
	transformat in string si apoi afisat cu ajutorul functiilor "auxiliary_print"
	si "write_stdout". La sfarsit este returnat numarul de caractere afisate "size".
* `print_unsigint` -> Functia afiseaza un element de tip "unsigned int". Comportamentul 
	functiei este acelasi ca si al functiei "print_int", diferenta fiind in faptul 
	ca numarul primit ca parametru este mereu pozitiv, deci nu se mai verifica daca
	este negativ. La sfarsit este returnat numarul de caractere afisate "size".
* `reverse` -> Functie ajutatoare ce returneaza inversul unui string primit ca parametru.
* `print_hexa` -> Functia afiseaza un element de tip "int" in format hexazecimal. Este creat
	un vector de caractere cu valorile posibile din sistemul hexazecimal, iar apoi
	numarul dat este transformat in baza 16 prin impartiri repetate. Este folosita
	functia ajutatoare "reverse" pentru a inversa string-ul creat, fiind apoi
	afisat. La sfarsit este returnat numarul de caractere afisate "size".
* `print_char` -> Functia afiseaza un element de tip "char" si returneaza 1.
* `iocla_printf` -> a fost folosita o implementare cu numar
variabil de parametri. Este parcurs sirul de caractere si sunt afisate caracterele 
exceptand '%', la aparitia acestuia fiind verificata tipul de variabila ce urmeaza cu
ajutorul unui switch. In final este returnat numarul total de caractere afisate.
	
