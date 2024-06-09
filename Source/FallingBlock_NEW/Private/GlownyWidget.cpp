// Fill out your copyright notice in the Description page of Project Settings.


#include "GlownyWidget.h"

UGlownyWidget::UGlownyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UGlownyWidget::NativeConstruct()
{
    Super::NativeConstruct();

    InitializeWidget();
}

void UGlownyWidget::InitializeWidget(){
    /*if (TextBlock_Title)
    {
        TextBlock_Title->SetText(FText::FromString("Podstawowe informacje"));
    }*/
}

//void UGlownyWidget::ustaw_punkty(int32 punkty) {
//    UE_LOG(LogTemp, Warning, TEXT("Zmiana punktow. GlownyWidget"));
//    if (TextBlock_Punkty_liczba) {
//        TextBlock_Punkty_liczba->SetText(FText::AsNumber(punkty));
//        //TextBlock_Punkty_liczba->SetText(FText::AsNumber(punkty));
//    }
//    else {
//        UE_LOG(LogTemp, Error, TEXT("nie ustawiono punktow"));
//    }
//}