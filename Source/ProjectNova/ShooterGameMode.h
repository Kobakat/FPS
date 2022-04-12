#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

class UDelayedActionManager;
class AQuickTimeManager;
class AShooter;
class AShooterController;
class AShooterCutscene;



UCLASS()
class PROJECTNOVA_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AShooterGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void Tick(float DeltaTime) override;

	void PostLogin(APlayerController* NewPlayer) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Game Mode")
	AShooter* Shooter;

	UPROPERTY(BlueprintReadOnly, Category = "Game Mode")
	AShooterController* ShooterController;

	UPROPERTY(Transient, BlueprintReadOnly)
	AQuickTimeManager* QuickTimeManager;

	UPROPERTY(Transient, BlueprintReadOnly)
	AShooterCutscene* ShooterCutscene;

private:

	UPROPERTY(Transient)
	UDelayedActionManager* DelayedActionManager;

	UClass* QuickTimeManagerClass;

	UClass* ShooterCutsceneClass;

public:

	FORCEINLINE AShooter* GetShooter() const { return Shooter; }
	FORCEINLINE AShooterController* GetShooterController() const { return ShooterController; }
	FORCEINLINE UDelayedActionManager* GetDelayedActionManager() const { return DelayedActionManager; }
	FORCEINLINE AShooterCutscene* GetShooterCutscene() const { return ShooterCutscene; }
};