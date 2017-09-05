// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "SlideDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API USlideDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlideDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePoint = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePoint1 = nullptr;
	UPROPERTY(EditAnywhere)
		AActor *ActorThatOpens = nullptr;
	
	AActor* Owner = nullptr;
	float DistanceToMove = -100.f;
	void OpenDoor();
	void CloseDoor();
	bool bisdoorclosed;
	FVector StartLocation;
};
