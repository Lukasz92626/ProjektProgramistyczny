// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlokAktor.h"
#include "Math/UnrealMathUtility.h"
#include "HAL/PlatformProcess.h"
#include "Plansza.generated.h"

UCLASS()
class FALLINGBLOCK_NEW_API APlansza : public AActor
{
	GENERATED_BODY()

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	int8 szerokosc_planszy; //liczona w blokach
	int8 wysokosc_planszy; //liczona w blokach
	int8 szer_szescianu; //szerokosc pojedynczego szescianu
	int8 punkty;
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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Atrybut")
	float czasMiedzyRuchem = .0125f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Atrybut")
	float czasMiedzyOpadaniem = .00625f;
	TArray<TArray<ABlokAktor*>> szesciany_na_planszy; //1 wsp x, 2 wsp z
	TArray<ABlokAktor*> szesciany_blok;
	TArray<TArray<int32>> wsp_akt_bloku; //aktualne wsp w "tablicy" z szescianami
	TArray<FVector> poruszanie; //wspolrzedne do dodania do GetActorLocation() aby przesunac blok
	FVector wsp_poczatku; //wspolrzedne do dodania do GetActorLocation() aby umiejscowic blok na poczatku

	int8 stadium_gry; //0 - blok nie wygenerowany, 1 - blok wygenerowany i opada, 2 - blok opadl, 3 - gra sie konczy, 4 - gra zakonczona

	int8 rotacja; //od 0 do 3
	TArray<int32> wsp_srodka_akt; //wsp srodka aktualnego bloku
	char blok; //typ bloku: L J S Z T O I
	bool czyPauza;
	bool czyPrzesuwane;

	/*UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Atrybut")
	TArray<ABlokAktor*> Bloki;*/
	/*UPROPERTY(VisibleAnywhere, Category = "Atrybut")
	int8 orientacja = 0;*/
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Atrybut")
	//float przerwa = 100.f;
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Atrybut")
	//bool czyOpada = false;
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Atrybut")
	//bool czyZakonczonoOpadanie = false;
	//FVector inputLoc; //!!!!!!!!!!!!!!!!!!!!!

	// Sets default values for this actor's properties
	APlansza();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ruch_w_prawo();
	void ruch_w_lewo();
	void obrot(); //obrot zgodnie z ruchem wskazowek zegara
	void opadanie();
	void generowanie_bloku();
	void czyszczenie_linii();
	int8 silnia(int8 liczba);
	void pauza();
	//virtual void set_pozycja(FVector npozycja);
	//virtual void set_inputLoc(FVector ninputLoc);
	//virtual void spadek();
	//virtual void czyKoliduje();
	//FORCEINLINE virtual bool get_czyZakonczonoOpadanie() const { return czyZakonczonoOpadanie; }
	//FORCEINLINE virtual bool get_czyOpada() const { return czyOpada; }
	//virtual TArray<ABlokAktor*> set_KolizjaStatyczna();
	//ZMIENIC
	//virtual void set_inputLoc(FVector ninputLoc);
	//virtual void rotacja_zgodna(); //rotacja zgodna z ruchem waskazowek zegara
	//virtual void rotacja_niezgodna(); //rotacja niezgodna z ruchem waskazowek zegara
	//virtual void nor_rotacja();
	//virtual void ruch(FVector kierunek, FVector poprz_poz);
	//virtual void ruch_w_lewo();
	//virtual void ruch_w_prawo();
	//virtual void ruch_w_gore();
	//virtual void ruch_w_dol();
	//virtual void sprawdz_obrocona_pozycje(FVector pozycja);
	//virtual bool znajdzLepszyObrot();
	FTimerHandle RuchXTimer;
	FTimerHandle RuchYTimer;
};
