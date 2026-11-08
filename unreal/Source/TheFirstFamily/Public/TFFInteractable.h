#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TFFInteractable.generated.h"
UINTERFACE(BlueprintType)
class THEFIRSTFAMILY_API UTFFInteractable : public UInterface { GENERATED_BODY() };
class THEFIRSTFAMILY_API ITFFInteractable
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="TFF|Interaction")
    void Interact(AActor* Interactor);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="TFF|Interaction")
    FText InteractionLabel() const;
};