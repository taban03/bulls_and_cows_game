// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);
    // int32 a = 0;
    // int32 b = 5;

    // const int32& refa = a;
    // PrintLine(TEXT("a = %i, b = %i, refa = %i"), a, b, refa);

    // refa = b;

    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
        
    } else 
    {
        ProcessGuess(PlayerInput);
    }   
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to Bulls & Cows game!"));
    
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    bGameOver = false;
    Lives = HiddenWord.Len();

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your your guess and press enter to continue..."), Lives);
    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord) 
    {
            PrintLine(TEXT("You have won!"));
            EndGame();
            return;
    }
        
    if (HiddenWord.Len() != Guess.Len()) 
    {
        PrintLine(TEXT("The hidden word is % letter long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again. You have %i lives left!"), Lives);
        return;
    }
    PrintLine(TEXT("You lost a life"));
    --Lives;
        
    if (!IsIsogram(Guess))
    {

        PrintLine(TEXT("No repeating letters, guerss again"));
        return;
    }

    if (Lives <= 0) 
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
     
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
        
}

bool UBullCowCartridge::IsIsogram(const FString& String) const
{
    for (int32 Index = 0; Index < String.Len(); Index++) 
    {
        for (int32 Comparison = Index + 1; Comparison < String.Len(); Comparison++)
        {
            if (String[Index] == String[Comparison])
            {
                return false;
            }
        }   
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
   // range-based foor loop
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

// Out parameters usage. Parameters that are only used for returning values back to the caller are called out parameters.
FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}
