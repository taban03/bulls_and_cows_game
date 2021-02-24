// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();

    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);
    PrintLine(TEXT("The number of valid words is :%i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The number of possible words is :%i."), Words.Num());

    TArray<FString> ValidWords;
/*
Work on TArray
*/
    for (int32 Index = 0; Index < 10; Index++)
    {
        if (Words[Index].Len() >= 4 && Words[Index].Len() <= 8)
        {
            // PrintLine(TEXT("%s"), *Words[Index]);
            ValidWords.Emplace(Words[Index]);
        }
    }
    for (int32 Index = 0; Index < ValidWords.Num(); Index++)
    {
        PrintLine(TEXT("%s"), *ValidWords[Index]);
    }
    
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
        
    } else 
    {
        ProcessGuess(Input);
       
    }   
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to Bulls & Cows game!"));

    HiddenWord = TEXT("Cake");
    bGameOver = false;
    Lives = HiddenWord.Len();

    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your your guess and press enter to continue..."), Lives);

    const TCHAR HW[] = TEXT("plums");
    PrintLine(TEXT("Character 1 of hidden word is: %c"), HiddenWord[0]);
    PrintLine(TEXT("Character 4 of HW word is: %c"), HW[3]);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
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
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
        
}

bool UBullCowCartridge::IsIsogram(FString String) const
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

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
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