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

    // Функция взаимодействия
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Interact();

    // Компоненты
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* CubeMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* InteractionCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* TextRenderComponent;

    // Звук при взаимодействии
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    USoundBase* InteractionSound;

    // Текст для отображения
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FString InteractionText;

    // Время отображения текста
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float TextDisplayTime = 3.0f;

    // Таймер для скрытия текста
    FTimerHandle TextTimerHandle;

    // Функция для скрытия текста
    UFUNCTION()
    void HideText();

    // Делегат для UI
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteraction, FString, Message);

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnInteraction OnInteraction;
};