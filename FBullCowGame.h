/* Játék logika(Nincs felhasználói interakció)
A játék a Mastermind-on alapuló egyszerü szó kitalálós játék */

#pragma once

#include <string>
#include <iostream>


using std::cout;


// Hogy Unreal barát legyen
using FString = std::string;
using int32 = int;




struct FBullCowCount // Ezt azért itt hozzuk létre mert ezt a main-ben nem fogjuk használni, csak a játék logikájában
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus   // Az Unreal-ben az enum változó nevei E betüvel kezdõdnek
{   // A class azért kell hogy az enum-ban lévõ változók csak az enum-ban létezzenek igy azok nevei máshol is megismétlõdhetnek
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};



class FBullCowGame {

public:
	FBullCowGame(); // Konstruktor létrehozása

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;



	bool isGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;




	void Reset();
	void PrintGameSummary();


	FBullCowCount SubmitValidGuess(FString);


	// Ezt most hadjuk, nézzük a fenti kódot /\

private:

	// Konstruktorban van az inicializáció
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
}; 
