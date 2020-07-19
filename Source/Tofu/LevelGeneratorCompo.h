// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sector.h"
#include "LevelGeneratorCompo.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOFU_API ULevelGeneratorCompo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelGeneratorCompo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TSubclassOf<ASector> GetRandomSector(bool hasOpenedPosX, bool hasOpenedNegX, bool hasOpenedPosY, bool hasOpenedNegY);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void GenerateLevel(int width, int height, int startX, int startY);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<ASector> GetSector(int x, int y);
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<ASector> > SectorList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ASector> StartingSector;

	UPROPERTY(BlueprintReadOnly)
	int LevelWidth;

	UPROPERTY(BlueprintReadOnly)
	int LevelHeight;
	
	TArray<TSubclassOf<ASector> > SectorGrid;
	TArray<bool> GridHasExpanded;
};
