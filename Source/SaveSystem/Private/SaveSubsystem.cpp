// 


#include "SaveSubsystem.h"

USaveSubsystem::USaveSubsystem()
	: Super()
{
}

USaveSubsystem* USaveSubsystem::Get(const UObject* ContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(ContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		return UGameInstance::GetSubsystem<USaveSubsystem>(World->GetGameInstance());
	}
	return nullptr;
}

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USaveSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void USaveSubsystem::Quicksave()
{
}
