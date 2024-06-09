// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuTablica.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"
#include "TablicaRekordowSaveGame.h"

void UMenuTablica::NativeConstruct() {
	Super::NativeConstruct();
	LoadGameInstance = nullptr;


	if (Button_Poprzednia) {
		Button_Poprzednia->OnClicked.AddDynamic(this, &UMenuTablica::klinieto_poprzednia);
	}
	if (Button_Nastepna) {
		Button_Nastepna->OnClicked.AddDynamic(this, &UMenuTablica::klinieto_nastepna);
	}
	if (Button_Powrot) {
		Button_Powrot->OnClicked.AddDynamic(this, &UMenuTablica::klinieto_powrot);
	}
	min_idx = 0;
	czy_powrot = false;
}

void UMenuTablica::klinieto_poprzednia() {
	if (min_idx - 10 >= 0) {
		min_idx -= 10;
		wypisz_tablice_posortowana();
	}
}

void UMenuTablica::klinieto_nastepna() {
	if (min_idx + 10 < punkty.Num()) {
		min_idx += 10;
		wypisz_tablice_posortowana();
	}
}

void UMenuTablica::klinieto_powrot() {
	this->SetVisibility(ESlateVisibility::Hidden);
	czy_powrot = true;
	//Menu->SetVisibility(ESlateVisibility::Visible);
}

void UMenuTablica::wypisz_tablice_posortowana() {
	wyczysc_tablice();
	if (LoadGameInstance->punkty.Num() == 0)
		return;
	sortuj_dane();
	int32 i = min_idx;
	
	if (i >= punkty.Num())
		return;
	TextBlock_Numer_1->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_1->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_1->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_1->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_1->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_1->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_2->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_2->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_2->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_2->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_2->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_2->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_3->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_3->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_3->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_3->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_3->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_3->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_4->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_4->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_4->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_4->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_4->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_4->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_5->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_5->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_5->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_5->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_5->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_5->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_6->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_6->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_6->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_6->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_6->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_6->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_7->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_7->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_7->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_7->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_7->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_7->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_8->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_8->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_8->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_8->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_8->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_8->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_9->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_9->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_9->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_9->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_9->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_9->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;

	if (i >= punkty.Num())
		return;
	TextBlock_Numer_10->SetText(FText::AsNumber(i+1));
	TextBlock_Punkty_10->SetText(FText::AsNumber(punkty[i]));
	if (tryb[i] == 0)
		TextBlock_Tryb_10->SetText(FText::FromString("normalny"));
	else if (tryb[i] == 1)
		TextBlock_Tryb_10->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_10->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_10->SetText(FText::FromString(data_godzina[i].ToString()));
	++i;
}

void UMenuTablica::wypisz_tablice() {
	wyczysc_tablice();
	if (LoadGameInstance->punkty.Num() == 0)
		return;
	int32 i = min_idx;
	UE_LOG(LogTemp, Warning, TEXT("Wypisz_tablice."));
	FText tmp = FText::AsNumber(LoadGameInstance->punkty.Num());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tmp.ToString());
	if (i >= LoadGameInstance->punkty.Num())
		return;
	UE_LOG(LogTemp, Warning, TEXT("Pierwszy if."));
	TextBlock_Numer_1->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_1->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_1->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_1->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_1->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_1->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_2->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_2->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_2->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_2->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_2->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_2->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_3->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_3->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_3->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_3->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_3->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_3->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_4->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_4->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_4->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_4->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_4->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_4->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_5->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_5->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_5->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_5->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_5->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_5->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_6->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_6->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_6->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_6->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_6->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_6->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_7->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_7->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_7->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_7->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_7->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_7->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_8->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_8->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_8->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_8->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_8->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_8->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_9->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_9->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_9->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_9->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_9->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_9->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;

	if (i >= LoadGameInstance->punkty.Num())
		return;
	TextBlock_Numer_10->SetText(FText::AsNumber(i + 1));
	TextBlock_Punkty_10->SetText(FText::AsNumber(LoadGameInstance->punkty[i]));
	if (LoadGameInstance->tryb[i] == 0)
		TextBlock_Tryb_10->SetText(FText::FromString("normalny"));
	else if (LoadGameInstance->tryb[i] == 1)
		TextBlock_Tryb_10->SetText(FText::FromString("ogr. blokow"));
	else
		TextBlock_Tryb_10->SetText(FText::FromString("przetrwania"));
	TextBlock_Data_10->SetText(FText::FromString(LoadGameInstance->data_godzina[i].ToString()));
	++i;
}

