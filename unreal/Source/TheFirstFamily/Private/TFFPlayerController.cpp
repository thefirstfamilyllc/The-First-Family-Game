#include "TFFPlayerController.h"
#include "TFFMenuWidget.h"
#include "TFFPlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
void ATFFPlayerController::BeginPlay()
{
 Super::BeginPlay();
 if (!IsLocalController()) return;
 // Prevent movement while the menu is visible.
 if (ACharacter* Character = Cast<ACharacter>(GetPawn()))
 {
  Character->GetCharacterMovement()->DisableMovement();
 }
 MainMenu = CreateWidget<UTFFMenuWidget>(this, UTFFMenuWidget::StaticClass());
 if (MainMenu)
 {
  MainMenu->AddToViewport();
  bShowMouseCursor = true;
  SetInputMode(FInputModeUIOnly());
 }
}
