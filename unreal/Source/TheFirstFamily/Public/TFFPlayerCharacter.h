#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TFFPlayerCharacter.generated.h"

UCLASS()
class THEFIRSTFAMILY_API ATFFPlayerCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ATFFPlayerCharacter();
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    UFUNCTION(BlueprintCallable, Category="TFF|Movement") void SetMovementEnabled(bool bEnabled);
private:
    UPROPERTY(VisibleAnywhere) class UTFFInteractionComponent* Interaction;
    void Interact();
    void MoveForward(float Value);
    void MoveRight(float Value);
    void StartSprint();
    void StopSprint();
    void BeginJump();
    void EndJump();
    float WalkSpeed = 420.f;
    float SprintSpeed = 700.f;
};