#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFFMenuWidget.generated.h"
class UButton;
class UTextBlock;
UCLASS()
class THEFIRSTFAMILY_API UTFFMenuWidget : public UUserWidget
{
 GENERATED_BODY()
public:
 virtual void NativeConstruct() override;
 UFUNCTION(BlueprintCallable, Category="TFF|Menu") void ShowMainMenu();
 UFUNCTION(BlueprintCallable, Category="TFF|Menu") void ShowCharacterSelection();
 UFUNCTION(BlueprintCallable, Category="TFF|Menu") void ShowCustomization();
 UFUNCTION(BlueprintCallable, Category="TFF|Menu") void EnterWorld();
private:
 UPROPERTY() class UVerticalBox* MenuColumn;
 void ClearAndTitle(const FString& Title);
 UButton* AddButton(const FString& Label);
 UFUNCTION() void SelectJay();
 UFUNCTION() void SelectEsined();
 UFUNCTION() void SelectJahde();
 UFUNCTION() void SetOutfitDefault();
 UFUNCTION() void SetOutfitCasual();
 UFUNCTION() void SetOutfitSport();
 UFUNCTION() void ConfirmAppearance();
};