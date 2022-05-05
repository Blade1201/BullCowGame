/* Ez a konzol exe.
Ez felel a felhasználói interakciókért. 
A játék logikája az FBullCowGame osztályban található
*/

#pragma once

#include <iostream>
#include "FBullCowGame.h"
#include <string>



using std::cout;
using std::cin;
using std::endl;

// Hogy Unreal barát legyen
using FText = std::string;
using int32 = int;

int main();

void bemutato();
FText ValidTipp();
void jatszani();
void Osszefoglalo();
bool akarszJatszani();


FBullCowGame BCGame;  // Új játék példányositása


// Bemeneti pont az alkalmazásunkba
int main() {

	setlocale(LC_ALL, "hun");



	do {
		bemutato();
		jatszani();
	} while (akarszJatszani());
	


	



	return 0; // Kilép az alkalmazásból
}



void bemutato() {
	cout << "\n\nÜdvözöllek a Bikák és Tehenekben, ez egy VIDÁM játék!\n" << endl;

	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BIKA |O            O| TEHÉN  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	cout << "\nEl találod hogy mely " << BCGame.GetHiddenWordLenght() << " betûs szóra gondolok?" << endl;
}


// Folyamatos ciklus amig a felhasználó egy valid értéket meg nem ad!
FText ValidTipp() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;

	FText tipp = "";
	do {
		// Tipp kérés a játékostól
		int32 JelenlegiProbalkozas = BCGame.GetCurrentTry();
		cout << endl << JelenlegiProbalkozas << ". Próba a " << BCGame.GetMaxTries() << "-ból/bõl\n" << " Tippelj egyet: " << endl;
		getline(cin, tipp);
		cout << "\nEzt tippelted: " << tipp << endl;


		// Helyzet ellenõrzés és válasz kapás
		Status = BCGame.CheckGuessValidity(tipp);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			cout << "Kérlek adj meg egy szót betü ismétlõdés nélkül!" << endl;
			break;
		case EGuessStatus::Wrong_Length:
			cout << "Kérlek adj meg egy " << BCGame.GetHiddenWordLenght() << " Karakteres szót!" << endl;
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "Kérlek adj meg egy szót kizárólag kisbetük használatával!" << endl;
			break;
		default:
			// Feltételezzük hogy a tipp valid értékû
			break;
		}
	} while (Status != EGuessStatus::OK); // Addig megy a ciklus amig van hiba


	return tipp;


}


// Játszik egy játékot a befejezésig
void jatszani() {
	BCGame.Reset();
	int32 MaxProbalkozas = BCGame.GetMaxTries();

	// Ciklus amig a játék nincs megnyerve és maradt még próbánk

	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxProbalkozas)
	{
		FText tippem = ValidTipp(); // Érvényes tipp-e?


		// Beküld egy valid tippet és visszakapja az értéket
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(tippem);

		cout << "Bikák = " << BullCowCount.Bulls << endl;

		cout << "Tehenek = " << BullCowCount.Cows << endl;
	}

	// Összesités
	Osszefoglalo();
}

bool akarszJatszani()
{
	cout << "Akarsz újra játszani ugyanezzel a szóval?? [i/n] ";
	FText valasz = "";
	getline(cin, valasz);
	return (valasz[0] == 'i' || valasz[0] == 'I');
}


void Osszefoglalo()
{
	if (BCGame.isGameWon())
	{
		cout << "\nGyõztünk!\n";
	}
	else
	{
		cout << "\nVeszitettünk!\n";
	}
}
