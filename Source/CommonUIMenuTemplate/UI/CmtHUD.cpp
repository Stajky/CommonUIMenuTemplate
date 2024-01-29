// 


#include "CmtHUD.h"

#include "Components/GameFrameworkComponentManager.h"
#include "Controller/PlayerOverlayController.h"
#include "Kismet/GameplayStatics.h"
#include "CommonUIExtensions.h"
#include "CommonUIMenuTemplate/CmtGameplayTags.h"
#include "ActivatableWidget/Widget/PlayerOverlay.h"
#include "ActivatableWidget/Widget/CheatWindow.h"
#include "../Player/CmtPlayerState.h"
#include "Controller/CheatWidgetController.h"



// Sets default values
ACmtHUD::ACmtHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}


void ACmtHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}


void ACmtHUD::BeginPlay()
{
	Super::BeginPlay();
	
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		SetupPlayerOverlayController(PC);
		SetupCheatWidgetController(PC);
	}
}


void ACmtHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}


UPlayerOverlayController* ACmtHUD::GetPlayerOverlayWidgetController()
{
	if(!PlayerOverlayWidgetController)
	{
		if(APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
		{
			SetupPlayerOverlayController(PC);
		}
	}
	return PlayerOverlayWidgetController;
}


UCheatWidgetController* ACmtHUD::GetCheatWidgetController()
{
	if(!CheatWidgetController)
	{
		if(APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
		{
			SetupCheatWidgetController(PC);
		}
	}
	return CheatWidgetController;
}


void ACmtHUD::ShowPlayerOverlay()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if(ULocalPlayer* LocalPlayer = UCommonUIExtensions::GetLocalPlayerFromController(PC))
		{
			//Crate the widget and push it to CommonUI stack (This will call Activate Widget)
			UCommonActivatableWidget* PlayerOverlay = UCommonUIExtensions::PushContentToLayer_ForPlayer(
				LocalPlayer, CmtTag::UI_Layer_Game, PlayerOverlayWidgetClass);

			//Save the new reference to HUD
			PlayerOverlayWidget = Cast<UPlayerOverlay>(PlayerOverlay);
		}
	}
}


void ACmtHUD::SetupPlayerOverlayController(APlayerController* PC)
{
	ACmtPlayerState* PS = PC->GetPlayerState<ACmtPlayerState>();
	check(PS);
			
	PlayerOverlayWidgetController = NewObject<UPlayerOverlayController>(this, PlayerOverlayWidgetControllerClass);
	PlayerOverlayWidgetController->Setup(PS);
	PlayerOverlayWidgetController->BindData();
}


void ACmtHUD::SetupCheatWidgetController(APlayerController* PC)
{
	ACmtPlayerState* PS = PC->GetPlayerState<ACmtPlayerState>();
	check(PS);
	
	CheatWidgetController = NewObject<UCheatWidgetController>(this, CheatWidgetControllerClass);
	CheatWidgetController->Setup(PS, PC);
}
