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
	// Here is an option to basically take control when the loading screen ends
	// By default the loading screen will end when level is loaded it might be a good idea to use this if
	// we need to wait for some other async function as well (I dont know loading a save file or something)
	// Currently its not used RN since I assume that the level load will take more time than other things, but
	// in the future I might need to revisit this. Good luck future someone
	// LSAttributes.bWaitForManualStop = true;
	GetMoviePlayer()->SetupLoadingScreen(LSAttributes);
	
}

void ULoadingScreenLibrary::StopLoadingScreen()
{
	GetMoviePlayer()->StopMovie();
}
