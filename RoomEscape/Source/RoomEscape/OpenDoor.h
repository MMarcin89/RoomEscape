// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnCloseRequest;
	
	
private:
	
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePoint=nullptr;
	UPROPERTY(EditAnywhere)
		float TriggerMassNeeded=40.f;
			
		AActor *Owner=nullptr;
		
				
		float GetTotalMassOfActorsOnPressurePoint();

		UFUNCTION(BlueprintCallable)
			FVector GetStartLocation();
};
