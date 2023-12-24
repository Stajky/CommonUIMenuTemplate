#include "SWidgets/SLevelLoadingScreen.h"

#include "SWidgets/SLoadingScreenBackground.h"
#include "..\..\Public\SWidgets\STestLoadingScreen.h"
#include "SWidgets/SImageSequenceLoading.h"
#include "SWidgets/STipPanel.h"

void SLevelLoadingScreen::Construct(const FArguments& InArgs)
{
	Settings = InArgs._Settings.Get();
	
	// Root widget and background
	TSharedRef<SOverlay> Root =
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SLoadingScreenBackground).Settings(Settings.BackgroundSettings)
		];
	
	// Add tip panel
	Root->AddSlot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Bottom)
	.Padding(Settings.TipPanelSettings.Padding)
	[
	SNew(STipPanel).Settings(Settings.TipPanelSettings)
	];
	
	//Add image sequence
	Root->AddSlot()
	.HAlign(HAlign_Right)
	.VAlign(VAlign_Bottom)
	.Padding(Settings.ImageSequenceSettings.Padding)
	[
		SNew(SImageSequenceLoading).Settings(Settings.ImageSequenceSettings)
	];
	
	ChildSlot
	[
		Root
	];
}
