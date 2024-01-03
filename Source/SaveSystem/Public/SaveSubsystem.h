// 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SAVESYSTEM_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USaveSubsystem();

	/** Get the global save manager */
	static USaveSubsystem* Get(const UObject* ContextObject);

	/** Begin USubsystem */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/** End USubsystem */

	//TODO implement later, when all is setup it will be easy
	void Quicksave();

	//Load Serialize
	//Save Serialize
	//Load
	//save

	//Some event logic for when level is loaded or rather when 
	
private:
	
	// Active save file - for quick save
	// Settings Data
	// Game instance could be usefull
	// Save Info (basicaly thumbnail data for UI, SaveFile name, timestamp, ...) - current
	// Save Data (the real ingame usfull data) - current
	
};
