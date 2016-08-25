// Copyright Dylan Filingeri 2016.

#include "BuildingEscape.h"
#include "ActivatePressurePlate.h"


// Sets default values for this component's properties
UActivatePressurePlate::UActivatePressurePlate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UActivatePressurePlate::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Is Missing a Pressure Plate!"), *GetOwner()->GetName());
	}
	if (!StaticMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Is Missing a Static Mesh To Trigger Door!"), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UActivatePressurePlate::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!TriggerVolume || !StaticMesh) { return; }

	if (TriggerVolume->IsOverlappingActor(StaticMesh))
	{
		//UE_LOG(LogTemp, Warning, TEXT("DOWN"));
		OnDownEvent.Broadcast();
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("UP"));
		OnUpEvent.Broadcast();
	}
}

