// Copyright Epic Games, Inc. All Rights Reserved.

#include "CmtSlider.h"
#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "../SWidget/SCmtSlider.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CmtSlider)

/////////////////////////////////////////////////////
// UAnalogSlider

UCmtSlider::UCmtSlider(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetOrientation(EOrientation::Orient_Horizontal);
	SetSliderBarColor(FLinearColor::White);
	SetSliderHandleColor(FLinearColor::White);
	SetStepSize(0.01f);
	IsFocusable = true;
}

TSharedRef<SWidget> UCmtSlider::RebuildWidget()
{
	MySlider = MyAnalogSlider = SNew(SCmtSlider)
		.Style(&GetWidgetStyle())
		.IsFocusable(IsFocusable)
		.OnMouseCaptureBegin(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnMouseCaptureBegin))
		.OnMouseCaptureEnd(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnMouseCaptureEnd))
		.OnControllerCaptureBegin(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnControllerCaptureBegin))
		.OnControllerCaptureEnd(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnControllerCaptureEnd))
		.OnValueChanged(BIND_UOBJECT_DELEGATE(FOnFloatValueChanged, HandleOnValueChanged))
		.OnFocused(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnFocused))
		.OnUnfocused(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnUnfocused))
		.OnAnalogCapture(BIND_UOBJECT_DELEGATE(FOnFloatValueChanged, HandleOnAnalogCapture));
	
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
	{
		MyAnalogSlider->SetUsingGamepad(CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad);
		CommonInputSubsystem->OnInputMethodChangedNative.AddUObject(this, &UCmtSlider::HandleInputMethodChanged);
	}

	return MySlider.ToSharedRef();
}

void UCmtSlider::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UCmtSlider::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyAnalogSlider.Reset();
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
	{
		CommonInputSubsystem->OnInputMethodChangedNative.RemoveAll(this);
	}
}

void UCmtSlider::HandleOnAnalogCapture(float InValue)
{
	OnAnalogCapture.Broadcast(InValue);
}

void UCmtSlider::HandleOnFocused()
{
	OnFocused().Broadcast();
	BP_OnFocused();
}

void UCmtSlider::HandleOnUnfocused()
{
	OnUnfocused().Broadcast();
	BP_OnUnfocused();
}

void UCmtSlider::HandleInputMethodChanged(ECommonInputType CurrentInputType)
{
	MyAnalogSlider->SetUsingGamepad(CurrentInputType == ECommonInputType::Gamepad);
}


