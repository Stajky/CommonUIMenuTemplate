

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CmtCommonActivatableWidget.generated.h"

/**
 * Input Modes that GthrActivatableWidgets can activate
 */
UENUM(BlueprintType)
enum class ECmtWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};



/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	UCmtCommonActivatableWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface
	
protected:
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category=Input)
	ECmtWidgetInputMode InputMode = ECmtWidgetInputMode::Default;	
};
