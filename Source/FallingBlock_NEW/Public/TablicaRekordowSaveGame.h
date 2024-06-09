// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TablicaRekordowSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API UTablicaRekordowSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UTablicaRekordowSaveGame();

    UPROPERTY(VisibleAnywhere, Category = "Dane tablicy")
    TArray<int32> punkty;

    UPROPERTY(VisibleAnywhere, Category = "Dane tablicy")
    TArray<int32> tryb;

    UPROPERTY(VisibleAnywhere, Category = "Dane tablicy")
    TArray<FDateTime> data_godzina;

    //int32 ile_linii; //ile linii zapisanych w tabeli

    void czyszczenie();
    void wypisz();
};
