// Fill out your copyright notice in the Description page of Project Settings.


#include "Podstawa_I.h"
#include "BlokAktor.h"

void APodstawa_I::BeginPlay() {
	Super::BeginPlay();
	orientacja = 1; //(zmiana orientacji dla testu)
	set_pozycja();
}

APodstawa_I::APodstawa_I() {
	PrimaryActorTick.bCanEverTick = true;
	Pozycja.Empty();
	//Prawo, Ty³, Góra
	//9
	//012
	//345
	//678[10]
	Pozycja.Add(FVector(-100, 0, 100)); //0
	Pozycja.Add(FVector(0, 0, 100)); //1
	Pozycja.Add(FVector(100, 0, 100)); //2
	Pozycja.Add(FVector(-100, 0, 0)); //3
	Pozycja.Add(FVector(0, 0, 0)); //4
	Pozycja.Add(FVector(100, 0, 0)); //5
	Pozycja.Add(FVector(-100, 0, -100)); //6
	Pozycja.Add(FVector(0, 0, -100)); //7
	Pozycja.Add(FVector(100, 0, -100)); //8
	Pozycja.Add(FVector(-100, 0, 200)); //9
	Pozycja.Add(FVector(200, 0, -100)); //10
}


void APodstawa_I::set_pozycja() {
	Super::set_pozycja();
	switch (orientacja) {
	case 0:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[6]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[7]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[8]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[10]);
		break; //lezy
	case 1:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[9]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[0]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[3]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[6]);
		break; //stoi
	case 2:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[6]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[7]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[8]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[10]);
		break; //lezy
	case 3:
		Bloki[0]->SetActorLocation(GetActorLocation() + Pozycja[9]);
		Bloki[1]->SetActorLocation(GetActorLocation() + Pozycja[0]);
		Bloki[2]->SetActorLocation(GetActorLocation() + Pozycja[3]);
		Bloki[3]->SetActorLocation(GetActorLocation() + Pozycja[6]);
		break; //stoi
	}
}

