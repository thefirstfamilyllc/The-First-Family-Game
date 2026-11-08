#include "TFFGameInstance.h"
#include "TFFSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UTFFGameInstance::ChooseCharacter(ETFFCharacter Character)
{
    SelectedCharacter = Character;
    bCharacterAccepted = false;
    Appearance = FTFFAppearance();
}
void UTFFGameInstance::AcceptCharacter() { bCharacterAccepted = true; }
void UTFFGameInstance::UpdateAppearance(FTFFAppearance NewAppearance) { Appearance = NewAppearance; }
int32 UTFFGameInstance::UnlockLevel(ETFFFeature Feature) const
{
    switch (Feature)
    {
    case ETFFFeature::StreetTeam: return 3;
    case ETFFFeature::Cleaning: return 5;
    case ETFFFeature::Franchise: return 10;
    default: return 1;
    }
}
bool UTFFGameInstance::IsFeatureUnlocked(ETFFFeature Feature) const { return Level >= UnlockLevel(Feature); }
FText UTFFGameInstance::GetActiveBrandName() const
{
    return FText::FromString(bCleaningBrandUpgraded && CanUpgradeBrandForCleaning()
        ? TEXT("The First Family Laundry & Cleaning")
        : TEXT("The First Family Pick-Up & Delivery Laundry Service"));
}
bool UTFFGameInstance::CanUpgradeBrandForCleaning() const { return Level >= 5; }
bool UTFFGameInstance::UpgradeBrandForCleaning()
{
    if (!CanUpgradeBrandForCleaning()) return false;
    bCleaningBrandUpgraded = true;
    return SaveProgress();
}
void UTFFGameInstance::SetLevel(int32 NewLevel) { Level = FMath::Max(1, NewLevel); }
void UTFFGameInstance::ChangeCash(int32 Delta) { Cash = FMath::Max(0, Cash + Delta); }
bool UTFFGameInstance::SaveProgress()
{
    UTFFSaveGame* Save = Cast<UTFFSaveGame>(UGameplayStatics::CreateSaveGameObject(UTFFSaveGame::StaticClass()));
    if (!Save) return false;
    Save->Level = Level; Save->Cash = Cash; Save->Character = SelectedCharacter;
    Save->bAccepted = bCharacterAccepted; Save->Appearance = Appearance;
    return UGameplayStatics::SaveGameToSlot(Save, TEXT("TFF_Main"), 0);
}
bool UTFFGameInstance::LoadProgress()
{
    UTFFSaveGame* Save = Cast<UTFFSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TFF_Main"), 0));
    if (!Save) return false;
    Level = Save->Level; Cash = Save->Cash; SelectedCharacter = Save->Character;
    bCharacterAccepted = Save->bAccepted; Appearance = Save->Appearance;
    return true;
}