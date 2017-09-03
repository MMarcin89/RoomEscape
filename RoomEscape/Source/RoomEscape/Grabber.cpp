// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "Public/WorldCollision.h"




// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	FindAndBindInput();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get player view point this tick
	FVector OwnerLocation;
	FRotator OwnerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OwnerLocation, OwnerRotator);

	//get end of our reach
	FVector TraceLineEnd = OwnerLocation + (OwnerRotator.Vector()*Reach);
	//setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	//set a line-trace  to  reach distance
	FHitResult ThisHitResult;
	GetWorld()->LineTraceSingleByObjectType
	(
		ThisHitResult,
		OwnerLocation,
		TraceLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters

	);

	//if the physics handle is attached 
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(TraceLineEnd);
	}
		//move the object that we/re holding

}

///look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No %s component"), *(GetOwner()->GetName()));
	}
}
///look for atached input component
void UGrabber::FindAndBindInput() {
	PawnInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT(" %s component reporting"), *(GetOwner()->GetName()));
		//bind the input action
		PawnInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		PawnInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No %s component"), *(GetOwner()->GetName()));
	}
}
void UGrabber::Grab()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grabb key pressed"));
	
	//Line-trace to see if we reach any actors with physics body collision channell
	auto HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	
	// if we hit than attach physics handle
	if (ActorHit) {
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			GetOwner()->GetActorRotation()
		);
	}
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabb key released"));
	//TODO release physics handle
	PhysicsHandle->ReleaseComponent();
}



const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	// get player view point this tick
	FVector OwnerLocation;
	FRotator OwnerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OwnerLocation, OwnerRotator);

	//get end of our reach
	FVector TraceLineEnd = OwnerLocation + (OwnerRotator.Vector()*Reach);
	//setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	//set a line-trace  to  reach distance
	FHitResult ThisHitResult;
	GetWorld()->LineTraceSingleByObjectType
	(
		ThisHitResult,
		OwnerLocation,
		TraceLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters

	);
	///see what we hit
	AActor* HitActor = ThisHitResult.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Zdezyles sie z %s"), *(HitActor->GetName()));
	}
	return ThisHitResult;
}
