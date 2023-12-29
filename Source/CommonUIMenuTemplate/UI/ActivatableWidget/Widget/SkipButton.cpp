// 


#include "SkipButton.h"
#include "CommonUITypes.h"
#include "Input/CommonUIInputTypes.h"

void USkipButton::SetListeningForInput(bool bShouldListen)
{
	if (GetUISubsystem() == nullptr)
	{
		// Shutting down
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

{	// New input system binding flow
	if (bIsListeningForInput)
	{
		const bool bIsEnhancedInputSupportEnabled = CommonUI::IsEnhancedInputSupportEnabled();
		if (bIsEnhancedInputSupportEnabled && EnhancedInputAction)
		{
			FBindUIActionArgs args = FBindUIActionArgs(EnhancedInputAction, false,
			                                           FSimpleDelegate::CreateUObject(this, &USkipButton::SkipButtonPressedNative));
			args.KeyEvent = IE_Pressed;
			InputActionHandlePressed = RegisterUIActionBinding(args);

			args = FBindUIActionArgs(EnhancedInputAction, false,
			 	FSimpleDelegate::CreateUObject(this, &USkipButton::SkipButtonReleasedNative));
			args.KeyEvent = IE_Released;
			InputActionHandleReleased = RegisterUIActionBinding(args);
		}
		else
		{
			FBindUIActionArgs args = FBindUIActionArgs(InputAction, false,
			                                           FSimpleDelegate::CreateUObject(this, &USkipButton::SkipButtonPressedNative));
			args.KeyEvent = IE_Pressed;
			InputActionHandlePressed = RegisterUIActionBinding(args);

			args = FBindUIActionArgs(InputAction, false,
				FSimpleDelegate::CreateUObject(this, &USkipButton::SkipButtonReleasedNative));
			args.KeyEvent = IE_Released;
			InputActionHandleReleased = RegisterUIActionBinding(args);
		}
	}
	else
	{
		InputActionHandlePressed.Unregister();
		InputActionHandleReleased.Unregister();
	}
}

void USkipButton::SkipButtonReleasedNative() const
{
	OnSkipButtonReleased.Broadcast();
}

void USkipButton::SkipButtonPressedNative() const
{
	OnSkipButtonPressed.Broadcast();
}
