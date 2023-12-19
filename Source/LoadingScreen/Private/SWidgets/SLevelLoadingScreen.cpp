#include "SWidgets/SLevelLoadingScreen.h"

#include "SWidgets/SLoadingScreenBackground.h"
#include "..\..\Public\SWidgets\STestLoadingScreen.h"

void SLevelLoadingScreen::Construct(const FArguments& InArgs)
{
	Settings = InArgs._Settings.Get();
	
	// Root widget and background
	TSharedRef<SOverlay> Root = SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SLoadingScreenBackground).Settings(Settings.BackgroundSettings)
		];

	ChildSlot
	[
		Root
	];
}
