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

	//Load Settings
	//Load Save info
	//Load Save Data
	//Load Serialize
	//Save Serialize
	//Load
	//save
	//Load all info data
	//lastplayed/continue slot
	// dava smysl hodit sem neco jako config object, kde se daji nastavit vse mozne shity tam se to jmenovalo preset
	
	// /** If true save files will be compressed
 // * Performance: Can add from 10ms to 20ms to loading and saving (estimate) but reduce file sizes making them up to 30x smaller
 // */
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Serialization)
	// bool bUseCompression = true;

	// /** If checked, will attempt to Save Game to first Slot found, timed event. */
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (EditCondition = "bAutoSave"))
	// bool bSaveOnExit = false;

	//this should be by default
	// /** Serialization will be multi-threaded between all available cores. */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asynchronous")
	// ESaveASyncMode MultithreadedSerialization = ESaveASyncMode::SaveAsync;

	// This we want yes
	// /** Files will be loaded or saved on a secondary thread while game continues */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asynchronous")
	// ESaveASyncMode MultithreadedFiles = ESaveASyncMode::SaveAndLoadAsync;

	
	//Delete
	//Refresh UI - po delete i po pridani slotu 

	//Event pro OnLoadStarted OnLoadFinished a OnSaveStarted OnSaveFinished - komunikace s UI
	//Some event logic for when level is loaded or rather when 
	
private:
	
	// Active save file - for quick save
	// Game instance could be usefull
	// Settings Data
	// Save Info (basicaly thumbnail data for UI, SaveFile name, timestamp, ...) - current
	// Save Data (the real ingame usfull data) - current
	
};
