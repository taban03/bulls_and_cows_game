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
        
        if (Input == HiddenWord) 
        {
            PrintLine(TEXT("You have won!"));
            EndGame();

        } else 
        {
            PrintLine(TEXT("Lost a life!"));
            PrintLine(TEXT("You have %i lives left"), --Lives);
            if (Lives > 0) 
            {
                 if (HiddenWord.Len() != Input.Len()) 
                {
                    PrintLine(TEXT("Sorry, try guessing again. You have %i lives left!"), Lives);
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left! You lost!");
                EndGame();
            }  
        }
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
    PrintLine(TEXT("You have lost a life, you have %i lives left."), Lives);
    PrintLine(TEXT("Press enter to play again."));
}
