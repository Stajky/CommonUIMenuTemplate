// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUIMenuTemplate/UI/ActivatableWidget/CmtActivatableWidget.h"
#include "SettingsTab.generated.h"

class UScrollBox;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API USettingsTab : public UCmtActivatableWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void CommitValues();

	UFUNCTION(BlueprintCallable)
	void ResetToDefaults();
	
private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScrollBox> SettingsScrollBox;
};
