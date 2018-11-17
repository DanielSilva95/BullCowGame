/* This is the console executable, that makes use of the BullCow Class
It acts like a View as in a MVC Pattern, so it's responsale for all
user interaction. For the game logic see the FBullCowGame class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
int32 AskHiddenWordLength();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();

FBullCowGame BCGame;

int main() {

	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

    return 0;
}

void PrintIntro() {
	std::cout << "Welcome to BullCowGame, a fun word game!\n\n";
	std::cout << "	                            ..---.\n";
	std::cout << "                           // |\\||\\\n";
	std::cout << "    \\   /                 ///;||\\|;\\               \\   /\n";
	std::cout << "      o               .__// \\\\____//\\_,.             o\n";
	std::cout << "    /   \\              Y{_\\_/  \\'' = __/           /   \\\n";
	std::cout << "                       \\___   (o) (o)  }       /\n";
	std::cout << "                          /         :--'   \n";
	std::cout << "                    .---/ \\_    `__\\-.\n";
	std::cout << "                   /     `--\\___(o'o) \\\n";
	std::cout << "             \\   / |     \\      `===='  |\\   /\n";
	std::cout << "               o    `.    `.    .'    .'   o\n";
	std::cout << "             /   \\   (`.    `. '    .')  /   \\\n";
	std::cout << "                    (  `.    `...'   )\n";
	std::cout << "                     (   .+.    `-.   )\n";
	std::cout << "                     (.-'  .>-._   `-.)\n";
	std::cout << "   \\   /           (___.-'      `-.___)            \\   /\n";
	std::cout << "     o              (                )               o\n";
	std::cout << "   /   \\            (                )             /   \\\n\n";
	std::cout << "I'll think of an isogram, can you guess what it is??\n\n";
}

void PlayGame() {

	BCGame.SetHiddenWord(AskHiddenWordLength());

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letters isogram I'm thinking of?\n\n";

	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "You've got " << BullCowCount.Bulls << " Bulls\n";
		std::cout << "You've got " << BullCowCount.Cows << " Cows\n\n";
	}

	PrintGameSummary();
}

int32 AskHiddenWordLength() {
	FString StrResponse = "";
	int32 HiddenWordLength;

	do {
		std::cout << "\nChoose the size of your isogram <3,4,5,6,7>: ";
		std::getline(std::cin,StrResponse);
	} while (StrResponse._Equal("3") || StrResponse._Equal("4") || StrResponse._Equal("5") 
		|| StrResponse._Equal("6") || StrResponse._Equal("7"));

	HiddenWordLength = std::stoi(StrResponse);

	return HiddenWordLength;
}

bool AskToPlayAgain() {
	char Response = 'N';

	do {
		std::cout << "Do you want to play the game again? <YES/NO>" << std::endl;
		FText StrResponse = "";
		std::getline(std::cin, StrResponse);

		Response = toupper(StrResponse[0]);

	} while (Response != 'Y' && Response != 'N');

	if (Response == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus GuessStatus = EGuessStatus::Invalid_Guess;

	do {
		std::cout << "Try n." << BCGame.GetCurrentTry() << " of ";
		std::cout << BCGame.GetMaxTries() << " - What is your guess? ";

		std::getline(std::cin, Guess);

		GuessStatus = BCGame.IsGuessValid(Guess);

		switch (GuessStatus) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
		default:
			break;
		}
	} while (GuessStatus != EGuessStatus::Ok);

	return Guess;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations!! You won the game!";
	} else {
		std::cout << "You're out tries, better luck next time!";
	}
}