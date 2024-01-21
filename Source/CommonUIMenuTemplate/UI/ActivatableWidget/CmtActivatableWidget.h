

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CmtActivatableWidget.generated.h"

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
 * A common activatable widget with option to define which input it should response to
 *
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	UCmtActivatableWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface


	UFUNCTION(BlueprintCallable)
	virtual void BP_RefreshFocus(); 
	
protected:
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category=Input)
	ECmtWidgetInputMode InputMode = ECmtWidgetInputMode::Default;	
};
