// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "SlideDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWallPanel);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API USlideDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlideDoor();


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FWallPanel OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FWallPanel OnCloseRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePoint = nullptr;
	UPROPERTY(EditAnywhere)
		AActor *ActorThatOpens = nullptr;
	
	AActor* Owner = nullptr;
	
	UFUNCTION(BlueprintCallable)
	FVector GetStartLocation();

	
	
};
