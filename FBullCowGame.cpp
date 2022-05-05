#pragma once

#include "FBullCowGame.h"
#include <string>
#include <map>

// Hogy Unreal bar�t legyen
#define TMap std::map		// #define kicser�li az std::map-ot TMap-ra (�gymond beletessz�k egy v�ltoz�ba)
using int32 = int;






void FBullCowGame::Reset()
{

	const FString HiddenWord = "kulcs";  // A sz�nak Izogramnak KELL lennie!

	MyHiddenWord = HiddenWord;
	MyCurrentTry = 1;


	bGameIsWon = false;
}



// �RV�NYES tippet fogad, ciklus n�veked�s, visszaadja a sz�mot

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	
	// visszat�r�si v�ltoz�
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();

	// Bej�rjuk a Rejtett sz� �sszes karakter�t
	for (int32 Rejtett_szo_karaktere = 0; Rejtett_szo_karaktere < WordLength; Rejtett_szo_karaktere++)
	{		// �sszehasonlitjuk a bet�ket a Tippelt sz�hoz
		for (int32 tippem_karaktere = 0; tippem_karaktere < WordLength; tippem_karaktere++) 
		{			// Ha azonosak
			if (Guess[tippem_karaktere] == MyHiddenWord[Rejtett_szo_karaktere])
			{
				if (Rejtett_szo_karaktere == tippem_karaktere)	// Ha egy helyen vannak
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	// A 0 �s 1 bet�s szavakat Izogramk�nt kezeli
	if (word.length() <= 1)
	{
		return true;
	}
	TMap <char, bool> LetterSeen;  // L�trehozzuk a map -unkat
	for (auto betu : word)     
	{
		betu = tolower(betu);   // Kezelje a mixelt szavakat (kis �s nagy bet� egyszerre)

		if (LetterSeen[betu])  // Ha a sz� a map-ban van
		{
			return false;     // Nincs Izogram
		}else {
			LetterSeen[betu] = true;   // Hozz�adja a sz�t a map-hoz
		}
	}
	return true;   // P�ld�ul azokban az esetekben ha /0 van beirva
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto betu : word)
	{
		if (!islower(betu))  // Ha NEM kisbet�s a bet�
		{
			return false;
		}else {
			return true;
		}
	}
	return false;
}


FBullCowGame::FBullCowGame()   // Alalp�rtelmezett konstruktor
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{
		{3,4},{4,7},{5,10},{6,16},{7,20}
	};

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}

int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWord.length();
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess))  // Ha a tipp NEM Izogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess))  // Ha a tipp valamelyik karaktere nem kisbet�s
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != MyHiddenWord.length())  // Ha a tipp hossza nem azonos a Rejtett sz�val
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
