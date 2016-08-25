// Copyright Dylan Filingeri 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "ActivatePressurePlate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressurePlateEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UActivatePressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivatePressurePlate();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	
	UPROPERTY(BlueprintAssignable)
	FPressurePlateEvent OnDownEvent;

	UPROPERTY(BlueprintAssignable)
	FPressurePlateEvent OnUpEvent;
	
private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerVolume = nullptr;

	UPROPERTY(EditAnywhere)
	AStaticMeshActor* StaticMesh = nullptr;

	
};
