#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TFFGameInstance.h"
#include "TFFSaveGame.generated.h"

UCLASS()
class THEFIRSTFAMILY_API UTFFSaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY() int32 Level = 1;
    UPROPERTY() int32 Cash = 5000;
    UPROPERTY() ETFFCharacter Character = ETFFCharacter::Jay;
    UPROPERTY() bool bAccepted = false;
    UPROPERTY() FTFFAppearance Appearance;
    UPROPERTY() bool bCleaningBrandUpgraded = false;
};