// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/Slider.h"
#include "CmtSlider.generated.h"

enum class ECommonInputType : uint8;

class SCmtSlider;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFocusEventSignature);

/**
 * A simple widget that shows a sliding bar with a handle that allows you to control the value between 0..1.
 *
 * * No Children
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtSlider : public USlider
{
	GENERATED_UCLASS_BODY()

public:
	/** Called when the value is changed by slider or typing. */
	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnFloatValueChangedEvent OnAnalogCapture;
	
	// UWidget interface
	virtual void SynchronizeProperties() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
	
	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface
	
	DECLARE_EVENT(UCmtSlider, FUCmtSliderEvent);
	FUCmtSliderEvent& OnFocused() const { return OnFocusedEvent; }
	FUCmtSliderEvent& OnUnfocused() const { return OnUnfocusedEvent; }
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Focused"))
	void BP_OnFocused();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Unfocused"))
	void BP_OnUnfocused();
	
protected:
	UFUNCTION()
	virtual void HandleOnAnalogCapture(float InValue);
	
	UFUNCTION()
	virtual void HandleOnFocused();
	
	UFUNCTION()
	virtual void HandleOnUnfocused();

	void HandleInputMethodChanged(ECommonInputType CurrentInputType);


protected:
	TSharedPtr<SCmtSlider> MyAnalogSlider;

private:
	mutable FUCmtSliderEvent OnFocusedEvent;
	mutable FUCmtSliderEvent OnUnfocusedEvent;
};

#if UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_2
#include "CommonInputSubsystem.h"
#include "SAnalogSlider.h"
#include "Types/NavigationMetaData.h"
#endif
