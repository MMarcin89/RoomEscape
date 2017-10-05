// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float Power = 0;
	float MaxPower = 1000;
private:
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent *PawnInputComponent = nullptr;
		
	//RAy-cast and grab what's in reach
	void Grab();
	void SetPower();
	void Release();

	//Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();

	//setup (assumed) attached input component
	void FindAndBindInput();

	//return hit for first physics body with collision channel in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
	FVector GetTraceLineEnd();
	FVector GetPlayerViewPointLocation();
	UPrimitiveComponent* ComponentToGrab;
	float CurrentPower;
	bool bKeyPressed;
	bool bIsPowerGrowing;
	
	UFUNCTION(BlueprintCallable)
		float GetCurrentPower();

	UFUNCTION(BlueprintPure)
		float GetCurrentPowerPercent();
};
