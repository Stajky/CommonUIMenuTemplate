// 
#include "LoadingScreenLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Modules/ModuleManager.h"
#include "SWidgets/SLevelLoadingScreen.h"
#include "..\Public\SWidgets\STestLoadingScreen.h"


bool ULoadingScreenLibrary::IsLoadingScreenAvailable()
{
	return FModuleManager::Get().IsModuleLoaded("LoadingScreen");
}

void ULoadingScreenLibrary::StartLoadingScreen(const FLevelLoadingScreenSettings& Settings)
{
	
	FLoadingScreenAttributes LSAttributes;
	LSAttributes.MinimumLoadingScreenDisplayTime = 10.0f;
	LSAttributes.WidgetLoadingScreen = SNew(SLevelLoadingScreen).Settings(Settings);
	GetMoviePlayer()->SetupLoadingScreen(LSAttributes);
	
}
