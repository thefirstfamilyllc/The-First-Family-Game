#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFFInteractable.h"
#include "TFFLaundryStation.generated.h"

UENUM(BlueprintType)
enum class ETFFLaundryStage : uint8 { WaitingForPickup, Collected, Washing, Drying, Folding, ReadyToDeliver, Delivered };

UCLASS(BlueprintType)
class THEFIRSTFAMILY_API ATFFLaundryStation : public AActor, public ITFFInteractable
{
    GENERATED_BODY()
public:
    ATFFLaundryStation();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TFF|Laundry") ETFFLaundryStage Stage = ETFFLaundryStage::WaitingForPickup;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TFF|Laundry") float OrderWeightLbs = 20.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TFF|Laundry") float PricePerLb = 2.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TFF|Laundry") int32 ExperiencePerOrder = 10;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TFF|Laundry") bool bNoFolding = false;
    UFUNCTION(BlueprintCallable, Category="TFF|Laundry") void AdvanceOrder();
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual FText InteractionLabel_Implementation() const override;
};