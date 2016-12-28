// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <cctype>
#include "FBullCowGame.h"

// makes syntax feel like Unreal Engine
using FText = std::string;
using int32 = int;

bool AskToPlayAgain();
bool IsValidWordLength(FText);

int32 SelectWordLength(FText);
FText GetValidGuess();

void PrintGameSummary();
void PrintIntroduction();
int32 SelectWordLength();
void PlayGame();

FBullCowGame BCGame;

int main()
{
	do {
		PrintIntroduction();
		PlayGame();
		// Add game summary
	} while (AskToPlayAgain());
	return 0;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else {
		std::cout << "You lost. Try again!\n";
	}
}


// Plays a single game iteration
void PlayGame() {
	BCGame.Reset(SelectWordLength());
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()){
		FText CurrentGuess = GetValidGuess();
		// submit valid guess to game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(CurrentGuess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n";
		std::cout << std::endl;
	}
	PrintGameSummary();
}


FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		std::cout << "You're on guess " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << std::endl;
		std::cout << "Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Not_Lowercase:
			std::cout << "The guess must be in lowercase.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "The guess must be a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "The guess is not an isogram (no repeating letters).\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); // loop until we get no errors
	return Guess;
}


void PrintIntroduction() {
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "         }   {          ___ " << std::endl;
	std::cout << "         (o o)         (o o) " << std::endl;
	std::cout << "  /-------\\ /           \\ /-------\\ " << std::endl;
	std::cout << " / | BULL |O             O| COW  | \\ " << std::endl;
	std::cout << "*  |-,--- |               |------|  * " << std::endl;
	std::cout << "  ^      ^               ^      ^ " << std::endl;
	std::cout << "Guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

int32 SelectWordLength()
{

	FText Choice = "";
	do
	{
		std::cout << "Type the desired length of the hidden word. 3 to 7 letters.\n";
		getline(std::cin, Choice);
	} while (!IsValidWordLength(Choice));
	int32 ChoiceInt = std::stoi(Choice);
	return ChoiceInt;
}


// returns True if Word is a single number from 3-7 inclusive
bool IsValidWordLength(FText Word){
	bool Error = false;
	if (Word.length() != 1) {
		Error = true;
	}
	else if (!std::isdigit(Word[0])) {
		Error = true;
	}
	else {
		// safe because we have length == 1 and it's a digit
		int32 ValueCheck = std::stoi(Word);
		if (ValueCheck < 3 || ValueCheck > 7) {
			Error = true;
		}
	}
	if (Error) {
		std::cout << "Please enter a number between 3 and 7.\n\n";
	}
	return !Error;
}
