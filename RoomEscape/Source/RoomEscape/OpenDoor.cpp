// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"




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
	
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//poll the trigger volume
		// if the actorThahOpens is in the volume than we open the door
	if (GetTotalMassOfActorsOnPressurePoint()>TriggerMassNeeded)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}
float UOpenDoor::GetTotalMassOfActorsOnPressurePoint()
{
	float TotalMass = 0.f;

	
	//znajdz pokrywajacych sie aktorow
	if (PressurePoint==nullptr) { UE_LOG(LogTemp, Error, TEXT("no pressurepoint component connected to %s"), *GetOwner()->GetName()) return TotalMass; }
	
	TArray<AActor*> OverlappingActors;
	PressurePoint->GetOverlappingActors(OverlappingActors);
	
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

FVector UOpenDoor::GetStartLocation()
{
	return GetOwner()->GetActorLocation();
}