// Fill out your copyright notice in the Description page of Project Settings.


#include "BlokAktor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABlokAktor::ABlokAktor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlokKolizja = CreateDefaultSubobject<UBoxComponent>(TEXT("Blok Kolizja"));
	RootComponent = BlokKolizja;
	BlokModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blok Model Siatki"));
	BlokModel->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABlokAktor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlokAktor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

