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
    ClearScreen();


    if (Input == HiddenWord) {
        PrintLine(TEXT("You have won!"));

    } else {
        if (HiddenWord.Len() != Input.Len()) {
        PrintLine(TEXT("The length is %i long, try again!"), HiddenWord.Len());
    }
        PrintLine(TEXT("You have lost!"));
    }

}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("Cake");
    Lives = 4;
}
