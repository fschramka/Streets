// Fill out your copyright notice in the Description page of Project Settings.

#include "Streets.h"
#include "DayNightActor.h"
#include "LightBehavior.h"


// Sets default values for this component's properties
ULightBehavior::ULightBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void ULightBehavior::BeginPlay()
{
	Super::BeginPlay();

	// Find the DayNightActor for subscription
	TActorIterator<ADayNightActor> ActorItr(GetWorld());
	
	Cast<ADayNightActor>(*ActorItr)->subscribeForStreetLightingEvent(this);

	light = GetOwner()->FindComponentByClass<ULightComponent>();
}


// Called every frame
void ULightBehavior::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	UE_LOG(LogTemp, Log, TEXT("NOPE"));
}

void ULightBehavior::notify(bool on) {
	if (on)
		light->SetIntensity(8000.0f);
	else
		light->SetIntensity(0.0f);
}


