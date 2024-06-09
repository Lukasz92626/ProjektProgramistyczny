// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MenuTablica.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/*UMenuWidget();*/

	bool czy_wybrano; //informacja czy uzytkownik juz dokonal wyboru tego jak ma wygladac rozgrywka
	bool czy_kliknieto_tablica; //informacja czy kliknieto wybor tablicy
	bool czy_kliknieto_wyjscie; //informacja czy kliknieto wyjscie

	int8 miejsce_w_menu; // 0 - pierwsza strona, 1 - wybor zestawu blokow, 2 - wybor rozmiaru planszy, 3 - wybor trybu gry

	int8 zestaw_blokow; // 0 - standardowy, 1 - duze bloki, 2 - bloki generowane losowo
	int8 rozmiar_planszy; // 0 - 10x20, 1 - 20x20, 2 - 30x20
	int8 tryb_gry; // 0 - standardowy, 1 - zdobywania okreslonej liczby punktow, 2 - przetrwania

	UMenuTablica* TablicaInstance;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void klinieto_1();
	UFUNCTION()
	void klinieto_2();
	UFUNCTION()
	void klinieto_3();

	//Tytul
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Tytul;

	//Pierwszy przycisk
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_1;

	//Drugi przycisk
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_2;

	//Trzeci przycisk
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_3;

	void pokaz_menu();
	void ukryj_menu();

	void ustaw_menu_glowne();
	void ustaw_menu_wybor_bloku();
	void ustaw_menu_wybor_planszy();
	void ustaw_menu_tryb_gry();
};
