// Copyright Simon Stockhause


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();


	FRotator DoorRotator = GetOwner()->GetActorRotation();
	StartYaw  = DoorRotator.Yaw;
	TargetYaw = StartYaw + 90.f;
	GetOwner()->SetActorRotation(DoorRotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/**
	 * FInterpTo vs Lerp
	 * Use Lerp() when you want to "move object X from location A to location B in time T"
	 * Use InterpTo() when you want to "move object X toward (potentially moving) location A at Speed S and stop when you get there"  
	*/
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	float Alpha = 2.f;
	float Delta = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime,Alpha);

	// Alternative Approach
	// float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	// float Alpha = 0.01f;
	// float Delta = FMath::Lerp(CurrentYaw, TargetYaw, Alpha);

	// Debug
	if(CurrentYaw != TargetYaw){
		UE_LOG(LogTemp,Warning,TEXT("%s "), *GetOwner()->GetActorRotation().ToString());
		UE_LOG(LogTemp,Warning,TEXT("Yaw is %f "), GetOwner()->GetActorRotation().Yaw);
	}
	FRotator Rotator = {0,Delta,0};
	GetOwner()->SetActorRelativeRotation(Rotator, true);

}

