
// Fill out your copyright notice in the Description page of Project Settings.


#include "ERActorComponent.h"

// Sets default values for this component's properties
UERActorComponent::UERActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UERActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UERActorComponent::GetERProgress_Implementation() const
{
	return 0.0f;
}

// Called every frame
void UERActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

