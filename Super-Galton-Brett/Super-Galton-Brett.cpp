// Super-Galton-Brett.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.

// benoetigte Bibliotheken hinzufuegen
#include <conio.h>
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
// Intialisuerung für Random-Generator
#include <time.h> 

// Namespace Angabe um cout zu nutzen
using namespace std;

// Globale Variablen
// Sprache (1 = deutsch)
int aktuelleSprache = 1;
// Kugel:
char alleKugelZeichen[4] = { '*', '+', '#', ':' };
int akteullesKugelZeichen = 0;
// Zeilen und Spalten
int zeilen = 3;
int spalten = 2 * zeilen + 1;
// Deklaration für die Wege (werden erst bei Aufruf von "generiereWeg()" initialisiert)
// 2-Dimensionales Array (Größe wird dynamisch festgelegt, daher ** -> Pointer of Pointer)
int** weg; 

/* Funktion: generiereWeg()
 * generiert die Wege für die vier Wuerfe.
 */
int** generiereWeg() {
	// 1. Dimension
	int** lokalWeg = new int*[4];
	// Grundinitalisierung für 2. Dimension 
	for (int i = 0; i < 4; ++i) {
		lokalWeg[i] = new int[zeilen - 1];
	}

	// Random-Geneerator neu-Initialisieren
	srand(time(NULL));

	// befüllen der wege kann losgehen!
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < zeilen - 1; j++)
		{
			// Gerade oder ungerade, bzw. 1 oder 0, bzw. links oder rechts
			lokalWeg[i][j] = rand() % 2;
		}
	}

	// gebe wege zurück
	return lokalWeg;
}

// akteulle Sprache:
// 0 = e = englisch
// 1 = d = deutsch
void getText(string sprachvariable) {
	// switch-case wäre effizienter!!!
	// ersteer versuch mit switch kam zu fehler.
	if (sprachvariable == "neues_brett") {
		// unterschiedung deutsch/englisch
		if (aktuelleSprache == 0) {
			cout << "create new board";
		}
		if (aktuelleSprache == 1) {
			cout << "neues Brett erstellen";
		}
		// return, damit weitere if-bloecke vermieden werden.
		return;
	}
	if (sprachvariable == "neuer_wurf") {

		if (aktuelleSprache == 0) {
			cout << "new trough";
		}
		if (aktuelleSprache == 1) {
			cout << "neuer Wurf";
		}
		return;
	}
	if (sprachvariable == "loesche_wuerfe") {
		if (aktuelleSprache == 0) {
			cout << "delete all trouhgs";
		}
		if (aktuelleSprache == 1) {
			cout << "loesche alle Wuerfe";
		}
		return;
	}
	if (sprachvariable == "brett_anzeigen") {
		if (aktuelleSprache == 0) {
			cout << "show board";
		}
		if (aktuelleSprache == 1) {
			cout << "Brett anzeigen";
		}
		return;
	}
	if (sprachvariable == "programm_schliessen") {
		if (aktuelleSprache == 0) {
			cout << "stop (close program)";
		}
		if (aktuelleSprache == 1) {
			cout << "Haaaaaalt Stop! (Schliesst das Programm)";
		}
		return;
	}
	if (sprachvariable == "anzahl_zeilen") {
		if (aktuelleSprache == 0) {
			cout << "amount of rows ";
		}
		if (aktuelleSprache == 1) {
			cout << "Anzahl der Zeilen: ";
		}
		return;
	}
	if (sprachvariable == "fehleingabe") {
		if (aktuelleSprache == 0) {
			cout << "wrong format";
		}
		if (aktuelleSprache == 1) {
			cout << "ungueltige eingabe";
		}
		return;
	}
	if (sprachvariable == "wurflimit_erreicht") {
		if (aktuelleSprache == 0) {
			cout << "trough limit succeeded";
		}
		if (aktuelleSprache == 1) {
			cout << "Wurflimit erreicht";
		}
		return;
	}
	if (sprachvariable == "auswahl") {
		if (aktuelleSprache == 0) {
			cout << "selection: ";
		}
		if (aktuelleSprache == 1) {
			cout << "Auswahl: ";
		}
		return;
	}
}

