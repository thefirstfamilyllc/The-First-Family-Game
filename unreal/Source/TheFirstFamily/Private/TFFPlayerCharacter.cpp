#include "TFFPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"

ATFFPlayerCharacter::ATFFPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
}
void ATFFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis("MoveForward", this, &ATFFPlayerCharacter::MoveForward);
    Input->BindAxis("MoveRight", this, &ATFFPlayerCharacter::MoveRight);
    Input->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    Input->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    Input->BindAction("Jump", IE_Pressed, this, &ATFFPlayerCharacter::BeginJump);
    Input->BindAction("Jump", IE_Released, this, &ATFFPlayerCharacter::EndJump);
    Input->BindAction("Sprint", IE_Pressed, this, &ATFFPlayerCharacter::StartSprint);
    Input->BindAction("Sprint", IE_Released, this, &ATFFPlayerCharacter::StopSprint);
}
void ATFFPlayerCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.f) AddMovementInput(FRotator(0, Controller->GetControlRotation().Yaw, 0).Vector(), Value);
}
void ATFFPlayerCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.f) AddMovementInput(FRotationMatrix(FRotator(0, Controller->GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::Y), Value);
}
void ATFFPlayerCharacter::StartSprint() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
void ATFFPlayerCharacter::StopSprint() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
void ATFFPlayerCharacter::BeginJump() { Jump(); }
void ATFFPlayerCharacter::EndJump() { StopJumping(); }
void ATFFPlayerCharacter::SetMovementEnabled(bool bEnabled)
{
    if (bEnabled) GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    else GetCharacterMovement()->DisableMovement();
}