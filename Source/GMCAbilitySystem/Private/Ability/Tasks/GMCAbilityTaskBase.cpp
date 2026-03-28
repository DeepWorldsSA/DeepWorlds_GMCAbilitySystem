#include "Ability/Tasks/GMCAbilityTaskBase.h"

#include "GMCAbilityComponent.h"
#include "Ability/GMCAbility.h"



void UGMCAbilityTaskBase::Activate()
{
	Super::Activate();
	RegisterTask(this);
}

void UGMCAbilityTaskBase::EndTaskGMAS()
{
	EndTask();
}

void UGMCAbilityTaskBase::SetAbilitySystemComponent(UGMC_AbilitySystemComponent* InAbilitySystemComponent)
{
	this->AbilitySystemComponent = InAbilitySystemComponent;
}

void UGMCAbilityTaskBase::RegisterTask(UGMCAbilityTaskBase* Task)
{
	TaskID = Ability->GetNextTaskID();
	Ability->RegisterTask(TaskID, Task);
}

void UGMCAbilityTaskBase::Tick(float DeltaTime)
{

}

void UGMCAbilityTaskBase::AncillaryTick(float DeltaTime)
{
}

void UGMCAbilityTaskBase::ClientProgressTask()
{
	FGMCAbilityTaskData TaskData;
	TaskData.TaskType = EGMCAbilityTaskDataType::Progress;
	TaskData.AbilityID = Ability->GetAbilityID();
	TaskData.TaskID = TaskID;
	const FInstancedStruct TaskDataInstance = FInstancedStruct::Make(TaskData);

	// Reliable RPC for server delivery (supplements lossy GMC move pipeline)
	Ability->OwnerAbilityComponent->ServerRPC_ProgressTask(
		Ability->GetAbilityID(), TaskID, TaskDataInstance);

	// Also queue via GMC for local prediction (client processes immediately)
	Ability->OwnerAbilityComponent->QueueTaskData(TaskDataInstance);
}

bool UGMCAbilityTaskBase::IsClientOrRemoteListenServerPawn() const
{
	return (AbilitySystemComponent->GetNetMode() != NM_DedicatedServer &&
		AbilitySystemComponent->GetNetMode() != NM_ListenServer) ||
		AbilitySystemComponent->GMCMovementComponent->IsLocallyControlledServerPawn();
}
