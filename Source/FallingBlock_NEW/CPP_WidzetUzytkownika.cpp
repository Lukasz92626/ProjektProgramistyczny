// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WidzetUzytkownika.h"

#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

void UCPP_WidzetUzytkownika::set_punkty(float punkty) {
	TextBlock_Punkty_liczba->SetText(FText::AsNumber(punkty));
	TextBlock_Punkty_liczba->SetText(UKismetTextLibrary::Conv_DoubleToText(punkty, ERoundingMode::ToZero));
}


void UCPP_WidzetUzytkownika::set_nr_bloku(int32 numer) {
	TextBlock_Nr_bloku_liczba->SetText(FText::AsNumber(numer));
}

