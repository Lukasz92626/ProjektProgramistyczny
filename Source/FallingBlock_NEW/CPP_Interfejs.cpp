//#include <iostream>
//#include <fstream>

// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Interfejs.h"
#include "CPP_WidzetUzytkownika.h"

void ACPP_Interfejs::BeginPlay()
{
    //std::ofstream plik("moj_plik.txt");

    //// Sprawdzenie, czy plik zosta� poprawnie otwarty
    //if (plik.is_open()) {
    //    // Zapisanie danych do pliku
    //    plik << "To jest tekst zapisany w pliku.\n";
    //    plik << "Mo�na tutaj napisa� wi�cej tekstu lub inne dane.\n";

    //    // Zamkni�cie pliku
    //    plik.close();
    //    //std::cout << "Plik zosta� pomy�lnie zapisany.\n";
    //}
    //else {
    //    //std::cout << "B��d podczas otwierania pliku!\n";
    //}

	UCPP_WidzetUzytkownika* widget = CreateWidget<UCPP_WidzetUzytkownika>(GetWorld()->GetFirstPlayerController(), HUDWidget);
	widget->AddToViewport();
	widget->set_punkty(100.f);
	widget->set_nr_bloku(150190);
}