// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Widgets/Input/SSlider.h"

struct FAnalogInputEvent;

/**
 * THIS CLASS IS ALMOST ALL COPIED FROM SAnalogButton because I have difficulty with linker error in for its SAnalogSlider::Construct
 * For some reason it doesn't see it so I opted to copy the whole class and I couldnt properly inherit from it
 *
 * The change here is that I added focus support so this class will also call events OnFocus and OnUnfocus
 */
class SCmtSlider : public SSlider
{
public:

	SLATE_BEGIN_ARGS(SCmtSlider)
		: _IndentHandle(true)
		, _Locked(false)
		, _Orientation(EOrientation::Orient_Horizontal)
		, _SliderBarColor(FLinearColor::White)
		, _SliderHandleColor(FLinearColor::White)
		, _Style(&FCoreStyle::Get().GetWidgetStyle<FSliderStyle>("Slider"))
		, _StepSize(0.01f)
		, _Value(1.f)
		, _IsFocusable(true)
		, _OnMouseCaptureBegin()
		, _OnMouseCaptureEnd()
		, _OnValueChanged()
		, _OnAnalogCapture()
		, _OnFocused()
		, _OnUnfocused()
	{ }
	
		/** Whether the slidable area should be indented to fit the handle. */
		SLATE_ATTRIBUTE(bool, IndentHandle)

		/** Whether the handle is interactive or fixed. */
		SLATE_ATTRIBUTE(bool, Locked)

		/** The slider's orientation. */
		SLATE_ARGUMENT(EOrientation, Orientation)

		/** The color to draw the slider bar in. */
		SLATE_ATTRIBUTE(FSlateColor, SliderBarColor)

		/** The color to draw the slider handle in. */
		SLATE_ATTRIBUTE(FSlateColor, SliderHandleColor)

		/** The style used to draw the slider. */
		SLATE_STYLE_ARGUMENT(FSliderStyle, Style)

		/** The input mode while using the controller. */
		SLATE_ATTRIBUTE(float, StepSize)

		/** A value that drives where the slider handle appears. Value is normalized between 0 and 1. */
		SLATE_ATTRIBUTE(float, Value)

		/** Sometimes a slider should only be mouse-clickable and never keyboard focusable. */
		SLATE_ARGUMENT(bool, IsFocusable)

		/** Invoked when the mouse is pressed and a capture begins. */
		SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin)

		/** Invoked when the mouse is released and a capture ends. */
		SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd)

		/** Invoked when the Controller is pressed and capture begins. */
		SLATE_EVENT(FSimpleDelegate, OnControllerCaptureBegin)

		/** Invoked when the controller capture is released.  */
		SLATE_EVENT(FSimpleDelegate, OnControllerCaptureEnd)

		/** Called when the value is changed by the slider. */
		SLATE_EVENT(FOnFloatValueChanged, OnValueChanged)

		/** Invoked when the mouse is pressed and a capture begins. */
		SLATE_EVENT(FOnFloatValueChanged, OnAnalogCapture)

		/** Invoked when the controller capture is released.  */
		SLATE_EVENT(FSimpleDelegate, OnFocused)
	
		/** Invoked when the controller capture is released.  */
		SLATE_EVENT(FSimpleDelegate, OnUnfocused)

	
	SLATE_END_ARGS()
	
	/**
	* Construct the widget.
	*
	* @param InDeclaration A declaration from which to construct the widget.
	*/
	void Construct(const SCmtSlider::FArguments& InDeclaration);

	// Input overrides, for adding controller input to the slider
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& InAnalogInputEvent) override;
	virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override;
	void SetUsingGamepad(bool InUsingGamepad);
	
	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;
	
private:
	// Holds a delegate that is executed when the mouse is let up and a capture ends.
	FOnFloatValueChanged OnAnalogCapture;

	FSimpleDelegate OnFocused;
	FSimpleDelegate OnUnfocused;
	bool bIsUsingGamepad = false;

	/** The last app time we stepped with analog input */
	double LastAnalogStepTime = 0;
};
