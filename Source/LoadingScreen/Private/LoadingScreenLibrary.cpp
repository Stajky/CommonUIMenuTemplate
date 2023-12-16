// 


#include "LoadingScreenLibrary.h"
#include "LoadingScreenModule.h"
#include "Modules/ModuleManager.h"

FLoadingScreenModule& ULoadingScreenLibrary::GetLoadingScreenModuleModule()
{
	return FModuleManager::LoadModuleChecked<FLoadingScreenModule>("LoadingScreen");
}

bool ULoadingScreenLibrary::IsLoadingScreenAvailable()
{
	return FModuleManager::Get().IsModuleLoaded("LoadingScreen");
}
