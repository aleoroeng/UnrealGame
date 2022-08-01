// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("HEREEEEEEEEEEE"));
	int result = SqlUtil::OpenConnection();
	UE_LOG(LogTemp, Display, TEXT("HEREEEEEEEEEEE, result: %d"), result);
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindUObject(this, &ACameraDirector::OnResponseReceived);
	Request->SetURL("http://localhost:5000/unreal/test");
	Request->ProcessRequest();
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBendTime = 10.0f;
	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.0f) {
		TimeToNextCameraChange += SmoothBendTime;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController) {
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr)) {
				OurPlayerController->SetViewTarget(CameraOne);
			}
			else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr)) {
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBendTime);
			}
			
		}
		
	}
}

void ACameraDirector::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	UE_LOG(LogTemp, Display, TEXT("Response from server: %s"), *Response->GetContentAsString());
}
