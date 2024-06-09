// Fill out your copyright notice in the Description page of Project Settings.


#include "Podstawa.h"

// Sets default values
APodstawa::APodstawa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Pozycja.Add(FVector(-100, 0, -100));
	Pozycja.Add(FVector(0, 0, -100));
	Pozycja.Add(FVector(100, 0, -100));
	Pozycja.Add(FVector(-100, 0, 0));
	Pozycja.Add(FVector(0, 0, 0));
	Pozycja.Add(FVector(100, 0, 0));
	Pozycja.Add(FVector(-100, 0, 100));
	Pozycja.Add(FVector(0, 0, 100));
	Pozycja.Add(FVector(100, 0, 100));
}

// Called when the game starts or when spawned
void APodstawa::BeginPlay(){
	Super::BeginPlay();
	
	for (int i = 0; i < 4; ++i) {
		Bloki.Add(GetWorld()->SpawnActor<ABlokAktor>(BP_BlokAktor, GetActorLocation(), GetActorRotation()));
	}
	orientacja = 0;
	set_pozycja();
}

// Called every frame
void APodstawa::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

}

void APodstawa::set_pozycja() {

}

