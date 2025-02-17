// Fill out your copyright notice in the Description page of Project Settings.


#include "WallRunningComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UWallRunningComponent::UWallRunningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//default values for variables

	b_isWallRunning = false;
	b_isJumping = false;
	f_wallRunGravityScale = 0.0f;
	f_normalGravityScale = 1.0f;

}


// Called when the game starts
void UWallRunningComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//ger owner and movement
	ac_wallRunCharacter = Cast<ACharacter>(GetOwner());
	if (ac_wallRunCharacter)
	{
		uc_movementComponent = ac_wallRunCharacter->GetCharacterMovement();

		//binding a jump event
		ac_wallRunCharacter->Jump().AddDynamic(this, &UWallRunningComponent::OnJump);
		ac_wallRunCharacter->LandedDelegate.AddDynamic(this, UWallRunningComponent::OnLanded);
	}

}


// Called every frame
void UWallRunningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//only check for walls when character is jumping and not already on a wall
	if (b_isJumping && !b_isWallRunning)
		WallCheck();
}

void UWallRunningComponent::WallCheck()
{
	FVector start = ac_wallRunCharacter->GetActorLocation();
	FVector rightVector = ac_wallRunCharacter->GetActorRightVector();

	FVector endRight = start + (rightVector * 100.0f);
	FVector endLeft = start - (rightVector * 100.0f);

	FHitResult hitRight, hitLeft;
	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(ac_wallRunCharacter); // insures the character will ignore itself

	bool bHitRight = GetWorld()->LineTraceSingleByChannel(hitRight, start, endRight, ECC_Visibility, traceParams);
	bool bHitLeft = GetWorld()->LineTraceSingleByChannel(hitLeft, start, endLeft, ECC_Visibility, traceParams);

	//makes debug lines visible in the scene
	DrawDebugLine(GetWorld(), start, endRight, FColor::Red, false, 0.1f, 0, 2.0f);
	DrawDebugLine(GetWorld(), start, endLeft, FColor::Red, false, 0.1f, 0, 2.0f);

	//if wall is detected
	if (bHitRight)
	{
		WallRunStart(hitRight.ImpactNormal);
	}
	else if (bHitLeft)
	{
		WallRunStart(hitLeft.ImpactNormal);
	}
}





void UWallRunningComponent::WallRunStart(const FVector& wallNormal)
{
	b_isWallRunning = true;

	//determine movment direction while wall running
	fv_wallRunDirection = FVector::CrossProduct(wallNormal, FVector::UpVector);
	fv_wallRunDirection.Normalize();

	//apply movemnt along wall
	ac_wallRunCharacter->LaunchCharacter(fv_wallRunDirection * 600.0f, true, false);

	//reduce gravity
	f_normalGravityScale = f_wallRunGravityScale;
}

void UWallRunningComponent::WallRunStop()
{
	b_isWallRunning = false;

	//restore normal gravity
	f_normalGravityScale = 1.0f;
}

void UWallRunningComponent::OnJump()
{
	b_isJumping = true;

	if (b_isWallRunning)
		WallRunStop();
}

void UWallRunningComponent::OnLanded(const FHitResult& Hit)
{
	b_isJumping = false;
}



