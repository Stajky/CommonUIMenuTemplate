﻿// 

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerInputKey.h"
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
public:

	USettingsEditor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Commit Value"))
	void BP_CommitValue();

	UFUNCTION(BlueprintCallable)
	virtual void SetCurrentAsDefaultOption();

	UFUNCTION(BlueprintCallable)
	virtual void ResetToDefaultOption();
	
	/** Beware this needs to be setup in the child class where the input receiver is or it won't be called at all*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Focused"))
	void BP_OnFocused();

	/** Beware this needs to be setup in the child class where the input receiver is or it won't be called at all*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Unfocused"))
	void BP_OnUnfocused();

	/** Beware this needs to be setup in the child class where the input receiver is or it won't be called at all*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Hovered"))
	void BP_OnHovered();

	/** Beware this needs to be setup in the child class where the input receiver is or it won't be called at all*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Unhovered"))
	void BP_OnUnhovered();
	
	/** Beware this needs to be setup in the child class where the input receiver is or it won't be called at all*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Focused Event"))
	void BP_OnFocusedEvent(const FString& RichText);
	
protected:
	/*~ Start of UUserwidget */
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	// Focus transitioning to subwidgets for the gamepad
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
	/*~ End of UUserwidget */
	
	virtual UWidget* NativeGetPrimaryGamepadFocusWidget();

private:
	void HandleInputMethodChanged(ECommonInputType CurrentInputType);
	
public:

	UPROPERTY(BlueprintReadWrite)
	ECommonInputType InputType;
	
private:	// Bound Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_SettingName;
};
