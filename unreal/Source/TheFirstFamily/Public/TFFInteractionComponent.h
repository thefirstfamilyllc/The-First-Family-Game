#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TFFInteractionComponent.generated.h"

UCLASS(ClassGroup=(TFF), meta=(BlueprintSpawnableComponent))
class THEFIRSTFAMILY_API UTFFInteractionComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UTFFInteractionComponent();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TFF|Interaction") float Range = 275.f;
    UFUNCTION(BlueprintCallable, Category="TFF|Interaction") bool TryInteract();
};