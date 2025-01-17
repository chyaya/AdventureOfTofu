// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

UCLASS()
class TOFU_API ASector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasOpenedPosX = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasOpenedNegX = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasOpenedPosY = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasOpenedNegY = false;
};
