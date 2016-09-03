// Fill out your copyright notice in the Description page of Project Settings.

#include "Streets.h"
#include "DayNightActor.h"


// Sets default values
ADayNightActor::ADayNightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	lamps.clear();

}

// Called when the game starts or when spawned
void ADayNightActor::BeginPlay()
{
	Super::BeginPlay();

	sunHeight = 0.0f;
	sunSpeed = 5.0f;
	dayTime = 12;

	// Extract Sunlight from SunLightActor
	if (sunLightActor != NULL) {
		sunLight = Cast<ULightComponent>(sunLightActor->GetComponentByClass(ULightComponent::StaticClass()));
		if (sunLight == NULL) {
			UE_LOG(LogTemp, Error, TEXT("SunLight could not be extracted from Actor"));
		}
		else
			sunLightActor->SetActorRotation(FQuat(FRotator(180.0f, 0.0f, 90.0f)));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SunLightActor not set!"));
	}

	// Extract Skylight from SkylightActor
	if (skyLightActor != NULL) {
		for (auto a : skyLightActor->GetComponents()) {

			if (a->GetClass()->GetName() == USkyLightComponent::StaticClass()->GetName()) {
				skyLight = Cast<USkyLightComponent>(a);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SkyLightActor not set!"));
	}

	// Extract SunHeight from SkySphere
	if (skySphereActor != NULL) {
		for (TFieldIterator<UProperty> PropIt(skySphereActor->GetClass()); PropIt; ++PropIt)
		{
			UProperty* Property = *PropIt;

			if (Property->GetName() == "Sun height") {
				sunHeightProperty = Cast<UFloatProperty>(Property);
				break;
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("SkySphere not set!"));
}

// Called every frame
void ADayNightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// sun manipulations
	if (sunLightActor != NULL) {
		if (!fixedTime) {
			sunLightActor->AddActorLocalRotation(FRotator(0.0f, -sunSpeed, 0.0f)*DeltaTime);
		}
		else {
			sunLightActor->SetActorRotation(FQuat(FRotator(dayTime * 15.0f + 90.0f, 0.0f, 90.0f)));
		}			
		if (sunHeight < 0.0f)
			sunLight->SetIntensity(0.0f);
		else {
			sunLight->SetIntensity(sunHeight * 20 > 10.0f ? 10.0f : sunHeight * 20);
		}
		sunLightIntensity = sunLight->Intensity;
	}

	// sky light manipulation
	if (skyLight != NULL) {
		skyLightIntensity = sunHeight > -0.1f ? sunHeight / 2 + 0.1f : 0.05f;
		skyLight->SetIntensity(skyLightIntensity);
	}

	// sky sphere manipulations
	if (skySphereActor != NULL) {
		FOutputDeviceNull ar;
		skySphereActor->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);

		sunHeight = sunHeightProperty->GetPropertyValue(sunHeightProperty->ContainerPtrToValuePtr<uint8>(skySphereActor));
	}


	if (lastSunHeight > 0.1 && sunHeight <= 0.1)
		notifyLamps(true);
	else if (lastSunHeight <= 0.1 && sunHeight > 0.1)
		notifyLamps(false);

	lastSunHeight = sunHeight;
}

void ADayNightActor::subscribeForStreetLightingEvent(DayNightListener* l) {
	lamps.push_back(l);
}

void ADayNightActor::notifyLamps(bool on) {
	for (auto lamp : lamps)
		lamp->notify(on);
}

