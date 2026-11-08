#include "TFFGameMode.h"
#include "TFFPlayerCharacter.h"
#include "TFFPlayerController.h"
ATFFGameMode::ATFFGameMode()
{
    DefaultPawnClass = ATFFPlayerCharacter::StaticClass();
    PlayerControllerClass = ATFFPlayerController::StaticClass();
}