// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "Misc/GenericPlatformMisc.h" 

//UMenuWidget::UMenuWidget() {
//}

void UMenuWidget::NativeConstruct() {
	Super::NativeConstruct();
	ustaw_menu_glowne();

	czy_wybrano = false;
	czy_kliknieto_tablica = false;
	czy_kliknieto_wyjscie = false;

	miejsce_w_menu = 0;

	zestaw_blokow = 0;
	rozmiar_planszy = 0;
	tryb_gry = 0;

	if (Button_1) {
		Button_1->OnClicked.AddDynamic(this, &UMenuWidget::klinieto_1);
	}
	if (Button_2) {
		Button_2->OnClicked.AddDynamic(this, &UMenuWidget::klinieto_2);
	}
	if (Button_3) {
		Button_3->OnClicked.AddDynamic(this, &UMenuWidget::klinieto_3);
	}

	TSubclassOf <UMenuTablica> TablicaClass = LoadClass<UMenuTablica>(nullptr, TEXT("/Game/Blueprints/BP_MenuTablica.BP_MenuTablica_C"));
	if (TablicaClass) {
		UE_LOG(LogTemp, Warning, TEXT("Menu Tablica"));
		TablicaInstance = CreateWidget<UMenuTablica>(this, TablicaClass);
		if (TablicaInstance) {
			TablicaInstance->AddToViewport();
		}
	}
	TablicaInstance->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::klinieto_1() {
	UE_LOG(LogTemp, Warning, TEXT("Nacisnieto 1."));
	if (miejsce_w_menu == 0) { //graj
		UE_LOG(LogTemp, Warning, TEXT("Nacisnieto Graj."));
		ustaw_menu_wybor_bloku();
	}
	else if (miejsce_w_menu == 1) { //zestaw standardowy
		zestaw_blokow = 0;
		ustaw_menu_wybor_planszy();
	}
	else if (miejsce_w_menu == 2) { //plansza standardowa 10x20
		rozmiar_planszy = 0;
		ustaw_menu_tryb_gry();
	}
	else if (miejsce_w_menu == 3) { //tryb standardowy
		tryb_gry = 0;
		czy_wybrano = true;
		ustaw_menu_glowne();
		ukryj_menu();
	}
}

void UMenuWidget::klinieto_2() {
	UE_LOG(LogTemp, Warning, TEXT("Nacisnieto 2."));
	if (miejsce_w_menu == 0) { //tablica rekordow
		UE_LOG(LogTemp, Warning, TEXT("Nacisnieto Tablica."));
		czy_kliknieto_tablica = true;
		TablicaInstance->SetVisibility(ESlateVisibility::Visible);
		TablicaInstance->wczytaj_tablice();
		//TablicaInstance->LoadGameInstance->wypisz();
		TablicaInstance->wypisz_tablice_posortowana();
		//TablicaInstance->Menu = this;
		TablicaInstance->czy_powrot = false;
		ukryj_menu();
	}
	else if (miejsce_w_menu == 1) { //zestaw duzych blokow
		UE_LOG(LogTemp, Warning, TEXT("Nacisnieto 2."));
		zestaw_blokow = 1;
		ustaw_menu_wybor_planszy();
	}
	else if (miejsce_w_menu == 2) { //plansza kwadratowa 20x20
		rozmiar_planszy = 1;
		ustaw_menu_tryb_gry();
	}
	else if (miejsce_w_menu == 3) { //tryb ograniczonej liczby blokow
		tryb_gry = 1;
		czy_wybrano = true;
		ustaw_menu_glowne();
		ukryj_menu();
	}
}

void UMenuWidget::klinieto_3() {
	UE_LOG(LogTemp, Warning, TEXT("Nacisnieto 3."));
	if (miejsce_w_menu == 0) { //wyjscie
		UE_LOG(LogTemp, Warning, TEXT("Nacisnieto Wyjscie."));
		czy_kliknieto_wyjscie = true;
		if (GetWorld()->IsGameWorld())
		{
			FGenericPlatformMisc::RequestExit(false);
		}
		else
		{
			UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
		}
	}
	else if (miejsce_w_menu == 1) { //zestaw blokow generowanych losowo
		zestaw_blokow = 2;
		ustaw_menu_wybor_planszy();
	}
	else if (miejsce_w_menu == 2) { //plansza duza 30x20
		rozmiar_planszy = 2;
		ustaw_menu_tryb_gry();
	}
	else if (miejsce_w_menu == 3) { //tryb przetrwania
		tryb_gry = 2;
		czy_wybrano = true;
		ustaw_menu_glowne();
		ukryj_menu();
	}
}

void UMenuWidget::pokaz_menu() {
	czy_wybrano = false;
	czy_kliknieto_tablica = false;
	czy_kliknieto_wyjscie = false;
	this->SetVisibility(ESlateVisibility::Visible);
	//this->AddToViewport();
	//ustaw_menu_glowne();
	
}
void UMenuWidget::ukryj_menu() {
	this->SetVisibility(ESlateVisibility::Hidden);
	//this->RemoveFromViewport();
}

void UMenuWidget::ustaw_menu_glowne() {
	miejsce_w_menu = 0;
	TextBlock_Tytul->SetText(FText::FromString("Falling block"));
	TextBlock_1->SetText(FText::FromString("Graj"));
	TextBlock_2->SetText(FText::FromString("Tablica rekordow"));
	TextBlock_3->SetText(FText::FromString("Wyjscie"));
}

void UMenuWidget::ustaw_menu_wybor_bloku() {
	miejsce_w_menu = 1;
	TextBlock_Tytul->SetText(FText::FromString("Wybor zestawu blokow"));
	TextBlock_1->SetText(FText::FromString("Standardowe bloki"));
	TextBlock_2->SetText(FText::FromString("Duze bloki"));
	TextBlock_3->SetText(FText::FromString("Bloki generowane losowo"));
}

void UMenuWidget::ustaw_menu_wybor_planszy() {
	miejsce_w_menu = 2;
	TextBlock_Tytul->SetText(FText::FromString("Wybor rozmiaru planszy"));
	TextBlock_1->SetText(FText::FromString("Standardowy 10x20"));
	TextBlock_2->SetText(FText::FromString("Kwadrat 20x20"));
	TextBlock_3->SetText(FText::FromString("Duzy 30x20"));
}

void UMenuWidget::ustaw_menu_tryb_gry() {
	miejsce_w_menu = 3;
	TextBlock_Tytul->SetText(FText::FromString("Wybor trybu gry"));
	TextBlock_1->SetText(FText::FromString("Tryb standardowy"));
	TextBlock_2->SetText(FText::FromString("Tryb ograniczonych blokow"));
	TextBlock_3->SetText(FText::FromString("Tryb przetrwania"));
}