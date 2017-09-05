// Fill out your copyright notice in the Description page of Project Settings.

#include "SlideDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
USlideDoor::USlideDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlideDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	bisdoorclosed = true;
	StartLocation = Owner->GetActorLocation();
}


// Called every frame
void USlideDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActorThatOpens->IsOverlappingActor(PressurePoint) && bisdoorclosed)
	{
		OpenDoor();
	}

	if (ActorThatOpens->IsOverlappingActor(PressurePoint1))
	{
		CloseDoor();
	}

}


void USlideDoor::OpenDoor()
{
	FVector NewLocation = Owner->GetActorLocation() + FVector(0, DistanceToMove, 0);
	FHitResult *ThisHit=nullptr;
		Owner->SetActorLocation(
		NewLocation,
		false,
		ThisHit,
		ETeleportType::None);
		bisdoorclosed = false;
}

void USlideDoor::CloseDoor()
{
	FHitResult *ThisHit = nullptr;
	Owner->SetActorLocation(
		StartLocation,
		false,
		ThisHit,
		ETeleportType::None);
		bisdoorclosed = true;

	
}


