// Copyright Dylan Filingeri 2016.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Find the owning Actor
	Owner = GetOwner(); // declaring a pointer to an actor called owner

	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); // DISABLED

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Is Missing a Pressure Plate!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor()
{
	// Set the door rotation (DISABLED)
	//Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));

	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	// Set the door rotation (DISABLED)
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// OLD CODE (PLayerController Pawn overlaps trigger to open door)
	/*
	// Poll the trigger volume
	// If the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}
	*/
	
	if (GetTotalMassOfActorsOnPlate() >= MassRequiredToOpenDoor) // TODO make magic number a var
	{
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}

	if ((GetWorld()->GetTimeSeconds()) >= (DoorLastOpenTime + DoorCloseDelay))
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	if (!PressurePlate) { return TotalMass; } // exit code if there is no pressure plate

	/// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	/// Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *Actor->GetName() );
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

