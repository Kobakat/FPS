#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Removable.h"
#include "Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerEvent);

class UBoxComponent;

UCLASS()
class UNREALPLAYGROUND_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrigger();

	virtual void SetActive(const bool Value);

	UPROPERTY(BlueprintAssignable)
	FTriggerEvent OnTriggerActivated;

	UPROPERTY(BlueprintAssignable)
	FTriggerEvent OnTriggerExited;

protected:

	/** True if this trigger can be activated when entered*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	uint8 bIsActive : 1;

	/** If true, this trigger will start as active*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	uint8 bStartActive : 1;

	/** If true, this trigger will activate everytime it is entered*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	uint8 bTriggerMoreThanOnce : 1;

	/** This trigger will only activate if the overlapping pawn is a of type that exists in this white list*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<TSubclassOf<APawn>> TriggerWhiteList;

	/** Collision volume that acts as the trigger region*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
	UBoxComponent* TriggerVolume;

	/** Called when the trigger is activated*/
	virtual void ExecuteTrigger(APawn* Sender);

	virtual void BeginPlay() override;
	virtual void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	virtual void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
