// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Public/WorldCollision.h"




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

	//UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty "));

	///look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No %s component"), *(GetOwner()->GetName()));
	}
	///look for atached input component
	PawnInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT(" %s component reporting"), *(GetOwner()->GetName()));
		//bind the input action
		PawnInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("No %s component"), *(GetOwner()->GetName()));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// get player view point this tick
	FVector OwnerLocation;
	FRotator OwnerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OwnerLocation, OwnerRotator);
	
	//UE_LOG(LogTemp, Warning, TEXT("Pozycja %s , rotacja %s"), *OwnerLocation.ToString(),*OwnerRotator.ToString());

	
	//get end of our reach
	 FVector TraceLineEnd = OwnerLocation + (OwnerRotator.Vector()*Reach);
	 ///draw a red trace in the world to visualize
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

	///setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	///set a line-trace  to  reach distance
	FHitResult ThisHitResult;
	GetWorld()->LineTraceSingleByObjectType
	(
		ThisHitResult,
		OwnerLocation,
		TraceLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters

	);
	AActor* HitActor = ThisHitResult.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Zdezyles sie z %s"), *(HitActor->GetName()));
	}
	///see what we hit
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabb key pressed"));
}

