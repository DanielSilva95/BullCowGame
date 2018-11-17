

#pragma once

#include "FBullCowGame.h"
#include <map>

// Makes the syntax close to Unreal's
#define TMap std::map
using FString = std::string;
using int32 = int32;

FBullCowGame::FBullCowGame() {
	AvailableHiddenWords = { {3,"ear"}, {4,"face"}, {5,"bacon"}, {6,"planet"}, {7,"harmony"} };
	Reset();
}

void FBullCowGame::Reset() {
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const {
	switch (MyHiddenWord.length())
	{
	case 3:
		return 4;
	case 4:
		return 7;
	case 5:
		return 10;
	case 6:
		return 16;
	case 7:
		return 20;
	default:
		break;
	}
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const {
	return bIsGameWon;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) {
	
	if (!isIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	if (GetHiddenWordLength() != Guess.length()) {
		return EGuessStatus::Wrong_Length;
	}
	if (!isLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else 
	{
		return EGuessStatus::Ok;
	}
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	for (int32 i = 0; i < MyHiddenWord.length(); i++) {
		for (int32 j = 0; j < Guess.length(); j++) {
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		bIsGameWon = true;
	} else {
		bIsGameWon = false;
	}

	return BullCowCount;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isIsogram(FString Guess) const
{
	if (Guess.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess) {
		Letter = tolower(Letter);

		if (!LetterSeen[Letter]) {
			LetterSeen[Letter] = true;
		} else {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::isLowerCase(FString Guess) const
{
	for (auto Letter : Guess) {
		if (!islower(Letter))
			return false;
	}

	return true;
}

void FBullCowGame::SetHiddenWord(int32 WordLength)
{
	MyHiddenWord = AvailableHiddenWords[WordLength];
}
