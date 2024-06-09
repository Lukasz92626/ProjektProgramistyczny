// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlokAktor.generated.h"

UCLASS()
class FALLINGBLOCK_NEW_API ABlokAktor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlokAktor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//protected:
	// Called when the game starts or when spawned
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	class UStaticMeshComponent* BlokModel;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ATTRIBUTES")
	class UBoxComponent* BlokKolizja;
	virtual void BeginPlay() override;
};
