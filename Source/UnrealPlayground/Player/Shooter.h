#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShooterMovementComponent.h"
#include "WeaponInput.h"
#include "Shooter.generated.h"

class UCapsuleComponent;
class UCameraComponent;
class UShooterStateMachine;
class UPawnMovementComponent;
class UCombatComponent;
class UHealthComponent;
class IInteractiveObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScanEvent, FHitResult, ScanData);

struct FShooterInput : public FWeaponInput
{
public:
	FShooterInput() { }
	/** 
	* Runs within the shooter's Tick to handle any input states that need to be watched 
	* @param	DeltaTime				Time slice
	*/
	void Tick(const float DeltaTime);

	/** Watches the crouch input values so any substates can avoid re-implementing the same checks for crouching/prone*/
	void HandleCrouchInputStates(const float DeltaTime);

	/** Shooter this input state applies to*/
	AShooter* Owner;

	/** How long crouch has been held for since the last release*/
	float CurrentCrouchHoldTime;

	/** X-axis movement input*/
	float MoveX;

	/** Y-axis movement input*/
	float MoveY;

	/** X-axis look input*/
	float LookX;

	/** Y-axis look input*/
	float LookY;

	/** Whether or not the player is pressing the jump button*/
	uint8 bIsTryingToJump : 1;

	/** Whether or not the player is pressing the crouch button*/
	uint8 bIsHoldingCrouch : 1;

	/** The previous ticks's state of the crouch input*/
	uint8 bWasHoldingCrouch: 1;

	/** Whether or not crouch input has been released after its been pressed*/
	uint8 bIsTryingToCrouch : 1;

	/** Whether or not crouch input has been held long enough go prone*/
	uint8 bIsTryingToProne : 1;

	/** Whether or not the player is pressing the sprint button*/
	uint8 bIsTryingToSprint : 1;
};

UCLASS()
class UNREALPLAYGROUND_API AShooter : public APawn
{
	GENERATED_BODY()

public:
	AShooter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	friend struct FShooterInput;

	USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	/** Returns the capsule component attached to this shooter*/
	UCapsuleComponent* GetCollider() const { return Collider; }

	/** Returns the camera anchor component attached to this shooter*/
	USceneComponent* GetAnchor() const { return CameraAnchor; }
	
	/** Returns the combat component attached to this shooter*/
	UCombatComponent* GetCombat() const { return Combat; }

	/** Returns the camera component attached to this shooter*/
	UCameraComponent* GetCamera() const { return Camera; }

	/** Returns the input state. Note: contents are mutable*/
	FShooterInput* GetInput() { return &InputState; }

	/** Draws debug traces for a variety of position tests if enabled*/
	UPROPERTY(Category = Pawn, EditAnywhere)
	uint8 bTraceDebug : 1;

	/**Invoked when the shooter is looking at an object that can be interacted with (a weapon/button)*/
	UPROPERTY(BlueprintAssignable)
	FScanEvent OnScanHit;

	/** Animation Hooks**/

	/** Returns whether this shooter is walking*/
	UFUNCTION(BlueprintCallable, Category = "Animation")
	bool IsWalking();

	/** Returns whether this shooter is falling*/
	UFUNCTION(BlueprintCallable, Category = "Animation")
	bool IsFalling();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Arms;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(Category = Shooter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UShooterMovementComponent* ShooterMovement;

	UPROPERTY(Category = Shooter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Collider;

	UPROPERTY(Category = Shooter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* CameraAnchor;

	UPROPERTY(Category = Shooter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(Category = Shooter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* Combat;

	UPROPERTY(Category = Shooter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* Health;

	UPROPERTY()
	UShooterStateMachine* StateMachine;
	
	/**Contains all relevant information of the input state*/
	FShooterInput InputState;

	/**Data regarding whether or not we are looking at a weapon or interactive object*/
	FHitResult ScanHit;

	/** Casts a trace from the camera to see if there is an object nearby we can interact with*/	
	void ScanInteractiveObject();

	///		 Begin Input Bindings	   ///
	void MoveInputX(const float Value)	{ InputState.MoveX = Value; }
	void MoveInputY(const float Value)	{ InputState.MoveY = Value; }
	void LookInputX(const float Value)	{ InputState.LookX = Value; }
	void LookInputY(const float Value)	{ InputState.LookY = Value; }
	void JumpPress()					{ InputState.bIsTryingToJump = true; }
	void JumpRelease()					{ InputState.bIsTryingToJump = false; }
	void CrouchPress()					{ InputState.bIsHoldingCrouch = true; }
	void CrouchRelease()				{ InputState.bIsHoldingCrouch = false; }
	void ShootPress()					{ InputState.bIsTryingToFire = true; }
	void ShootRelease()					{ InputState.bIsTryingToFire = false; }
	void AimPress()						{ InputState.bIsTryingToAim = true; }
	void AimRelease()					{ InputState.bIsTryingToAim = false; }
	void InteractPress()				{ InputState.bIsTryingToInteract = true; }
	void InteractRelease()				{ InputState.bIsTryingToInteract = false; }
	void SwapPress()					{ InputState.bIsTryingToSwap = true; }
	void SwapRelease()					{ InputState.bIsTryingToSwap = false; }
	void MeleePress()					{ InputState.bIsTryingToMelee = true; }
	void MeleeRelease()					{ InputState.bIsTryingToMelee = false; }
	void SprintPress()					{ InputState.bIsTryingToSprint = true; }
	void SprintRelease()				{ InputState.bIsTryingToSprint = false; }
	void ReloadPress()					{ InputState.bIsTryingToReload = true; }
	void ReloadRelease()				{ InputState.bIsTryingToReload = false; }
	void ThrowPrimaryPress()			{ InputState.bIsTryingToThrowPrimary = true; }
	void ThrowPrimaryRelease()			{ InputState.bIsTryingToThrowPrimary = false; }
	void ThrowSecondaryPress()			{ InputState.bIsTryingToThrowSecondary = true; }
	void ThrowSecondaryRelease()		{ InputState.bIsTryingToThrowSecondary = false; }
};
