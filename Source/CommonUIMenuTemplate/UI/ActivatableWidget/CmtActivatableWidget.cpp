


#include "CmtActivatableWidget.h"



UCmtActivatableWidget::UCmtActivatableWidget(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

TOptional<FUIInputConfig> UCmtActivatableWidget::GetDesiredInputConfig() const
{
	FUIInputConfig ConfigOverride;

	switch (InputMode)
	{
	case ECmtWidgetInputMode::Game:
		ConfigOverride = FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
		break;
	case ECmtWidgetInputMode::GameAndMenu:
		ConfigOverride = FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CaptureDuringMouseDown);
		break;
	case ECmtWidgetInputMode::Menu:
		ConfigOverride = FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		break;
	case ECmtWidgetInputMode::Default:
	default:
		// By default, no input change is desired, return an empty config
		return TOptional<FUIInputConfig>();
	}

	return ConfigOverride;
}
