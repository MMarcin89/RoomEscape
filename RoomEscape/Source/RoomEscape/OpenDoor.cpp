// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"





// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//Find owning actor
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	
	//Creat rotator
	FRotator NewRotation = FRotator(0, OpenAngle, 0);
	//Set door rotation
	Owner->SetActorRotation(NewRotation);

}

void UOpenDoor::CloseDoor()
{
	//Set door rotation
	Owner->SetActorRotation(FRotator(0, 0, 0)); //or Creat rotator (look OpenDoor)							
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//poll the trigger volume
	// if the actorThahOpens is in the volume than we open the door
	if (PressurePoint->IsOverlappingActor(ActorThatOpens))
	{

		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	//else if (!PressurePoint->IsOverlappingActor(ActorThatOpens) && (LastDoorOpenTime + DoorCloseDelay <= GetWorld()->GetTimeSeconds()))
	if(GetWorld()->GetTimeSeconds()-LastDoorOpenTime>DoorCloseDelay)
	{
		CloseDoor();
	}
}


