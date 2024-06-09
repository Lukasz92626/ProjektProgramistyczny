// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TablicaRekordowSaveGame.h"
#include "MenuTablica.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API UMenuTablica : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void klinieto_poprzednia();
	UFUNCTION()
	void klinieto_nastepna();
	UFUNCTION()
	void klinieto_powrot();
	
	//Tytul
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tytul;

	//Kolumna Numer
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_Tytul;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Numer_10;

	//Kolumna Punkty
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_Tytul;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Punkty_10;

	//Kolumna Tryb
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_Tytul;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tryb_10;

	//Kolumna Data
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_Tytul;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_7;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_8;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_9;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Data_10;

	//Przyciski
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Poprzednia;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Poprzednia;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Nastepna;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Nastepna;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Powrot;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Powrot;

	virtual void NativeConstruct() override;

	void wypisz_tablice_posortowana();
	void wypisz_tablice();
	void wczytaj_tablice();
	void wyczysc_tablice();
	void sortuj_dane();

	int32 min_idx;
	UTablicaRekordowSaveGame* LoadGameInstance;
	bool czy_powrot;

	TArray<int32> punkty;
	TArray<int32> tryb;
	TArray<FDateTime> data_godzina;

	void log_liczba(int liczba);
};
