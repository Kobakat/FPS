// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.h"
#include "HealthPickup.generated.h"

class UHealthComponent;

UCLASS()
class UNREALPLAYGROUND_API AHealthPickup : public AActor, public IInteractiveObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickup();

	virtual void InteractionEvent(APawn* EventSender) override;

protected:

	UPROPERTY(EditAnywhere)
	int32 HealAmount;

	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

};
