// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();

    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);

    PrintLine(TEXT("Welcoime to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Please insert something and press Enter:"));

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
    PrintLine(TEXT("Welcome to Bulls & Cows game!");

    HiddenWord = TEXT("Cake");
    bGameOver = false;
    Lives = HiddenWord.Len();

    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your your guess and press enter to continue..."), Lives);
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
    
    // if (!IsIsogram)
    // {

    // }
        
    if (HiddenWord.Len() != Guess.Len()) 
    {
        PrintLine(TEXT("The hidden word is % letter long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again. You have %i lives left!"), Lives);
        return;
    }
    PrintLine(TEXT("You lost a life"));
    --Lives;
        
    if (Lives <= 0) 
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!");
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    PrintLine(TEXT("Guess again, yoi have %i lives left"), Lives);
        
}
