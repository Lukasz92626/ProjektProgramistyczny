// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_WidzetUzytkownika.generated.h"


class UCanvasPanel;
class UOverlay;
class UImage;
class UVerticalBox;
class UTextBlock;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API UCPP_WidzetUzytkownika : public UUserWidget
{
	GENERATED_BODY()
public:
	//Glowne
	UPROPERTY(meta = (BindWidget)) UCanvasPanel* CanvasPanel_11;
	UPROPERTY(meta = (BindWidget)) UOverlay* Overlay_0;
	UPROPERTY(meta = (BindWidget)) UImage* Image_0;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* VerticalBox_Main;
	
	//Tytul
	UPROPERTY(meta = (BindWidget)) UVerticalBox* VerticalBox_Title;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_Title;

	//Punkty
	UPROPERTY(meta = (BindWidget)) UHorizontalBox* HorizontalBox_Punkty;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_Punkty_nazwa;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UTextBlock* TextBlock_Punkty_liczba;
	
	//Numer bloku
	UPROPERTY(meta = (BindWidget)) UHorizontalBox* HorizontalBox_Nr_bloku;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_Nr_bloku_nazwa;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UTextBlock* TextBlock_Nr_bloku_liczba;

	//Metody
	void set_punkty(float punkty);
	void set_nr_bloku(int32 numer);
	

	//virtual void NativeConstruct() override {
	//	Super::NativeConstruct();

	//	FString TextValue = "121";

	//	set_punkty(121);
	//	set_nr_bloku(1);

	//	//// Przypisz TextBlock, korzystaj¹c z jego nazwy nadanej w edytorze Blueprint.
	//	//TextBlock_Punkty_liczba = Cast<UTextBlock>(GetWidgetFromName(TEXT("YourTextBlockName")));

	//	//// SprawdŸ, czy uda³o siê poprawnie przypisaæ TextBlock.
	//	//if (TextBlock_Punkty_liczba)
	//	//{
	//	//	// Ustaw tekst w TextBlocku.
	//	//	TextBlock_Punkty_liczba->SetText(FText::FromString(TextValue));
	//	//}
	//}
};
