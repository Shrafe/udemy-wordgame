#include "FBullCowGame.h"

FBullCowGame::FBullCowGame(){ Reset(3); }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset(int32 Choice)
{
	MyHiddenWord = Isograms[Choice];
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}


bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (isupper(Letter)) {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// 0 or 1 letter words return true instantly
	if (Word.length() <= 1) { return true; }
	// create map for storing letter counts
	TMap<char, bool> LetterSeen;
	
	// for each letter
	for (auto Letter : Word) {
		
		Letter = tolower(Letter);
		// letter exists in the map already. not an isogram
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)){
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

// recieves valid guess, increments try and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	FBullCowCount Counts;

	// word lengths must match
	int32 WordLength = GetHiddenWordLength();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (GChar == MHWChar) {
					Counts.Bulls++;
				} else {
					Counts.Cows++;
				}
			}
		}
	}

	if (Counts.Bulls == GetHiddenWordLength()) {
		bIsGameWon = true;
	}else {
		bIsGameWon = false;
	}

	MyCurrentTry++;
	return Counts;
}
