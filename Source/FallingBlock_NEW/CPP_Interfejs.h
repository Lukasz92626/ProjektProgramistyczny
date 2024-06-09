// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPP_Interfejs.generated.h"

class UCPP_WidzetUzytkownika;

/**
 * 
 */
UCLASS()
class FALLINGBLOCK_NEW_API ACPP_Interfejs : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "HUD") TSubclassOf<UCPP_WidzetUzytkownika> HUDWidget;
};
