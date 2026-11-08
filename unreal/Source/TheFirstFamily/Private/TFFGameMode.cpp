#include "TFFGameMode.h"
#include "TFFPlayerCharacter.h"
ATFFGameMode::ATFFGameMode()
{
    DefaultPawnClass = ATFFPlayerCharacter::StaticClass();
}