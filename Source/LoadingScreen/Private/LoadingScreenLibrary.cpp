// 
#include "LoadingScreenLibrary.h"
#include "Modules/ModuleManager.h"
#include "SWidgets/SLevelLoadingScreen.h"
#include "..\Public\SWidgets\STestLoadingScreen.h"


void ULoadingScreenLibrary::StartLoadingScreen(const FLevelLoadingScreenSettings& Settings, float MinimumLoadingScreenDisplayTime = 3.f)
{
	FLoadingScreenAttributes LSAttributes;
	LSAttributes.MinimumLoadingScreenDisplayTime = MinimumLoadingScreenDisplayTime;
	LSAttributes.WidgetLoadingScreen = SNew(SLevelLoadingScreen).Settings(Settings);
	GetMoviePlayer()->SetupLoadingScreen(LSAttributes);
}
