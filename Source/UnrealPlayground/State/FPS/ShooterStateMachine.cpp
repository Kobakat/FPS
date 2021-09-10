#include "ShooterStateMachine.h"
#include "Movement/SWalkState.h"
#include "Movement/SRunState.h"
#include "Movement/SCrouchState.h"
#include "Movement/SProneState.h"
#include "Movement/SDiveState.h"

void UShooterStateMachine::Initialize(UObject* Context)
{
	Super::Initialize(Context);

	this->AddState<USWalkState>(Context, "Walking");
	this->AddState<USRunState>(Context, "Running");
	this->AddState<USCrouchState>(Context, "Crouching");
	this->AddState<USProneState>(Context, "Proning");
	this->AddState<USDiveState>(Context, "Diving");

	this->SetInitialState("Walking");
	this->GetActiveState()->OnEnter();
}

void UShooterStateMachine::SetState(const FString NewStateKey)
{
	PreviousState = GetActiveState();
	Super::SetState(NewStateKey);
}