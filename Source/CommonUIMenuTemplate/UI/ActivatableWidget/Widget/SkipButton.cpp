// 


#include "SkipButton.h"
#include "CommonUITypes.h"
#include "Input/CommonUIInputTypes.h"

void USkipButton::SetListeningForInput(bool bShouldListen)
{
	if (GetUISubsystem() == nullptr)
	{
		return;
	}

	if (bShouldListen != bIsListeningForInput)
	{
		bIsListeningForInput = bShouldListen;
		UpdateBindings();
	}
}

void USkipButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (bAutoListenForInput)
	{
		SetListeningForInput(true);
	}
}

void USkipButton::NativeDestruct()
{
	SetListeningForInput(false);
	Super::NativeDestruct();
}

void USkipButton::UpdateBindings()

{	
	if (bIsListeningForInput)
	{
		const bool bIsEnhancedInputSupportEnabled = CommonUI::IsEnhancedInputSupportEnabled();
		if (bIsEnhancedInputSupportEnabled && EnhancedInputAction)
		{
			FBindUIActionArgs args = FBindUIActionArgs(EnhancedInputAction, false,
			                                           FSimpleDelegate::CreateUObject(this, &USkipButton::NativeSkipButtonPressed));
			args.KeyEvent = IE_Pressed;
			args.OnHoldActionProgressed.BindUObject(this, &USkipButton::NativeHeldProgress);
			InputActionHandlePressed = RegisterUIActionBinding(args);
		}
		else
		{
			FBindUIActionArgs args = FBindUIActionArgs(InputAction, false,
			                                           FSimpleDelegate::CreateUObject(this, &USkipButton::NativeSkipButtonPressed));
			args.KeyEvent = IE_Pressed;
			args.OnHoldActionProgressed.BindUObject(this, &USkipButton::NativeHeldProgress);
			InputActionHandlePressed = RegisterUIActionBinding(args);
		}
	}
	else
	{
		InputActionHandlePressed.Unregister();
	}
}

void USkipButton::NativeHeldProgress(float HeldPercent)
{
	BP_HeldProgressEvent(HeldPercent);
}

void USkipButton::NativeSkipButtonPressed() const
{
	OnSkipButtonPressed.Broadcast();
}
