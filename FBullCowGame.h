/* J�t�k logika(Nincs felhaszn�l�i interakci�)
A j�t�k a Mastermind-on alapul� egyszer� sz� kital�l�s j�t�k */

#pragma once

#include <string>
#include <iostream>


using std::cout;


// Hogy Unreal bar�t legyen
using FString = std::string;
using int32 = int;




struct FBullCowCount // Ezt az�rt itt hozzuk l�tre mert ezt a main-ben nem fogjuk haszn�lni, csak a j�t�k logik�j�ban
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus   // Az Unreal-ben az enum v�ltoz� nevei E bet�vel kezd�dnek
{   // A class az�rt kell hogy az enum-ban l�v� v�ltoz�k csak az enum-ban l�tezzenek igy azok nevei m�shol is megism�tl�dhetnek
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};



class FBullCowGame {

public:
	FBullCowGame(); // Konstruktor l�trehoz�sa

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;



	bool isGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;




	void Reset();
	void PrintGameSummary();


	FBullCowCount SubmitValidGuess(FString);


	// Ezt most hadjuk, n�zz�k a fenti k�dot /\

private:

	// Konstruktorban van az inicializ�ci�
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
}; 
