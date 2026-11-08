#include "TFFInteractionComponent.h"
#include "TFFInteractable.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

UTFFInteractionComponent::UTFFInteractionComponent() { PrimaryComponentTick.bCanEverTick = false; }
bool UTFFInteractionComponent::TryInteract()
{
    APawn* Pawn = Cast<APawn>(GetOwner());
    if (!Pawn || !Pawn->GetController() || !GetWorld()) return false;
    FVector Eye; FRotator Facing;
    Pawn->GetController()->GetPlayerViewPoint(Eye, Facing);
    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(TFFInteract), false, Pawn);
    if (!GetWorld()->LineTraceSingleByChannel(Hit, Eye, Eye + Facing.Vector() * Range, ECC_Visibility, Params)) return false;
    AActor* Target = Hit.GetActor();
    if (!IsValid(Target) || !Target->GetClass()->ImplementsInterface(UTFFInteractable::StaticClass())) return false;
    ITFFInteractable::Execute_Interact(Target, Pawn);
    return true;
}