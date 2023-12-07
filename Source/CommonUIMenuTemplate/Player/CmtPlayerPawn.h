// 

#pragma once

#include "CoreMinimal.h"
#include "CommonUIMenuTemplate/Core/CmtPawn.h"
#include "CmtPlayerPawn.generated.h"

UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtPlayerPawn : public ACmtPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACmtPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
