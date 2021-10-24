#pragma once

#include "CoreMinimal.h"
#include "Gameplay/VaultObject.h"
#include "GameFramework/HUD.h"
<<<<<<< Updated upstream
#include "../UnrealPlayground/Weapon/Weapon.h"
=======
#include "Components/SlateWrapperTypes.h"
>>>>>>> Stashed changes
#include "ShooterHUD.generated.h"

class AShooter;
<<<<<<< Updated upstream
class UShooterCombatComponent;
=======
class UCombatComponent;
class AWeapon;
class UUserWidget;
class AShooterGameMode;
>>>>>>> Stashed changes

UCLASS()
class UNREALPLAYGROUND_API AShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShooterHUD();
	virtual void Tick(float DeltaTime) override;
	void Initialize();

protected:
<<<<<<< Updated upstream
=======

	/** Invoked when a UI update is requested*/
	UPROPERTY(BlueprintAssignable)
		FUpdateHUD OnUpdate;

	/** Invoked when the combat component adds a new weapon to the arsenal*/
	void ReceiveWeapon(AWeapon* NewWeapon);

	/** Invoked when the combat component removes a weapon from the arsenal*/
	void ReleaseWeapon(AWeapon* DiscardedWeapon);

	/** Called when OnUpdate is invoked. Updates member fields below so they can be read from blueprint*/
	void InternalUpdate();

	UFUNCTION()
		void ShowPauseMenu();

	void HidePauseMenu();

	uint8 bIsPaused : 1;

	/** Called when shooter looks at something interactable*/
	UFUNCTION()
		void ShowInteractionPrompt(FHitResult Hit);

	/** Called when shooter is not looking at something interactable*/
	UFUNCTION()
		void HideInteractionPrompt(FHitResult Hit);

	UPROPERTY(BlueprintReadWrite)
		UUserWidget* InteractionPromptWidget;

	UPROPERTY(BlueprintReadWrite)
		UUserWidget* VaultPromptWidget;

	UPROPERTY(BlueprintReadWrite)
		UUserWidget* PauseMenuWidget;

>>>>>>> Stashed changes
	/** Max ammo that can be stored in this weapon after reloading*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		int MaxAmmoInWeapon;

	/** Current amount of ammo ready to be fired*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		int AmmoInWeapon;

	/** The amount of extra ammo the player has*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		int ExcessAmmo;

	/** The amount of bloom currently attached to the combat component*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float Bloom;

	UPROPERTY(BlueprintReadOnly)
		uint8 bPlayerHasWeapon : 1;

	UPROPERTY(BlueprintReadOnly)
		AShooter* Shooter;

private:

	/** Combat component attached to player*/
	UShooterCombatComponent* Combat;
};