void UMenuTablica::wyczysc_tablice() {
	TextBlock_Numer_1->SetText(FText::FromString(""));
	TextBlock_Punkty_1->SetText(FText::FromString(""));
	TextBlock_Tryb_1->SetText(FText::FromString(""));
	TextBlock_Data_1->SetText(FText::FromString(""));

	TextBlock_Numer_2->SetText(FText::FromString(""));
	TextBlock_Punkty_2->SetText(FText::FromString(""));
	TextBlock_Tryb_2->SetText(FText::FromString(""));
	TextBlock_Data_2->SetText(FText::FromString(""));

	TextBlock_Numer_3->SetText(FText::FromString(""));
	TextBlock_Punkty_3->SetText(FText::FromString(""));
	TextBlock_Tryb_3->SetText(FText::FromString(""));
	TextBlock_Data_3->SetText(FText::FromString(""));

	TextBlock_Numer_4->SetText(FText::FromString(""));
	TextBlock_Punkty_4->SetText(FText::FromString(""));
	TextBlock_Tryb_4->SetText(FText::FromString(""));
	TextBlock_Data_4->SetText(FText::FromString(""));

	TextBlock_Numer_5->SetText(FText::FromString(""));
	TextBlock_Punkty_5->SetText(FText::FromString(""));
	TextBlock_Tryb_5->SetText(FText::FromString(""));
	TextBlock_Data_5->SetText(FText::FromString(""));

	TextBlock_Numer_6->SetText(FText::FromString(""));
	TextBlock_Punkty_6->SetText(FText::FromString(""));
	TextBlock_Tryb_6->SetText(FText::FromString(""));
	TextBlock_Data_6->SetText(FText::FromString(""));

	TextBlock_Numer_7->SetText(FText::FromString(""));
	TextBlock_Punkty_7->SetText(FText::FromString(""));
	TextBlock_Tryb_7->SetText(FText::FromString(""));
	TextBlock_Data_7->SetText(FText::FromString(""));

	TextBlock_Numer_8->SetText(FText::FromString(""));
	TextBlock_Punkty_8->SetText(FText::FromString(""));
	TextBlock_Tryb_8->SetText(FText::FromString(""));
	TextBlock_Data_8->SetText(FText::FromString(""));

	TextBlock_Numer_9->SetText(FText::FromString(""));
	TextBlock_Punkty_9->SetText(FText::FromString(""));
	TextBlock_Tryb_9->SetText(FText::FromString(""));
	TextBlock_Data_9->SetText(FText::FromString(""));

	TextBlock_Numer_10->SetText(FText::FromString(""));
	TextBlock_Punkty_10->SetText(FText::FromString(""));
	TextBlock_Tryb_10->SetText(FText::FromString(""));
	TextBlock_Data_10->SetText(FText::FromString(""));
}

void UMenuTablica::wczytaj_tablice() {
	LoadGameInstance = Cast<UTablicaRekordowSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TablicaSaveSlot"), 0));
	//LoadGameInstance->czyszczenie();///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//sortuj_dane();
}

void UMenuTablica::sortuj_dane() {
	if (LoadGameInstance->punkty.Num() == 0)
		return;
	punkty.Empty();
	tryb.Empty();
	data_godzina.Empty();
	for (int32 i = 0; i < LoadGameInstance->punkty.Num(); ++i) {
		punkty.Add(LoadGameInstance->punkty[i]);
		tryb.Add(LoadGameInstance->tryb[i]);
		data_godzina.Add(LoadGameInstance->data_godzina[i]);
	}
	for (int32 i = 1; i < punkty.Num(); ++i) {
		int32 key = punkty[i];
		int32 key_t = tryb[i];
		FDateTime key_data = data_godzina[i];
		int j = i - 1;
		while (j >= 0 && punkty[j] < key) {
			punkty[j + 1] = punkty[j];
			tryb[j + 1] = tryb[j];
			data_godzina[j + 1] = data_godzina[j];

			j = j - 1;
		}
		punkty[j + 1] = key;
		tryb[j + 1] = key_t;
		data_godzina[j + 1] = key_data;
	}
	UE_LOG(LogTemp, Warning, TEXT("Posortowane:"));
	for (int i = 0; i < punkty.Num(); ++i) {
		UE_LOG(LogTemp, Warning, TEXT("%d %d %s"), punkty[i], tryb[i], *data_godzina[i].ToString());
	}
}