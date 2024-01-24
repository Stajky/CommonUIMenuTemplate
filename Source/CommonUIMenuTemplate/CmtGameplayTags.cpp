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


	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GMSChannel_UI, "GMSChannel.UI", "Gameplay Message System UI channel");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Level, "UI.Message.Level", "GMS Message with level data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_XP, "UI.Message.XP", "GMS Message with XP data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Health, "UI.Message.Health", "GMS Message with Health data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Mana, "UI.Message.Mana", "GMS Message with Mana data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell1, "UI.Message.Spell1", "GMS Message with Spell1 data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell2, "UI.Message.Spell2", "GMS Message with Spell2 data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell3, "UI.Message.Spell3", "GMS Message with Spell3 data");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Message_Spell4, "UI.Message.Spell4", "GMS Message with Spell4 data");
	
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
