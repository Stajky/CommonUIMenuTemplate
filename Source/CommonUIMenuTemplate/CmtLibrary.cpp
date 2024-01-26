// 


#include "CmtLibrary.h"

#include "CmtGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Messages/SimpleTagMessage_Float.h"
#include "Messages/SimpleTagMessage_Int.h"
#include "Player/CmtPlayerPawn.h"

UEnhancedInputLocalPlayerSubsystem* UCmtLibrary::GetEnhancedInputLocalPlayerSubsystem(
	const APlayerController* PlayerController)
{
	if(const APlayerController* PC = Cast<APlayerController>(PlayerController))
	{
		if (const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		}
	}

	return nullptr;
}


void UCmtLibrary::CmtSetMouseInputMode(APlayerController* PlayerController, bool bMouseVisible, bool bIgnoreLookInput,
                                       bool bIgnoreMoveInput)
{
	// You must give us a valid PlayerController
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController [%s] is not valid"), *GetNameSafe(PlayerController));
		return;
	}

	// Make sure the controller is connected to a local player
	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalPlayer is null"));
		return;
	}

	// We only need the base action router, not our custom one, though none of this
	// will work the way we want if this hasn't been overridden to use our custom
	// action router subsystem.
	UCommonUIActionRouterBase* ActionRouter = LocalPlayer->GetSubsystem<UCommonUIActionRouterBase>();
	if (!ActionRouter)
	{
		UE_LOG(LogTemp, Error, TEXT("Common UI Action Router subsystem is not available"));
		return;
	}

	// Create the new desired UI Input Config
	FUIInputConfig NewInputConfig;
	if (bMouseVisible)
	{
		// Input settings when mouse is Visible
		constexpr bool bHideCursorDuringViewportCapture = false;
		NewInputConfig = FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CaptureDuringMouseDown, bHideCursorDuringViewportCapture);
	}
	else
	{
		// Input settings when mouse is Invisible
		constexpr bool bHideCursorDuringViewportCapture = true;
		NewInputConfig = FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown, bHideCursorDuringViewportCapture);
	}

	// Apply Look/Move ignore switches
	NewInputConfig.bIgnoreLookInput = bIgnoreLookInput;
	NewInputConfig.bIgnoreMoveInput = bIgnoreMoveInput;

	// Set mouse visibility just *before* we change the UI Input Config
	PlayerController->SetShowMouseCursor(bMouseVisible);

	// Tell the Action Router to use this new input config
	ActionRouter->SetActiveUIInputConfig(NewInputConfig);
}

void UCmtLibrary::SendIntMessage(const UObject* WorldContextObject, FGameplayTag Tag, int32 Value)
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(WorldContextObject);
	FSimpleTagMessage_Int OutgoingMessage;
	OutgoingMessage.Tag = Tag;
	OutgoingMessage.Value = Value;
	MessageSubsystem.BroadcastMessage(CmtTag::GMSChannel_UI, OutgoingMessage);
}

void UCmtLibrary::SendFloatMessage(const UObject* WorldContextObject, FGameplayTag Tag, float Value)
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(WorldContextObject);
	FSimpleTagMessage_Float OutgoingMessage;
	OutgoingMessage.Tag = Tag;
	OutgoingMessage.Value = Value;
	MessageSubsystem.BroadcastMessage(CmtTag::GMSChannel_UI, OutgoingMessage);
}


