#pragma once


#include "NativeGameplayTags.h"
#include "Engine/DataAsset.h"
#include "CmtGameplayTags.generated.h"

class UInputAction;

/**
 * Input Action
 *
 * Struct used to map an Input Action to a Gameplay Tag
 */
USTRUCT(BlueprintType)
struct FInputActionToTagData
{
	GENERATED_BODY()

public:
	/** The IA asset for this input */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	/** The GameplayTag unique to this Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};


/**
 * Input Action Map
 *
 * Const DataAsset that allows us to map IA_* assets (that C++ can't
 * easily work with) to GameplayTags (which it can).
 *
 * When EnhancedInput is handling input, it will have the InputAction available,
 * but it will then need to translate that to a GameplayTag so C++ can deal with it.
 * Thus each InputAction should be listed ONLY ONCE.
 */
UCLASS(BlueprintType, Const)
class COMMONUIMENUTEMPLATE_API UInputActionToTagMap : public UDataAsset
{
	GENERATED_BODY()

public:
	UInputActionToTagMap(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag) const;

public:
	/**
	 * These input actions are mapped to a Gameplay Tag and must be manually bound
	 * via that Gameplay Tag in C++ to do whatever you want this input to do.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FInputActionToTagData> NativeInputActions;

};


namespace CmtTag
{

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Game);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_GameMenu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Menu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Modal);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Zoom);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GMSChannel_UI);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Modal_ConfirmSave);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Modal_ConfirmLoad);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Modal_ConfirmDelete);
}