// funktion erstelle brett
// Parameter: Zeilen und Spalten
char** erstelleBrett(int zeilen, int spalten) {
	// reset Kugelzeichen-Posiotn
	akteullesKugelZeichen = 0;

	char** brett = new char*[zeilen];
	for (int i = 0; i < zeilen; ++i) {
		brett[i] = new char[spalten];
	}
	// äquivalent zaheler galton brett (ohne super!)
	int index = 0;

	int leere = zeilen - 1;
	// schleife über die zeilen!
	// ich auf einem array arbeite -> Index bei 0!
	for (int zeile = 0; zeile < zeilen; zeile++) {
		// einfügen der leeren felder , heißt leerzeichen!!!
		for (int leer = 1; leer <= leere; leer++) {
			brett[zeile][index] = '-'; // zum sehen ein - oder etwas anderes
			index++;
		}
		// Gatter einfügen
		for (int gate = 0; gate < zeilen - leere; gate++) {
			// nach jedem zeichen indexer hochzaehlen!
			brett[zeile][index] = '|';
			index++;
			brett[zeile][index] = ' ';
			index++;

		}
		brett[zeile][index] = '|';
		index++;
		// initialwerte die char setzt überschreiben
		for (int leer = 1; leer <= leere; leer++) {
			brett[zeile][index] = '-'; // wenn man des nicht macht kann es passieren, das da zb ein = steht!
			index++;
		}
		// neue Zeile, neues Glueck
		index = 0;
		// analog leere = leere -1 "Immer eins weniger" als davor (zeile)
		leere--;
	}

	//generie doch gleich mal den weg!!!
	// jedesBrett bekommt neuen weg
	weg = generiereWeg();
	// return brett!
	return brett;
}

// funktion drucke Brett
// Paramter: das Brett
void druckeBrett(char** brett) {
	// doppelete Schelife über Brett
	for (int i = 0; i < zeilen; i++) {
		for (int j = 0; j < spalten; j++) {
			cout << brett[i][j];	
		}
		// neue Zeile!!!
		cout << endl;
	}
}


// Funktion: druckeWeg
// gibt die Wege aus. (dient nur zum uberprüfen, quasi debug mode)
void druckeWeg(int** weg) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < zeilen - 1; j++)
		{
			if (weg[i][j] == 0) {
				cout << "l";
			}

			if (weg[i][j] == 1) {
				cout << "r";
			}

			if (j != zeilen - 2) {
				cout << "-";
			}
		}
		cout << endl;
	}
}

// Funktion: loescheBrett
// Paramter Brett
// char** = 2-Dim-Array
// & vor dem Parameter bedeutet call-by-ref, d.h. ich maniuliere die Daten auch nach aussen
void loescheBrett(char** &brett) {
	brett = erstelleBrett(zeilen, spalten);
	// zuruecksetzen der "Laufvariable" fuer das Kugelzeichen
	// sonst sagt das Programm bei neuem Wurf sofort "Limit erreicht"
	akteullesKugelZeichen = 0;


}

// Funktion: wegEinfuegen
// Paramter
void wegEinfuegen(char** &brett, int** weg) {
	// initlaisierung für die Mitte, INDEX!!!
	int positionKugel = zeilen;
	// aktueles zeichen hoeln
	char zeichen = alleKugelZeichen[akteullesKugelZeichen];

	if (akteullesKugelZeichen <= 3) {
		// start Zeile 0 in der mitte
		brett[0][positionKugel] = zeichen;

		// Schleife ueber weg
		for (int i = 0; i < zeilen - 1; i++) {
			// entscheidung links oder rechts
			if (weg[akteullesKugelZeichen][i] == 0) {
				positionKugel -= 1;
			}

			if (weg[akteullesKugelZeichen][i] == 1) {
				positionKugel += 1;
			}
			// zeichen an entsprechender posiiton/index einfuegen, bzw. ueberschreiben!
			// +1 daher, da fuer 0 bereits gesetzt und schleife startet ebenfalls bei 0
			brett[i + 1][positionKugel] = zeichen;

		}

		// Kugelzeichen um eins erhoehen.
		akteullesKugelZeichen += 1;
		
	}
	else {
		// gebe Text aus wenn wurflimit von 4 erreicht
		getText("wurflimit_erreicht");
		cout << endl;
		// ohne system("pause") wuerde der Text niemals sichtbar sein, da sofort durch system("CLS") geloescht
		system("pause");
	}
}

