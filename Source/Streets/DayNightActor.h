// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DayNightListener.h"
#include <vector>
#include "DayNightActor.generated.h"

UCLASS()
class STREETS_API ADayNightActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Day & Night Actors", meta = (AllowPrivateAccess = "true"))
	class ADirectionalLight* sunLightActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Day & Night Actors", meta = (AllowPrivateAccess = "true"))
	class ASkyLight* skyLightActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Day & Night Actors", meta = (AllowPrivateAccess = "true"))
	class AActor* skySphereActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data Overview", meta = (AllowPrivateAccess = "true"))
	float sunHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data Overview", meta = (AllowPrivateAccess = "true"))
	float sunLightIntensity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data Overview", meta = (AllowPrivateAccess = "true"))
	float skyLightIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time Handles", meta = (AllowPrivateAccess = "true"))
	bool fixedTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time Handles", meta = (AllowPrivateAccess = "true", UIMin = "0", UIMax = "23"))
	int dayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Handles", meta = (AllowPrivateAccess = "true", UIMin = "0.0", UIMax = "50.0"))
	float sunSpeed;

	UFloatProperty* sunHeightProperty;
	ULightComponent* sunLight;
	USkyLightComponent* skyLight;
	std::vector<DayNightListener*> lamps;
	float lastSunHeight;

public:	
	// Sets default values for this actor's properties
	ADayNightActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void subscribeForStreetLightingEvent(DayNightListener* l);
	void notifyLamps(bool on);
};
