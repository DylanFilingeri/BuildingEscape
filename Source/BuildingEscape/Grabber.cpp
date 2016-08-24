// Copyright Dylan Filingeri 2016.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner()->GetName();

	FindPhysicsHandleComponent();

	SetupInputComponent();
	
	
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// PhysicsHandleComponent
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandleComponent is missing from %s"), *Owner);
	}
}

/// Look for attatched InputComponent (only appears at runtime)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		// InputComponent is found
		//UE_LOG(LogTemp, Warning, TEXT("InputComponent is found from %s"), *Owner);

		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); // & is an address of operator
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent is missing from %s"), *Owner);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!"));

	/// Line trace and try to reach any actors with physics body collision channel set
	// can use auto for each type
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent(); // gets the mesh component in our case
	AActor* ActorHit = HitResult.GetActor();

	/// If we hit something, attatch a physics handle
	if (ActorHit) // if (ActorHit != nullptr)
	{ 
		PhysicsHandle->GrabComponent(
		ComponentToGrab,
		NAME_None, // no bones needed
		ComponentToGrab->GetOwner()->GetActorLocation(),
		true // allow rotation
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released!"));

	// Release physics handle
	PhysicsHandle->ReleaseComponent();
}

/// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// if the physics handle is attatched 
	if (PhysicsHandle->GrabbedComponent)
	{
		FVector LineTraceEnd = GetReachLineEnd();

		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// CODE BEFORE REFACTOR TO GETREACHLINEEND/START
	/* 
	/// Get playerviewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// Log out PlayerViewPointLocation/Rotation to test (Disabled)
	
	UE_LOG(LogTemp, Warning, TEXT("Location: %s , Rotation: %s"),
	*PlayerViewPointLocation.ToString(),
	*PlayerViewPointRotation.ToString()
	);

	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * Reach);
	*/

	/// Draw Debug Line (Disabled)
	/*
	DrawDebugLine(
	GetWorld(),
	PlayerViewPointLocation,
	LineTraceEnd,
	FColor(255, 0, 0),
	false,
	0.f,
	0.f,
	10.f
	);
	*/

	FVector PlayerViewPointLocation = GetReachLineStart();
	FVector LineTraceEnd = GetReachLineEnd();

	/// Setup Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); // true/false whether complex collision, getowner to ignore collision

	/// Line Trace (AKA Ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// SEE WHAT WE HIT MOVED TO GRAB FUNCTION
	/* /// See what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *(ActorHit->GetName())); // Pointer -> GetName // GetName returns an FString - have to put * to dereference it 
	}
	*/

	return Hit;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

