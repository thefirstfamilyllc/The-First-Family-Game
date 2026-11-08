#include "TFFMenuWidget.h"
#include "TFFGameInstance.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void UTFFMenuWidget::NativeConstruct()
{
 Super::NativeConstruct();
 MenuColumn = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("MenuColumn"));
 WidgetTree->RootWidget = MenuColumn;
 ShowMainMenu();
}
void UTFFMenuWidget::ClearAndTitle(const FString& Title)
{
 MenuColumn->ClearChildren();
 UTextBlock* Heading = WidgetTree->ConstructWidget<UTextBlock>();
 Heading->SetText(FText::FromString(Title));
 MenuColumn->AddChildToVerticalBox(Heading);
}
UButton* UTFFMenuWidget::AddButton(const FString& Label)
{
 UButton* Button = WidgetTree->ConstructWidget<UButton>();
 UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>();
 Text->SetText(FText::FromString(Label));
 Button->AddChild(Text);
 MenuColumn->AddChildToVerticalBox(Button);
 return Button;
}
void UTFFMenuWidget::ShowMainMenu()
{
 ClearAndTitle(TEXT("THE FIRST FAMILY - BUILD YOUR EMPIRE"));
 AddButton(TEXT("PLAY GAME"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::ShowCharacterSelection);
}
void UTFFMenuWidget::ShowCharacterSelection()
{
 ClearAndTitle(TEXT("SELECT YOUR CHARACTER"));
 AddButton(TEXT("JAY"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::SelectJay);
 AddButton(TEXT("ESINED"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::SelectEsined);
 AddButton(TEXT("JAHDE"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::SelectJahde);
 AddButton(TEXT("BACK"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::ShowMainMenu);
}
void UTFFMenuWidget::SelectJay()
{
 if (auto* Game = Cast<UTFFGameInstance>(GetGameInstance())) Game->ChooseCharacter(ETFFCharacter::Jay);
 ShowCustomization();
}
void UTFFMenuWidget::SelectEsined()
{
 if (auto* Game = Cast<UTFFGameInstance>(GetGameInstance())) Game->ChooseCharacter(ETFFCharacter::Esined);
 ShowCustomization();
}
void UTFFMenuWidget::SelectJahde()
{
 if (auto* Game = Cast<UTFFGameInstance>(GetGameInstance())) Game->ChooseCharacter(ETFFCharacter::Jahde);
 ShowCustomization();
}
void UTFFMenuWidget::ShowCustomization()
{
 ClearAndTitle(TEXT("CUSTOMIZE APPEARANCE"));
 AddButton(TEXT("APPROVED DEFAULT"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::SetOutfitDefault);
 AddButton(TEXT("CASUAL OUTFIT"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::SetOutfitCasual);
 AddButton(TEXT("SPORT OUTFIT"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::SetOutfitSport);
 AddButton(TEXT("ACCEPT CHARACTER"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::ConfirmAppearance);
 AddButton(TEXT("BACK"))->OnClicked.AddDynamic(this, &UTFFMenuWidget::ShowCharacterSelection);
}
void UTFFMenuWidget::SetOutfitDefault()
{
 if (auto* Game = Cast<UTFFGameInstance>(GetGameInstance())) { FTFFAppearance A = Game->Appearance; A.Outfit = TEXT("Default"); Game->UpdateAppearance(A); }
}
void UTFFMenuWidget::SetOutfitCasual()
{
 if (auto* Game = Cast<UTFFGameInstance>(GetGameInstance())) { FTFFAppearance A = Game->Appearance; A.Outfit = TEXT("Casual"); Game->UpdateAppearance(A); }
}
void UTFFMenuWidget::SetOutfitSport()
{
 if (auto* Game = Cast<UTFFGameInstance>(GetGameInstance())) { FTFFAppearance A = Game->Appearance; A.Outfit = TEXT("Sport"); Game->UpdateAppearance(A); }
}
void UTFFMenuWidget::ConfirmAppearance()
{
 if (auto* Game = Cast<UTFFGameInstance>(GetGameInstance())) { Game->AcceptCharacter(); Game->SaveProgress(); }
 EnterWorld();
}
void UTFFMenuWidget::EnterWorld()
{
 if (auto* PC = GetOwningPlayer())
 {
  PC->SetInputMode(FInputModeGameOnly());
  PC->bShowMouseCursor = false;
 }
 RemoveFromParent();
}