#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "StructUtils/InstancedStruct.h"
#include "GMASSyncedEvent.generated.h"

UCLASS()
class GMCABILITYSYSTEM_API UGMASSyncedEvent : public UObject
{
	GENERATED_BODY()
};

UENUM()
enum EGMASSyncedEventType
{
	BlueprintImplemented,
	Custom,
	AddImpulse,
	PlayMontage
};

USTRUCT(BlueprintType)
struct GMCABILITYSYSTEM_API FGMASSyncedEventContainer
{
	GENERATED_BODY()

	UPROPERTY()
	TEnumAsByte<EGMASSyncedEventType> EventType{BlueprintImplemented};

	UPROPERTY(BlueprintReadWrite, Category = "GMASSyncedEvent")
	FGameplayTag EventTag;

	UPROPERTY(BlueprintReadWrite, Category = "GMASSyncedEvent")
	FInstancedStruct InstancedPayload;
};

USTRUCT(BlueprintType)
struct GMCABILITYSYSTEM_API FGMASSyncedEventData_AddImpulse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Impulse")
	FVector Impulse {FVector::Zero()};

	UPROPERTY(BlueprintReadWrite, Category = "Impulse")
	bool bVelocityChange {false};
};