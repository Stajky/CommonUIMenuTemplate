// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SettingsTab.generated.h"

class UScrollBox;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API USettingsTab : public UCommonUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void CommitValues();

	
private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScrollBox> SettingsScrollBox;
};
