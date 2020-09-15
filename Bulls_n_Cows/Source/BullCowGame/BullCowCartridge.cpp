// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/CString.h"
#include <limits>

TMap<int32,TArray<FString>> UBullCowCartridge::HiddenWordDictionary = 
    {   
        {3,{"cat", "cow", "pan", "dog"}},
        {4,{"crow", "four", "helm", "post"}},
        {5,{"bread",}},
        {6,{"person","parent"}},
    };

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver){
        SetupGame();
    }
    else{
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    
    if(!IsIsogram(Guess)){
        PrintLine(TEXT("This is no Isogram."));
        PrintLine(FString::Printf(TEXT("You Have %i Lives Left"), lives));
        return;
    }
    if(Guess.Len() > HiddenWord.Len()){
        PrintLine(TEXT("Your Guess is too long"));
        PrintLine(FString::Printf(TEXT("You Have %i Lives Left"), lives));
        return;
    }
    else if(Guess.Len() < HiddenWord.Len()){
        PrintLine(TEXT("Your Guess is too short"));
        PrintLine(FString::Printf(TEXT("You Have %i Lives Left"), lives));
        return;
    }

    int32 Bulls, Cows;
    CalcBullsCows(Guess,Bulls,Cows);
    PrintLine(FString::Printf(TEXT("You hit %i Bulls and %i Cows"),Bulls,Cows));

    if(IsWin(Guess)){
        PrintLine(TEXT("You Have Won"));
         EndGame();
    }
    else{
        if(lives > 0){
            --lives;
            PrintLine(TEXT("You Lose A Life"));
            PrintLine(FString::Printf(TEXT("You Have %i Lives Left"), lives));
        }
        else{
            PrintLine(TEXT("You Have No Lives Left"));
            PrintLine(TEXT("You Have Lost"));
            EndGame();
        }
    }
}

void UBullCowCartridge::SetupGame(){
    bGameOver = false;
    HiddenWord = RandomHiddenWord();
    lives = HiddenWord.Len();
    ClearScreen();
    PrintLine(FString::Printf(TEXT("The HiddenWord ist: %s"), *HiddenWord)); // Debug Line
    PrintLine(TEXT("Hi Dumbasss!"));
    PrintLine(FString::Printf(TEXT("Guess the %i word"), HiddenWord.Len()));
    PrintLine(TEXT("Type In Your Guess\nPress Enter to Continue..."));
}
bool UBullCowCartridge::IsIsogram(const FString& Guess) const{
    TSet<TCHAR> WordChars;

    for (auto& character : Guess){
        WordChars.Add(character);
    }
    if(WordChars.Num()!=Guess.Len()){
        return false;
    }
    return true;
}

void UBullCowCartridge::CalcBullsCows(const FString& Guess, int32 &Bulls, int32 &Cows) const{
    Bulls = 0;
    Cows = 0;
    for(int32 i = 0; i < Guess.Len(); ++i){
        for(int32 j = 0; j < HiddenWord.Len(); ++j){
            if( Guess[i] == HiddenWord[j]  && i == j){
                ++Bulls;
                continue;
            }
            else if( Guess[i] == HiddenWord[j] && i != j){
                ++Cows;
                continue;
            }
        }
    }
}

bool UBullCowCartridge::IsWin(const FString& Guess) const{
    if(Guess.Equals(HiddenWord, ESearchCase::IgnoreCase)){
        return true;
    }
    return false;
}

void  UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(FString::Printf(TEXT("Press Enter To Continue...")));
}

FString UBullCowCartridge::RandomHiddenWord(){
    int32 min = std::numeric_limits<int>::max();
    int32 max = std::numeric_limits<int>::min();
    for (auto& DirElem : HiddenWordDictionary){
        if(min > DirElem.Key){
            min = DirElem.Key;
        }
        if(max < DirElem.Key){
            max = DirElem.Key;
        }
    }
    int32 Difficulty = FMath::RandRange(min,max);
    TArray<FString> Results = HiddenWordDictionary.FindRef(Difficulty);
    int32 RandomIntegerInRange = FMath::RandRange(0,Results.Num()-1);
    return Results[RandomIntegerInRange];
}   