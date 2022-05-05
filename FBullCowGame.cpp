#pragma once

#include "FBullCowGame.h"
#include <string>
#include <map>

// Hogy Unreal barát legyen
#define TMap std::map		// #define kicseréli az std::map-ot TMap-ra (úgymond beletesszük egy változóba)
using int32 = int;






void FBullCowGame::Reset()
{

	const FString HiddenWord = "kulcs";  // A szónak Izogramnak KELL lennie!

	MyHiddenWord = HiddenWord;
	MyCurrentTry = 1;


	bGameIsWon = false;
}



// ÉRVÉNYES tippet fogad, ciklus növekedés, visszaadja a számot

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	
	// visszatérési változó
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();

	// Bejárjuk a Rejtett szó összes karakterét
	for (int32 Rejtett_szo_karaktere = 0; Rejtett_szo_karaktere < WordLength; Rejtett_szo_karaktere++)
	{		// Összehasonlitjuk a betüket a Tippelt szóhoz
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
	// A 0 és 1 betüs szavakat Izogramként kezeli
	if (word.length() <= 1)
	{
		return true;
	}
	TMap <char, bool> LetterSeen;  // Létrehozzuk a map -unkat
	for (auto betu : word)     
	{
		betu = tolower(betu);   // Kezelje a mixelt szavakat (kis és nagy betü egyszerre)

		if (LetterSeen[betu])  // Ha a szó a map-ban van
		{
			return false;     // Nincs Izogram
		}else {
			LetterSeen[betu] = true;   // Hozzáadja a szót a map-hoz
		}
	}
	return true;   // Például azokban az esetekben ha /0 van beirva
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto betu : word)
	{
		if (!islower(betu))  // Ha NEM kisbetüs a betü
		{
			return false;
		}else {
			return true;
		}
	}
	return false;
}


FBullCowGame::FBullCowGame()   // Alalpértelmezett konstruktor
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
	else if (!IsLowercase(guess))  // Ha a tipp valamelyik karaktere nem kisbetüs
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != MyHiddenWord.length())  // Ha a tipp hossza nem azonos a Rejtett szóval
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
