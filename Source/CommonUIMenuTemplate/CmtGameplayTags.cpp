#include "CmtGameplayTags.h"


namespace CmtTag
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Game,          "UI.Layer.Game", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_GameMenu,      "UI.Layer.GameMenu", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Menu,          "UI.Layer.Menu", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Modal,         "UI.Layer.Modal", "");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look,          "InputTag.Look", "Player Look");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move,          "InputTag.Move", "Player Move");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Zoom,          "InputTag.Zoom", "Zoom Camera");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Cheat_F1, "InputTag.Cheat.F1", "Cheat Input for F1 key");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GMSChannel_UI, "GMSChannel.UI", "Gameplay Message System UI channel");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Level, "UI.Message.Level", "GMS Message with level data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_XPPercent, "UI.Message.XPPercent", "GMS Message with XP Percent data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_HealthPercent, "UI.Message.HealthPercent", "GMS Message with Health Percent data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_ManaPercent, "UI.Message.ManaPercent", "GMS Message with Mana Percent data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell1Cooldown, "UI.Message.Spell1Cooldown", "GMS Message with Spell1 Cooldown data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell2Cooldown, "UI.Message.Spell2Cooldown", "GMS Message with Spell2 Cooldown data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell3Cooldown, "UI.Message.Spell3Cooldown", "GMS Message with Spell3 Cooldown data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell4Cooldown, "UI.Message.Spell4Cooldown", "GMS Message with Spell4 Cooldowndata");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Modal_ConfirmLoad, "UI.Modal.ConfirmLoad", "UI Modal Confirm Load Message");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Modal_ConfirmSave, "UI.Modal.ConfirmSave", "UI Modal Confirm Save Message");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Modal_ConfirmDelete, "UI.Modal.ConfirmDelete", "UI Modal Confirm Delete Message");
}

UInputActionToTagMap::UInputActionToTagMap(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

const UInputAction* UInputActionToTagMap::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
	const UInputAction* Result {nullptr};

	for (const FInputActionToTagData& Action : NativeInputActions)
	{
		const bool bMatch = Action.InputAction && (Action.InputTag == InputTag);
		if (bMatch && !Result)
		{
			// This tag matches; this is our result
			Result = Action.InputAction;
		}
		else if (bMatch)
		{
			// This tag matches, but we already have a result! Data error
			UE_LOG(LogTemp, Error, TEXT("Found multiple instances of InputTag [%s]; using only the first"), *InputTag.ToString());
		}
	}

	if (!Result)
	{
		UE_LOG(LogTemp, Error, TEXT("No InputAction found for InputTag [%s]"), *InputTag.ToString());
	}

	return Result;
}
