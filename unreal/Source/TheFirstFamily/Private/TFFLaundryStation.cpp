#include "TFFLaundryStation.h"
#include "TFFGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

ATFFLaundryStation::ATFFLaundryStation()
{
    PrimaryActorTick.bCanEverTick = false;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StationMesh"));
    SetRootComponent(Mesh);
}
void ATFFLaundryStation::Interact_Implementation(AActor* Interactor)
{
    AdvanceOrder();
}
FText ATFFLaundryStation::InteractionLabel_Implementation() const
{
    switch(Stage)
    {
    case ETFFLaundryStage::WaitingForPickup: return FText::FromString(TEXT("Collect laundry"));
    case ETFFLaundryStage::Collected: return FText::FromString(TEXT("Start wash"));
    case ETFFLaundryStage::Washing: return FText::FromString(TEXT("Move to dryer"));
    case ETFFLaundryStage::Drying: return FText::FromString(bNoFolding ? TEXT("Pack clean laundry") : TEXT("Fold laundry"));
    case ETFFLaundryStage::Folding: return FText::FromString(TEXT("Pack order"));
    case ETFFLaundryStage::ReadyToDeliver: return FText::FromString(TEXT("Deliver order"));
    default: return FText::FromString(TEXT("Order complete"));
    }
}
void ATFFLaundryStation::AdvanceOrder()
{
    if (Stage == ETFFLaundryStage::Delivered) return;
    if (Stage == ETFFLaundryStage::Drying && bNoFolding) Stage = ETFFLaundryStage::ReadyToDeliver;
    else Stage = static_cast<ETFFLaundryStage>(static_cast<uint8>(Stage) + 1);
    if (Stage == ETFFLaundryStage::Delivered)
    {
        if (UTFFGameInstance* Game = Cast<UTFFGameInstance>(GetGameInstance()))
        {
            const float Rate = bNoFolding ? 1.f : PricePerLb;
            Game->ChangeCash(FMath::RoundToInt(OrderWeightLbs * Rate));
            Game->SaveProgress();
        }
    }
}