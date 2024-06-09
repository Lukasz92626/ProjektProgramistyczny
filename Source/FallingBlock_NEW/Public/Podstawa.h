// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlokAktor.h"
#include "Podstawa.generated.h"

UCLASS()
class FALLINGBLOCK_NEW_API APodstawa : public AActor
{
	GENERATED_BODY()

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	TSubclassOf<ABlokAktor> BP_BlokAktor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	float czasMiedzyRuchem = .0125f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	float czasMiedzyOpadaniem = .00625f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	TArray<ABlokAktor*> Bloki;

	UPROPERTY(VisibleAnywhere, Category = "ATTRIBUTES")
	int8 orientacja = 0;
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	//float przerwa = 100.f;
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	//bool czyOpada = false;
	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	//bool czyZakonczonoOpadanie = false;
	TArray<FVector> Pozycja;
	//FVector inputLoc; //!!!!!!!!!!!!!!!!!!!!!

	// Sets default values for this actor's properties
	APodstawa();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
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
	virtual void set_pozycja();
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
