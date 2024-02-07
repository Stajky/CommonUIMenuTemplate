﻿// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SettingsEditor.generated.h"


class UTextBlock;

/**
 * This class represents settings editor its main funcionality is to focus given child insdead of the button itself (so that it can recieve input for gamepad)
 *
 * Idealy here would also be communication logic between settings system as well AKA we would have pointer to the setting we refer to
 * It make sense to me to create a Parent class that this would inherit from that has that would provide the communication funcionality
 * the parent would have a controller that would handle the communication (similar to ActivitableWidgets
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API USettingsEditor : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	/*~ Start of UUserwidget */ 
	// Focus transitioning to subwidgets for the gamepad
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	/*~ End of UUserwidget */
	
	virtual UWidget* NativeGetPrimaryGamepadFocusWidget();
	
private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_SettingName;
};
