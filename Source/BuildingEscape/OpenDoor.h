// Copyright Dylan Filingeri 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	//void OpenDoor();
	//void CloseDoor();

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenRequest; // event handler of type FOnOpenRequest

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseRequest;

/// no other class can set these values because it's private
private:
	
	//UPROPERTY(VisibleAnywhere) // macro makes visible in the editor details panel
	//UPROPERTY(EditAnywhere)
	//float OpenAngle = -90.0f;

	UPROPERTY(EditAnywhere) // macro makes editable in the editor details panel
	ATriggerVolume* PressurePlate = nullptr; // pointer type of trigger volume // we call the pointer PressurePlate

	UPROPERTY(EditAnywhere)
	AStaticMeshActor* StaticMesh = nullptr;

	//UPROPERTY(EditAnywhere)
	//float DoorCloseDelay = 0.f;

	UPROPERTY(EditAnywhere)
	float MassRequiredToOpenDoor = 50.f;

	//float DoorLastOpenTime;

	//AActor* ActorThatOpens; // Pawn inherits from Actor (DISABLED)
	AActor* Owner = nullptr; // The owning door

	float GetTotalMassOfActorsOnPlate();
	
};
