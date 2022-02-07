// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Removable.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.h"
#include "HealthPickup.generated.h"

class UHealthComponent;

UCLASS()
class PROJECTNOVA_API AHealthPickup : public AActor, public IInteractiveObject, public IRemovable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickup();

	virtual void InteractionEvent(APawn* EventSender) override;

	FInteractionPrompt& GetInteractionPrompt() override { return Prompt; }

	FName& GetInteractionMappingName() override { return ActionMappingName; }

	virtual bool CanInteract() const { return true; }

	void RecieveLookedAt(APawn* EventSender) override;

	void RecieveLookedAway(APawn* EventSender, int32 MappingIndexToRemove) override;

protected:

	UPROPERTY(EditAnywhere)
	int32 HealAmount;

	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FInteractionPrompt Prompt;

	/** Is set to interact by default. See Edit->ProjectSettings->Input for list of action mapping names.*/
	UPROPERTY(EditAnywhere, Category = "Interaction")
	FName ActionMappingName;
};
