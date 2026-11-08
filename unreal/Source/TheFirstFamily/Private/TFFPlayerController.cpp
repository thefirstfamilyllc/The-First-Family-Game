#include "TFFPlayerController.h"
#include "TFFMenuWidget.h"
#include "Blueprint/UserWidget.h"
void ATFFPlayerController::BeginPlay()
{
 Super::BeginPlay();
 if (IsLocalController())
 {
  MainMenu = CreateWidget<UTFFMenuWidget>(this, UTFFMenuWidget::StaticClass());
  if (MainMenu)
  {
   MainMenu->AddToViewport();
   bShowMouseCursor = true;
   SetInputMode(FInputModeUIOnly());
  }
 }
}