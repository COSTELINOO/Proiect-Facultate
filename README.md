Tutorial (pentru Code::Blocks, e posibil ca pe alte compilatoare sa nu functioneze conform asteptarilor)


Pasul 1: Instalarea compilatorului

-> Descarcarcati compilatorul Code::Blocks de pe urmatorul link:

https://sourceforge.net/projects/codeblocks/



Pasul 2: Descarcare fisiere

-> Descarcati(apasati click stanga pe: "Code->Download ZIP") si dezarhivati directorul principal

-> Pasul 2.1: Descarcati fisierul "MinGW" (click stanga pe "MinGW")

-> Pasul 2.2: Apasati click stanga pe "Download raw file" 

*deoarece fisierul "MinGW" este destul de mare( aproximativ 150 MB, peste limita de 100 MB, acesta trebuie descarcat separat de directorul principal,acest lucru exemplicat in cei doi pasi de mai sus)

*in cazul unor neclaritati, am atasat in directorul "Poze_tutorial_config" 2 poze ajutatoare pentru cei 2 pasi de mai sus(2.1, 2.2) cu nume corespunzatoare fiecarui pas

-> Dezarhivati fisierul "MinGW"(descarcat conform celor 2 pasi de mai sus, nu cel din directorul principal "Proiect-Facultate-master", caci o sa rezulte un mesaj de tipul "Fisier invalid") si puneti-l intr-o locatie accesibila(la mine se afla in "C:", unde vedeti in tutorial "C:\MinGW", o sa inlocuiti cu "locatie_MinGw\MinGW"; spre exemplu daca puneti directorul "MinGW" pe desktop, unde o sa am eu in tutorial "C:\MinGW", dumneavoastra o sa puneti: "C:\Desktop\MinGW")

*daca aveti configurata biblioteca: "graphics.h" puteti sari direct la pasul 4, fara a mai dezarhiva directorul: "MinGW" 




Pasul 3: Configurarea Compilatorului

-> Deschideti aplicatia Code::Blocks

->Pasul 3.1: Apasati click stanga pe "Settings"

->Pasul 3.2: Apasati click stanga pe: "Compiler"

->Pasul 3.3: Apasati pe: "Linker settings"

->Pasul 3.4: Apasati pe add si puneti locatia fisierului urmata de "\lib\libbgi.a" (Exemple:"C:\Desktop\MinGW\lib\libbgi.a","C:\MinGW\lib\libbgi.a","locatie_MinGW\lib\libbgi.a")

->Pasul 3.5: Copiati urmatorul text: "-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32" si il lipiti in: "Other linker options"

->Pasul 3.6: Apasati pe "Toolchain executables"

->Pasul 3.7: In "Compiler's installation directory" puneti calea catre directorul "MinGW"(in cazul meu, calea este: "C:\MinGW")

->Pasul 3.8: Apasati pe "Ok"

->Observatie:	-> In cazul unor neclaritati, am atasat in directorul "Poze_tutorial_config" cateva poze ajutatoare pentru cei 8 pasi de mai sus(3.1-3.8) cu nume corespunzatoare fiecarui pas


Pasul 4: Compilare cod

-> Deschide directorul "Source"

->Apasati click dreapta pe "main.cpp"

->Apasati pe: "Open With"

->Apasati pe: "Code::Blocks IDE"

->Apasati tasta "F9" pentru a compila codul si a rula aplicatia


*Daca sunt neclaritati sau erori va rog sa ma contactati pe adresa de mail: "costelarseni13@gmail.com"

