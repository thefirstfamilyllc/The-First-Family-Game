#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TFFGameInstance.generated.h"

UENUM(BlueprintType)
enum class ETFFCharacter : uint8 { Jay, Esined, Jahde };

UENUM(BlueprintType)
enum class ETFFFeature : uint8 { Laundry, BusinessManagement, PickupDelivery, StreetTeam, Cleaning, Franchise };

USTRUCT(BlueprintType)
struct FTFFAppearance
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Outfit = TEXT("Default");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Hair = TEXT("Approved");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Shoes = TEXT("Default");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Accessory = NAME_None;
};

UCLASS(BlueprintType)
class THEFIRSTFAMILY_API UTFFGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadOnly, Category="TFF|Progress") int32 Level = 1;
    UPROPERTY(BlueprintReadOnly, Category="TFF|Progress") int32 Cash = 5000;
    UPROPERTY(BlueprintReadOnly, Category="TFF|Characters") ETFFCharacter SelectedCharacter = ETFFCharacter::Jay;
    UPROPERTY(BlueprintReadOnly, Category="TFF|Characters") bool bCharacterAccepted = false;
    UPROPERTY(BlueprintReadOnly, Category="TFF|Characters") FTFFAppearance Appearance;

    UFUNCTION(BlueprintCallable, Category="TFF|Characters") void ChooseCharacter(ETFFCharacter Character);
    UFUNCTION(BlueprintCallable, Category="TFF|Characters") void AcceptCharacter();
    UFUNCTION(BlueprintCallable, Category="TFF|Characters") void UpdateAppearance(FTFFAppearance NewAppearance);
    UFUNCTION(BlueprintPure, Category="TFF|Progress") bool IsFeatureUnlocked(ETFFFeature Feature) const;
    UFUNCTION(BlueprintPure, Category="TFF|Progress") int32 UnlockLevel(ETFFFeature Feature) const;
    UFUNCTION(BlueprintCallable, Category="TFF|Progress") void SetLevel(int32 NewLevel);
    UFUNCTION(BlueprintCallable, Category="TFF|Progress") void ChangeCash(int32 Delta);
    UFUNCTION(BlueprintCallable, Category="TFF|Save") bool SaveProgress();
    UFUNCTION(BlueprintCallable, Category="TFF|Save") bool LoadProgress();
};