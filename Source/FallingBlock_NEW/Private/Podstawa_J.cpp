// Fill out your copyright notice in the Description page of Project Settings.


#include "Podstawa_J.h"
#include "BlokAktor.h"

void APodstawa_J::BeginPlay() {
	Super::BeginPlay();
	orientacja = 2; //(zmiana orientacji dla testu)
	set_pozycja();
}

APodstawa_J::APodstawa_J() {
	PrimaryActorTick.bCanEverTick = true;
	Pozycja.Empty();
	//Prawo, Ty�, G�ra
	//012
	//345
	//678
	Pozycja.Add(FVector(-100, 0, 100)); //0
	Pozycja.Add(FVector(0, 0, 100)); //1
	Pozycja.Add(FVector(100, 0, 100)); //2
	Pozycja.Add(FVector(-100, 0, 0)); //3
	Pozycja.Add(FVector(0, 0, 0)); //4
	Pozycja.Add(FVector(100, 0, 0)); //5
	Pozycja.Add(FVector(-100, 0, -100)); //6
	Pozycja.Add(FVector(0, 0, -100)); //7
	Pozycja.Add(FVector(100, 0, -100)); //8
}


void APodstawa_J::set_pozycja() {
	Super::set_pozycja();
	switch (orientacja) {
	case 0:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[1]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[4]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[7]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[6]);
		break; //stoi
	case 1:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[3]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[6]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[7]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[8]);
		break; //lezy na brzuchu
	case 2:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[0]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[3]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[6]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[1]);
		break; //do gory nogami
	case 3:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[3]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[8]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[4]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[5]);
		break; //lezy na plecach
	}
}