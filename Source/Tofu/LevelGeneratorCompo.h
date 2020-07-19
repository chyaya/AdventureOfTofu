// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sector.h"
#include "LevelGeneratorCompo.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOFU_API ULevelGeneratorCompo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelGeneratorCompo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void GenerateLevel(int width, int height, int startX, int startY);


	ASector* GetRandomSector(bool hasOpenedPosX, bool hasOpenedNegX, bool hasOpenedPosY, bool hasOpenedNegY);


	UPROPERTY(BlueprintReadWrite)
	TArray<ASector*> SectorList;

	UPROPERTY(BlueprintReadWrite)
	ASector* StartingSector;
	
	TArray<ASector*> SectorGrid;
	TArray<bool> GridHasExpanded;
};
