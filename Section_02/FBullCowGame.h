/* 
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/


#pragma once
#include <string>
#include <map>
#define TMap std::map

// makes syntax feel like Unreal Engine
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public: 
	FBullCowGame();

	int32 GetMaxTries() const; 
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	void Reset(int32);

	bool IsLowerCase(FString) const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString);
	
private:
	// word list
	TMap<int32, FString> Isograms{ {3, "tan"}, {4, "sand"}, {5, "brand"}, {6, "planet"}, {7, "planets"} };
	bool IsIsogram(FString) const;

	bool bIsGameWon;
	int32 MyCurrentTry;
	FString MyHiddenWord;
};