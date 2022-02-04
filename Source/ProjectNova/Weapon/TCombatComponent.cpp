#include "TCombatComponent.h"


FName UTCombatComponent::WeaponSocketName = TEXT("Weapon_Socket");

UTCombatComponent::UTCombatComponent()
	: MaxWeaponCount(4)
{

}

void UTCombatComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsTryingToAttack && !IsActionLocked())
	{
		GetHeldWeapon()->Attack();

		if (!GetHeldWeapon()->bAttackContinuously)
		{
			bIsTryingToAttack = false;
		}
	}
}

void UTCombatComponent::SetUpConstruction(USkeletalMeshComponent* SocketMesh, USceneComponent* TraceComponent)
{
	AttachmentMesh = SocketMesh;
	TraceOrigin = TraceComponent;
}

void UTCombatComponent::PickUpWeapon(ATWeapon* NewWeapon)
{
	//Perform any necessary set up for the weapon
	Arsenal.Emplace(NewWeapon);
	NewWeapon->SetCombatComponent(this);
	NewWeapon->AttachToComponent(AttachmentMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);

	//We are holding too many weapons, drop the currently held one
	if (Arsenal.Num() > MaxWeaponCount)
	{
		Arsenal[CurrentWeaponIndex]->SetCombatComponent(nullptr);
		Arsenal.SwapMemory(CurrentWeaponIndex, Arsenal.Num() - 1);
		Arsenal.RemoveAt(Arsenal.Num() - 1);
	}

	//We picked up a new weapon but havent gone over our weapon limit, just swap to it
	else if (Arsenal.Num() > 1)
	{
		bIsTryingToAttack = false;
		Arsenal[CurrentWeaponIndex]->GetMesh()->SetVisibility(false);

		CurrentWeaponIndex = Arsenal.Num() - 1;

		Arsenal[CurrentWeaponIndex]->GetMesh()->SetVisibility(true);		
	}

	UpdateHUD();
}

void UTCombatComponent::SwapWeapon(const int32 Direction)
{
	const int32 WeaponCount = Arsenal.Num();

	if (WeaponCount < 2 || IsNonSwapLocked())
	{
		return;
	}

	bIsTryingToAttack = false;
	Arsenal[CurrentWeaponIndex]->GetMesh()->SetVisibility(false);

	//If we swap past the last or before the first index, loop to the other end
	const int32 LastIndex = WeaponCount - 1;
	int32 NewIndex = CurrentWeaponIndex + Direction;
	NewIndex = NewIndex > LastIndex ? 0 : NewIndex;
	NewIndex = NewIndex < 0 ? LastIndex : NewIndex;

	CurrentWeaponIndex = NewIndex;

	Arsenal[CurrentWeaponIndex]->GetMesh()->SetVisibility(true);

	UpdateHUD();
}

ATWeapon* UTCombatComponent::GetHeldWeapon() const
{
	return Arsenal.Num() < 1 ? nullptr : Arsenal[CurrentWeaponIndex];
}

void UTCombatComponent::ReceiveReload()
{
	if (GetHeldWeapon()->IsReloadable() && !IsReloadLocked())
	{
		//Don't want to keep attacking when a reload is requested
		bIsTryingToAttack = false;

		bIsReloading = true;

		OnReload.ExecuteIfBound();
	}
}

void UTCombatComponent::ReceiveStartAttack()
{
	bIsTryingToAttack = true;
}

void UTCombatComponent::ReceiveStopAttack()
{
	bIsTryingToAttack = false;
}

void UTCombatComponent::ReceiveAimStart()
{
	if (GetHeldWeapon()->IsAimable() && IsActionLocked())
	{
		bIsAimed = true;
		bIsInAnimation = true;

		OnAimStart.ExecuteIfBound();
	}
}

void UTCombatComponent::ReceiveAimStop()
{
	if (GetHeldWeapon()->IsAimable())
	{
		bIsAimed = false;
		bIsInAnimation = true;

		OnAimStop.ExecuteIfBound();
	}
}

void UTCombatComponent::ReceiveReloadComplete(const bool bInterrupted)
{
	if (!bInterrupted)
	{
		Arsenal[CurrentWeaponIndex]->Reload();
	}

	bIsReloading = false;
}

void UTCombatComponent::ReceiveAnimationComplete()
{
	bIsInAnimation = false;
}

void UTCombatComponent::ReceiveSwapComplete()
{
	bIsSwapping = false;
}

void UTCombatComponent::UpdateHUD()
{
	OnUpdateHUD.ExecuteIfBound(GetHeldWeapon()->GetImmutableHUD());
}