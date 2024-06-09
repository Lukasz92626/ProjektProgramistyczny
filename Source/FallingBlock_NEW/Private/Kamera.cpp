// Fill out your copyright notice in the Description page of Project Settings.


#include "Kamera.h"

AKamera::AKamera() {
    SetActorLocation(FVector(0.0f, 0.0f, 1000.0f));
    SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

void AKamera::BeginPlay() {
    Super::BeginPlay();
}