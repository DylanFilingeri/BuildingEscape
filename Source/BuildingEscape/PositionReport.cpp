// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties // constructor
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true; // sets up beginplay
	PrimaryComponentTick.bCanEverTick = true; // sets it up to tick every frame

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay() // method BeginPlay in class UPositionReport
{
	Super::BeginPlay(); // Super - do whatever happens up the inheritance tree - the actor component
	FString ObjectName = GetOwner()->GetName(); // GetOwner returns pointer to an actor -> look through pointer to get to GetName method which returns an FString
	//FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos); // %s is a format operator
	
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

