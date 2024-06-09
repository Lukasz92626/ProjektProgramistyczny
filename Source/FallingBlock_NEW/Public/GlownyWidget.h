// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "GlownyWidget.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API UGlownyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UGlownyWidget(const FObjectInitializer& ObjectInitializer);
    
    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* CanvasPanel_11;

    UPROPERTY(meta = (BindWidget))
    class UOverlay* Overlay_0;

    UPROPERTY(meta = (BindWidget))
    class UImage* Image_0;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* VerticalBox_Main;

    //Title
    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* VerticalBox_Title;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_Title;
    
    //Punkty
    UPROPERTY(meta = (BindWidget))
    class UHorizontalBox* HorizontalBox_Punkty;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_Punkty_nazwa;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_Punkty_liczba;

    //Numer bloku
    UPROPERTY(meta = (BindWidget))
    class UHorizontalBox* HorizontalBox_Nr_bloku;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_Nr_bloku_nazwa;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_Nr_bloku_liczba;

    //Informacja
    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* VerticalBox_Informacja;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_Informacja;

    void InitializeWidget();

    virtual void NativeConstruct() override;

   /* void ustaw_punkty(int32 punkty);*/
};
