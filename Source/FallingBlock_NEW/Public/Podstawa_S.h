// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Podstawa.h"
#include "Podstawa_S.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API APodstawa_S : public APodstawa
{
	GENERATED_BODY()
	
public:
	APodstawa_S();
	void BeginPlay() override;
	void set_pozycja() override;

};
