#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TFFPlayerController.generated.h"
UCLASS()
class THEFIRSTFAMILY_API ATFFPlayerController : public APlayerController
{
 GENERATED_BODY()
public:
 virtual void BeginPlay() override;
 UPROPERTY() class UTFFMenuWidget* MainMenu;
};