// funktion: druckeMenue
// druckz das Menue auf die Konsole
void druckeMenue() {
	// CLS = CLear Screen, Loescht kompletten konsoleninhalt
	system("CLS");
	cout << "1 = "; getText("neues_brett"); cout << endl;
	cout << "2 = "; getText("neuer_wurf"); cout << endl;
	cout << "3 = "; getText("loesche_wuerfe"); cout << endl;
	cout << "4 = "; getText("brett_anzeigen"); cout << endl;
	cout << "5 = "; getText("programm_schliessen"); cout << endl;
	getText("auswahl");
}

// funktion: druckeSprahauswahl
// gibt Startbildschrim auswahl aus.
void druckeSprachauswahl() {
	cout << "Bitte waehlen Sie eine Sprache:" << endl;
	cout << "'d' fuer deutsche Sprache." << endl;
	cout << "'e' fuer englische Sprache." << endl;
	cout << "(Bei Eingabe eines anderen zeichens, wird automatisch deutsch als Sprache gewaehlt.)" << endl;
	cout << "Auswahl: ";
}

// funktion main
// wird immer automatisch gestartet
// wenn main am anfang -> fehler, da andere funktionen noch nicht deklariert wurden!
int main()
{
	// Variablen deklarieren
	int zeilenanzahl;
	int menueauswahl;
	char sprachauswahl = 'd';
	// zusatz fuer konsole
	int wegeinfuegenzaehler = 1;

	char** brett = erstelleBrett(zeilen, spalten);

	// Sprache auswaehlen
	druckeSprachauswahl();
	cin >> sprachauswahl;

	// Sicherheitscheck!!! wir wollen keine alternativen!!!
	if (sprachauswahl == 'd') {
		aktuelleSprache = 1;
	}
	else {
		if (sprachauswahl == 'e') {
			aktuelleSprache = 0;
		}
		else {
			aktuelleSprache = 1;
		}
	}

	// Never-Ending-Story
	while (true) {
		druckeMenue();
		cin >> menueauswahl;

		system("CLS");
		// Neues Brett
		if (menueauswahl == 1) {
			// Wir gehen davon aus das der Nutzer dumm ist und 1 eingibt, bzw. versucht
			bool eingabeValide = false;
			// solange eingabe ungueltig, nochmal
			while (eingabeValide == false) {
				system("CLS");
				getText("anzahl_zeilen");
				cin >> zeilenanzahl;
				// pruefe auf validitaet
				if (3 > (int) zeilenanzahl || 30 < (int) zeilenanzahl) {
					// Fehlermeldung ausgeben
					getText("fehleingabe");
					cout << endl;
					eingabeValide = false;
					system("pause");
				}
				else {
					eingabeValide = true;
				}
			}
			
			// belegen der globalen Variablen
			zeilen = zeilenanzahl;
			spalten = zeilen * 2 + 1;
			// brett initialiseren
			brett = erstelleBrett(zeilen, spalten);
		}
		// neuer Wurf
		if (menueauswahl == 2) {
			// pruefen, ob geworfen werden darf soll kann
			if (akteullesKugelZeichen <= 4) {
				// funktion aufrufen
				wegEinfuegen(brett, weg);
			}
			else {
				// Fehler ausgeben
				getText("wurflimit_erreicht");
			}
			
		}
		// brett loeschen
		if (menueauswahl == 3) {
			// initliaert im Grunde lediglich ein neues brett, sodas es leer wird
			loescheBrett(brett);
		}
		// Brett anzeigen
		if (menueauswahl == 4) {
			druckeBrett(brett);
			// lass es uns erstmal sehen!, deshalb ...
			system("pause");
		}
		// beenden
		if (menueauswahl == 5) {
			return 0;
		}
	}
}

