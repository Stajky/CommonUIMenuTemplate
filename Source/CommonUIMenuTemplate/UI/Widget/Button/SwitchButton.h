﻿// 

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "SwitchButton.generated.h"


class UCommonTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitched, int32, Value);


/**
 * A class that has the ability to switch between text array and simulates the small buttons select bar by texture 
 */
UCLASS(meta = (DisableNativeTick))
class COMMONUIMENUTEMPLATE_API USwitchButton : public UCommonButtonBase
{
	GENERATED_UCLASS_BODY()

public:

	virtual bool Initialize() override;
	virtual FNavigationReply NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply) override;

	/** Handle and use controller navigation to rotate text */
	FNavigationDelegate OnNavigation;
	TSharedPtr<SWidget> HandleNavigation(EUINavigation UINavigation);

	/** Set the array of texts available */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	void PopulateTextLabels(TArray<FText> Labels);

	/** Gets the current text value of the slider. */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	FText GetSelectedText() const;

	/** Sets the current value of the slider. */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	virtual void SetSelectedItem(int32 InValue);

	/** Gets the current selected index */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	int32 GetSelectedIndex() const { return SelectedIndex; }

	/** Shift the current text left. */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	void ShiftTextLeft();

	/** Shift the current text right. */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	void ShiftTextRight();

	/**  Sets the default value of the slider. */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	int32 GetCurrentOptionIndex();

	/**  Sets the default value of the slider. */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	int32 GetDefaultOptionIndex();
	
	/**  Sets the default value of the slider. */
	UFUNCTION(BlueprintCallable, Category = "Switch Button")
	void SetDefaultOption(int32 DefaultOptionIndex);

public:

	/** Called when the Selected state of this button changes */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSwitched OnSwitched;

	DECLARE_EVENT_TwoParams(UCommonRotator, FSwitchedEvent, int32 /*Value*/, bool /*bUserInitiated*/);
	FSwitchedEvent OnSwitchedEvent;

protected:
	void ShiftTextLeftInternal();
	void ShiftTextRightInternal();
	
	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Options Populated"))
	void BP_OnOptionsPopulated(int32 Count);

	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Options Selected"))
	void BP_OnOptionSelected(int32 Index);

	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Default Option Specified"))
	void BP_OnDefaultOptionSpecified(int32 DefaultOptionIndex);
protected:

	/** The displayed text */
	UPROPERTY(BlueprintReadOnly, Category = CommonRotator, Meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> LabelText;

	// Holds the array of display texts
	TArray<FText> TextLabels;

	/** The index of the current text item */
	int32 SelectedIndex;
	int32 DefaultIndex;
};
