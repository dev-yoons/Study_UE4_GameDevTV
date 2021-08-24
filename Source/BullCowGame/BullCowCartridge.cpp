// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame();

}
 
void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) 
    {
        ClearScreen();
        InitGame();
    }
    else {
        ProcessGuess(Input, 3);
    }
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;
    int a = 4;
    int d = a += 2;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Enter your guess"));

    const TCHAR HW[] = TEXT("cakes");
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
    PrintLine(TEXT("Press Enter to continue."));
}

void UBullCowCartridge::ProcessGuess(FString Input, int32 Counter) 
{
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have won"));
        EndGame();
        return;
    }


    if (Input.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Hidden word is %i letter long."), HiddenWord.Len());
        return;
    }

	if (!IsIsogram(Input))
	{
		PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }


    PrintLine(TEXT("Wrong answer, Lost a life!"));
    PrintLine(TEXT("Try again, %i lives remaining."), --Lives);

    if (Lives <= 0) 
    {
        PrintLine(TEXT("You have no lives left"));
        EndGame();
        return;
    }
}

bool UBullCowCartridge::IsIsogram(FString Input) const
{
    TArray<bool> BoolArray;
    BoolArray.Init(false, 26);

    for (int i = 0; i < Input.Len(); i++) {

        if (BoolArray[int32(Input[0]) - 64])
        {
            return false;
        } 
        else {
            BoolArray[int32(Input[0]) - 64] = true;
            continue;
        }
    }

    return true;
}