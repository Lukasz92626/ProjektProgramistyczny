// Fill out your copyright notice in the Description page of Project Settings.


#include "TablicaRekordowSaveGame.h"

UTablicaRekordowSaveGame::UTablicaRekordowSaveGame()
{
    //punkty = 0;
    //tryb = 0;
    //data_godzina = FDateTime::Now();
}

void UTablicaRekordowSaveGame::czyszczenie() {
    punkty.Empty();
    tryb.Empty();
    data_godzina.Empty();
}

void UTablicaRekordowSaveGame::wypisz() {
    UE_LOG(LogTemp, Warning, TEXT("Tablica rekordow:"));
    UE_LOG(LogTemp, Warning, TEXT("%d"), punkty.Num());
    //for (int i = 0; i < punkty.Num(); ++i) {
    //    UE_LOG(LogTemp, Warning, TEXT("%d %d %s"), punkty[i], tryb[i], *data_godzina[i].ToString());
    //    /*UE_LOG(LogTemp, Warning, TEXT("Punkty: %d"), punkty[i]);
    //    UE_LOG(LogTemp, Warning, TEXT("Tryb gry: %d"), tryb[i]);
    //    UE_LOG(LogTemp, Warning, TEXT("Tryb gry: %s"), *data_godzina[i].ToString());*/
    //}
}