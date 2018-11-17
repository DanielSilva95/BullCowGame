// Header of the Game Logic Class

#pragma once

#include <string>
#include <map>
#define TMap std::map

// Makes the syntax close to Unreal's
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Ok, Not_Isogram, Wrong_Length, Not_Lowercase, Invalid_Guess
};

class FBullCowGame {

public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	void Reset();
	EGuessStatus IsGuessValid(FString);
	FBullCowCount SubmitGuess(FString);
	int32 GetHiddenWordLength() const;
	void SetHiddenWord(int32);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	TMap<int32, FString> AvailableHiddenWords;

	bool isIsogram(FString) const;
	bool isLowerCase(FString) const;
};