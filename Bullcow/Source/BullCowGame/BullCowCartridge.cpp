// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

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
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = GetValidWords(HiddenWords);
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

void UBullCowCartridge::ProcessGuess(const FString& Input) 
{
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have won"));
        EndGame();
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

    int32 Bulls, Cows;
    FBullCowCount CountResult = GetBullCows(Input);

    PrintLine(TEXT("You have %i Bulls, %i Cows"), CountResult.Bulls, CountResult.Cows);
}

bool UBullCowCartridge::IsIsogram(const FString& Input) const
{
    TArray<bool> BoolArray;
    BoolArray.Init(false, 26);

    for (int i = 0; i < Input.Len(); i++) {

        if (BoolArray[int32(Input[i]) - 97])
        {
            return false;
        } 
        else {
            BoolArray[int32(Input[i]) - 97] = true;
        }
    }

    return true;
}

FString UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    return WordList[FMath::RandRange(0,WordList.Num()-1)];
}
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