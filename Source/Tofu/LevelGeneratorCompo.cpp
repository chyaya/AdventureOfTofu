// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGeneratorCompo.h"

// Sets default values for this component's properties
ULevelGeneratorCompo::ULevelGeneratorCompo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevelGeneratorCompo::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULevelGeneratorCompo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ASector* ULevelGeneratorCompo::GetRandomSector(bool hasOpenedPosX, bool hasOpenedNegX, bool hasOpenedPosY, bool hasOpenedNegY)
{
	TArray<ASector*> list;

	for (ASector* sector : SectorList)
	{
		if (sector->HasOpenedPosX == hasOpenedPosX
			&& sector->HasOpenedNegX == hasOpenedNegX
			&& sector->HasOpenedPosY == hasOpenedPosY
			&& sector->HasOpenedNegY == hasOpenedNegY)
		{
			list.Add(sector);
		}
	}

	if (list.Num() == 0)
		return nullptr;

	int randN = FMath::Rand() % list.Num();

	return list[randN];
}

void ULevelGeneratorCompo::GenerateLevel(int width, int height, int startX, int startY)
{
	SectorGrid.SetNum(width*height, false);
	GridHasExpanded.SetNum(width*height, false);

	SectorGrid[width*startY + startX] = StartingSector;

	TArray<TTuple<int, int> > queue;

	queue.Add(MakeTuple(startX, startY));

	while (queue.Num() > 0)
	{
		TTuple<int, int> cur = queue.Pop();
		int x = cur.Get<0>();
		int y = cur.Get<1>();
		int idx = width * y + x;

		if(GridHasExpanded[idx])
			continue;

		ASector* sector = SectorGrid[idx];

		if (sector->HasOpenedPosX)
		{
			queue.Add(MakeTuple(x + 1, y));
		}
		
		if (sector->HasOpenedNegX)
		{
			queue.Add(MakeTuple(x - 1, y));
		}

		if (sector->HasOpenedPosY)
		{
			queue.Add(MakeTuple(x, y + 1));
		}

		if (sector->HasOpenedNegY)
		{
			queue.Add(MakeTuple(x, y - 1));
		}
		
		SectorGrid[idx] = GetRandomSector(
			sector->HasOpenedPosX && x < width - 1,
			sector->HasOpenedNegX && x > 0,
			sector->HasOpenedPosY && y < height - 1,
			sector->HasOpenedNegY && y > 0);

		GridHasExpanded[idx] = true;
	}



	//SectorGrid


}