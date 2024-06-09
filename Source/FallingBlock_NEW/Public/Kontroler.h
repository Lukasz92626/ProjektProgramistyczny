// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlokAktor.h"
#include "Plansza.h"
#include "MenuWidget.h"
#include "Math/UnrealMathUtility.h"
#include "HAL/PlatformProcess.h"
#include "Kontroler.generated.h"

/**
 *
 */
UCLASS()
class FALLINGBLOCK_NEW_API AKontroler : public APlayerController {
	GENERATED_BODY()

public:
	AKontroler();

	UPROPERTY()
	UGlownyWidget* MyWidgetInstance;

	UMenuWidget* MenuInstance;

	void BeginPlay();

	virtual void SetupInputComponent() override;

	//public:
	void ruch_w_prawo_test();
	void ruch_w_lewo_test();

	void obrot_test();
	void opadanie_test();

	void pauza_test();

		// Called every frame
	virtual void Tick(float DeltaTime) override;

	//public:
	int8 szerokosc_planszy; //liczona w blokach
	int8 wysokosc_planszy; //liczona w blokach
	int8 szer_szescianu; //szerokosc pojedynczego szescianu
	int punkty;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_L;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_J;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_S;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_Z;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_T;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_O;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_I;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_blekitny;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Blok")
	TSubclassOf<ABlokAktor> Blok_Aktor_cien;

	UFUNCTION(BlueprintCallable, Category = "Zapis gry")
	void zapisz_tablice();
	UFUNCTION(BlueprintCallable, Category = "Zapis gry")
	void wczytaj_tablice();
	UFUNCTION(BlueprintCallable, Category = "Zapis gry")
	void wczytaj_zapisz_tablice();

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<class UMenuWidget> Menu;

	FVector Wsp_Startu;
	FRotator Rotacja_Standardowa;

	TArray<TArray<ABlokAktor*>> szesciany_na_planszy; //1 wsp x, 2 wsp z
	TArray<ABlokAktor*> szesciany_blok;
	TArray<TArray<int32>> wsp_akt_bloku; //aktualne wsp w "tablicy" z szescianami
	TArray<FVector> poruszanie; //wspolrzedne do dodania do GetActorLocation() aby przesunac blok
	FVector wsp_poczatku; //wspolrzedne do dodania do wsp (0,0,0) aby umiejscowic blok na poczatku

	int8 stadium_gry; //0 - blok nie wygenerowany, 1 - blok wygenerowany i opada, 2 - blok opadl, 3 - gra sie konczy, 4 - gra zakonczona

	int8 rotacja; //od 0 do 3
	TArray<int32> wsp_srodka_akt; //wsp srodka aktualnego bloku
	TArray<int32> wsp_srodka_spawn; //wsp srodka spawn-u
	char blok; //typ bloku (standardowe): L J S Z T O I
	bool czyPauza;
	bool czyPrzesuwane;
	int32 nr_bloku;
	int32 ile_szescianow_bloku;

	TArray<ABlokAktor*> szesciany_cien;
	TArray<TArray<int32>> wsp_cien;

	int8 zestaw_blokow; // 0 - standardowy, 1 - duze bloki, 2 - bloki generowane losowo
	int8 rozmiar_planszy; // 0 - 10x20, 1 - 20x20, 2 - 30x20
	int8 tryb_gry; // 0 - standardowy, 1 - zdobywania okreslonej liczby punktow, 2 - przetrwania

	TArray<ABlokAktor*> Znacznik;
	int32 wsp_znacznik;
	bool czyZatwierdzonoKasowanie;
	bool czyKasowanie;

	int32 limit_blokow; //limit blokow dla trybu ograniczonych blokow
	int32 oczekiwane_punkty; //oczekiwana liczba punktow dla trybu ograniczonych blokow

	//podpowiedz
	TArray<ABlokAktor*> szesciany_podp;
	TArray<TArray<int32>> wsp_podp;
	TArray<int32> wsp_srodka_podp;
	bool czy_podpowiedz;

	AKamera* GlownaKamera;

	void gra_rozpoczeta();

	void ruch_w_prawo();
	void ruch_w_lewo();
	void obrot(); //obrot zgodnie z ruchem wskazowek zegara
	void opadanie();
	void generowanie_bloku();
	void czyszczenie_linii();
	int32 silnia(int32 liczba);
	void pauza();
	void zamiana_bloku();

	void log_liczba(int liczba);
	void log_znak(char znak);
	void log_float(float znak);

	FTimerHandle OpadanieTimer;
	float opadanie_przerwa = 1.0f; // 1.0f najlepiej dla zmiennego w czasie

	void UpdatePunkty();
	void UpdateNrBloku();
	void UpdatePauza();
	void UpdateKoniecGry();
	void WyczyscInformacja();
	void ustaw_do_zdobycia();
	//void wyczysc_do_zdobycia();

	void czyszczenie_planszy();
	void przyspieszanie_opadania();
	void miejsce_opadania();
	void przenoszenie_cienia();
	void usun_cien();

	void generowanie_bloku_standardowego();
	void generowanie_bloku_losowego();
	void generowanie_bloku_duzego();

	void znacznik_w_gore();
	void znacznik_w_dol();
	void kasowanie_zatwierdzenie();
	void interfejs_kasowania_linii();
	void skasuj_linie(int8 nr);

	void tryb_ograniczonych_blokow();
	void tryb_przetrwania();

	void usun_podpowiedz();
	void podpowiedz();
};
