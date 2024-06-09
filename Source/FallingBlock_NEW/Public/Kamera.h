// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Kamera.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API AKamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	AKamera();

	virtual void BeginPlay() override;
};
