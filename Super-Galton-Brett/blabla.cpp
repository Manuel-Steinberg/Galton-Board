// funktion drucke Brett
void druckeBrett(char** brett) {
	for (int i = 0; i < zeilen; i++) {
		for (int j = 0; j < spalten; j++) {
			if (brett[i][j] != NULL) {
				cout << brett[i][j];
			}

		}
		// neue Zeile!!!
		cout << endl;
	}
}