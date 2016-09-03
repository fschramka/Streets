// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DayNightListener.h"
#include "LightBehavior.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREETS_API ULightBehavior : public UActorComponent, public DayNightListener
{
	GENERATED_BODY()

	ULightComponent* light;

public:	
	// Sets default values for this component's properties
	ULightBehavior();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void notify(bool on) override;
	
};
