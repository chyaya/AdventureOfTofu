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

TSubclassOf<ASector> ULevelGeneratorCompo::GetRandomSector(bool hasOpenedPosX, bool hasOpenedNegX, bool hasOpenedPosY, bool hasOpenedNegY)
{
	TArray<TSubclassOf<ASector> > list;

	for (TSubclassOf<ASector> subclass : SectorList)
	{
		ASector* sector = Cast<ASector>(subclass->ClassDefaultObject);

			if (sector->HasOpenedPosX == hasOpenedPosX
				&& sector->HasOpenedNegX == hasOpenedNegX
				&& sector->HasOpenedPosY == hasOpenedPosY
				&& sector->HasOpenedNegY == hasOpenedNegY)
			{
				list.Add(subclass);
			}
	}

	if (list.Num() == 0)
		return nullptr;

	int randN = FMath::Rand() % list.Num();

	return list[randN];
}

TSubclassOf<ASector> ULevelGeneratorCompo::GetSector(int x, int y)
{
	return SectorGrid[LevelWidth*y + x];
}

void ULevelGeneratorCompo::GenerateLevel(int width, int height, int startX, int startY)
{
	LevelWidth = width;
	LevelHeight = height;

	SectorGrid.SetNum(width*height, false);
	GridHasExpanded.SetNum(width*height, false);

	TArray<TTuple<int, int> > queue;

	SectorGrid[width*startY + startX] = StartingSector;
	GridHasExpanded[width*startY + startX] = true;

	if (nullptr == StartingSector)
		return;

	ASector* ssector = Cast<ASector>(StartingSector->ClassDefaultObject);

	if (ssector->HasOpenedPosX)	queue.Add(MakeTuple(startX + 1, startY));
	if (ssector->HasOpenedNegX)	queue.Add(MakeTuple(startX - 1, startY));
	if (ssector->HasOpenedPosY)	queue.Add(MakeTuple(startX, startY + 1));
	if (ssector->HasOpenedNegY)	queue.Add(MakeTuple(startX, startY - 1));

	TTuple<int, int> dir[4] = { MakeTuple(1, 0), MakeTuple(-1, 0), MakeTuple(0, 1), MakeTuple(0, -1) };

	while (queue.Num() > 0)
	{
		TTuple<int, int> cur = queue.Pop();
		int x = cur.Get<0>();
		int y = cur.Get<1>();
		int idx = width * y + x;

		if (GridHasExpanded[idx])
			continue;

		bool open[4] = { false, };

		for (int i = 0; i < 4; ++i)
		{
			auto dx = dir[i].Get<0>();
			auto dy = dir[i].Get<1>();

			if (dx < 0)	open[i] = x > 0;
			if (dx > 0)	open[i] = x < width - 1;
			if (dy < 0)	open[i] = y > 0;
			if (dy > 0)	open[i] = y < height - 1;

			if (open[i])
			{
				TSubclassOf<ASector> subc = SectorGrid[width*(y + dy) + (x + dx)];
				
				if (subc)
				{
					ASector* s = Cast<ASector>(subc->ClassDefaultObject);

					if (dx > 0)			open[i] = s->HasOpenedNegX;
					else if (dx < 0)	open[i] = s->HasOpenedPosX;
					else if (dy > 0)	open[i] = s->HasOpenedNegY;
					else if (dy < 0)	open[i] = s->HasOpenedPosY;
				}
				else
				{
					open[i] = FMath::RandBool();
				}
			}
		}

		TSubclassOf<ASector> randSubclass = GetRandomSector(open[0], open[1], open[2], open[3]);
		ASector* randSector = Cast<ASector>(randSubclass->ClassDefaultObject);

		if (randSector->HasOpenedPosX)	queue.Add(MakeTuple(x + 1, y));
		if (randSector->HasOpenedNegX)	queue.Add(MakeTuple(x - 1, y));
		if (randSector->HasOpenedPosY)	queue.Add(MakeTuple(x, y + 1));
		if (randSector->HasOpenedNegY)	queue.Add(MakeTuple(x, y - 1));

		SectorGrid[idx] = randSubclass;
		GridHasExpanded[idx] = true;
	}


}