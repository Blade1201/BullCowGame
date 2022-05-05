/* Ez a konzol exe.
Ez felel a felhaszn�l�i interakci�k�rt. 
A j�t�k logik�ja az FBullCowGame oszt�lyban tal�lhat�
*/

#pragma once

#include <iostream>
#include "FBullCowGame.h"
#include <string>



using std::cout;
using std::cin;
using std::endl;

// Hogy Unreal bar�t legyen
using FText = std::string;
using int32 = int;

int main();

void bemutato();
FText ValidTipp();
void jatszani();
void Osszefoglalo();
bool akarszJatszani();


FBullCowGame BCGame;  // �j j�t�k p�ld�nyosit�sa


// Bemeneti pont az alkalmaz�sunkba
int main() {

	setlocale(LC_ALL, "hun");



	do {
		bemutato();
		jatszani();
	} while (akarszJatszani());
	


	



	return 0; // Kil�p az alkalmaz�sb�l
}



void bemutato() {
	cout << "\n\n�dv�z�llek a Bik�k �s Tehenekben, ez egy VID�M j�t�k!\n" << endl;

	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BIKA |O            O| TEH�N  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	cout << "\nEl tal�lod hogy mely " << BCGame.GetHiddenWordLenght() << " bet�s sz�ra gondolok?" << endl;
}


// Folyamatos ciklus amig a felhaszn�l� egy valid �rt�ket meg nem ad!
FText ValidTipp() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;

	FText tipp = "";
	do {
		// Tipp k�r�s a j�t�kost�l
		int32 JelenlegiProbalkozas = BCGame.GetCurrentTry();
		cout << endl << JelenlegiProbalkozas << ". Pr�ba a " << BCGame.GetMaxTries() << "-b�l/b�l\n" << " Tippelj egyet: " << endl;
		getline(cin, tipp);
		cout << "\nEzt tippelted: " << tipp << endl;


		// Helyzet ellen�rz�s �s v�lasz kap�s
		Status = BCGame.CheckGuessValidity(tipp);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			cout << "K�rlek adj meg egy sz�t bet� ism�tl�d�s n�lk�l!" << endl;
			break;
		case EGuessStatus::Wrong_Length:
			cout << "K�rlek adj meg egy " << BCGame.GetHiddenWordLenght() << " Karakteres sz�t!" << endl;
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "K�rlek adj meg egy sz�t kiz�r�lag kisbet�k haszn�lat�val!" << endl;
			break;
		default:
			// Felt�telezz�k hogy a tipp valid �rt�k�
			break;
		}
	} while (Status != EGuessStatus::OK); // Addig megy a ciklus amig van hiba


	return tipp;


}


// J�tszik egy j�t�kot a befejez�sig
void jatszani() {
	BCGame.Reset();
	int32 MaxProbalkozas = BCGame.GetMaxTries();

	// Ciklus amig a j�t�k nincs megnyerve �s maradt m�g pr�b�nk

	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxProbalkozas)
	{
		FText tippem = ValidTipp(); // �rv�nyes tipp-e?


		// Bek�ld egy valid tippet �s visszakapja az �rt�ket
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(tippem);

		cout << "Bik�k = " << BullCowCount.Bulls << endl;

		cout << "Tehenek = " << BullCowCount.Cows << endl;
	}

	// �sszesit�s
	Osszefoglalo();
}

bool akarszJatszani()
{
	cout << "Akarsz �jra j�tszani ugyanezzel a sz�val?? [i/n] ";
	FText valasz = "";
	getline(cin, valasz);
	return (valasz[0] == 'i' || valasz[0] == 'I');
}


void Osszefoglalo()
{
	if (BCGame.isGameWon())
	{
		cout << "\nGy�zt�nk!\n";
	}
	else
	{
		cout << "\nVeszitett�nk!\n";
	}
}
