#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Sound/SoundBase.h"
#include "InteractiveCube.generated.h"

UCLASS()
class VENDING_API AInteractiveCube : public AActor
{
    GENERATED_BODY()

public:
    AInteractiveCube();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // ������� ��������������
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Interact();

    // ����������
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* CubeMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* InteractionCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* TextRenderComponent;

    // ���� ��� ��������������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    USoundBase* InteractionSound;

    // ����� ��� �����������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FString InteractionText;

    // ����� ����������� ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float TextDisplayTime = 3.0f;

    // ������ ��� ������� ������
    FTimerHandle TextTimerHandle;

    // ������� ��� ������� ������
    UFUNCTION()
    void HideText();

    // ������� ��� UI
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteraction, FString, Message);

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnInteraction OnInteraction;
};