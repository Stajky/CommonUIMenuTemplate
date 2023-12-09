#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TestMessage.generated.h"


/**
 * Time Message
 */
USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FTestMessage
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag Verb;
	
};
