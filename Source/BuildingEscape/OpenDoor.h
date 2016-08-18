// Copyright Dylan Filingeri 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

// no other class can set these values because it's private
private:
	//UPROPERTY(VisibleAnywhere) // macro makes visible in the editor details panel
	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.0f;

	UPROPERTY(EditAnywhere) // macro makes editable in the editor details panel
	ATriggerVolume* PressurePlate; // pointer type of trigger volume // we call the pointer PressurePlate

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float DoorLastOpenTime;

	AActor* ActorThatOpens; // Pawn inherits from Actor
	AActor* Owner; // The owning door
	
};
