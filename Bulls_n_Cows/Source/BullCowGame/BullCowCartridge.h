// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:


	static TMap<int32,TArray<FString>> HiddenWordDictionary;

	bool bGameOver;
	FString HiddenWord;
	int32 lives;
	

	void SetupGame();
	void EndGame();
	void CalcBullsCows(const FString& Guess, int32 &Bulls, int32 &Cows) const;
	void ProcessGuess(const FString& Guess);
	bool IsWin(const FString& Guess) const;
	bool IsIsogram(const FString& Guess) const;
	FString RandomHiddenWord();
};

