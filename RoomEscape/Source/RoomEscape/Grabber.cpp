// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty "));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get player view point this tick
	FVector OwnerLocation;
	FRotator OwnerRotator;
	 GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OwnerLocation, OwnerRotator);
	
	//UE_LOG(LogTemp, Warning, TEXT("Pozycja %s , rotacja %s"), *OwnerLocation.ToString(),*OwnerRotator.ToString());

	//draw a red trace in the world to visualize

	 FVector TraceLineEnd = OwnerLocation + (OwnerRotator.Vector()*Reach);
	
	DrawDebugLine
	(
		GetWorld(),
		OwnerLocation,
		TraceLineEnd,
		FColor(255, 0, 0),
		false,
		0,
		0,
		10

		);
	// ray-cast out to rich distance

	//see what we hit
}

