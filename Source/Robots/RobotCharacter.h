// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "RobotCharacter.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EStanding : uint8
{
	GOOD 	UMETA(DisplayName = "Good"),
	SUSPECT 	UMETA(DisplayName = "Suspect"),
	ROGUE	UMETA(DisplayName = "Rogue"),
};


UCLASS(config = Game)
class ARobotCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PunchZone, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* PunchZone;
	


public:
	ARobotCharacter();

	virtual void Tick(float DeltaTime) override;

	// alive
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		bool alive;
	UFUNCTION(BlueprintCallable, Category = "Alive")
	void SetIsAlive(bool newAlive);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetIsAlive(bool newAlive);
	virtual void ServerSetIsAlive_Implementation(bool newAlive);
	virtual bool ServerSetIsAlive_Validate(bool newAlive);


	// health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		float health;
	void SetHealth(float health);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetHealth(float newHealth);
	virtual void ServerSetHealth_Implementation(float newHealth);
	virtual bool ServerSetHealth_Validate(float newHealth);


	// speed

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		float speed;
	void SetSpeed(float speed);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetSpeed(float newSpeed);
	virtual void ServerSetSpeed_Implementation(float newSpeed);
	virtual bool ServerSetSpeed_Validate(float newSpeed);

	// ispunching

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation, Replicated)
		bool isPunching;
	void SetIsPunching(bool newIsPunching);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetIsPunching(bool newIsPunching);
	virtual void ServerSetIsPunching_Implementation(bool newIsPunching);
	virtual bool ServerSetIsPunching_Validate(bool newIsPunching);


	// canLaser

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
		bool canLaser;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetCanLaser(bool newCanLaser);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetCanLaser(bool newCanLaser);
	virtual void ServerSetCanLaser_Implementation(bool newCanLaser);
	virtual bool ServerSetCanLaser_Validate(bool newCanLaser);

	// canAssimilate

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
		bool canAssimilate;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetCanAssimilate(bool newCanAssimilate);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetCanAssimilate(bool newCanAssimilate);
	virtual void ServerSetCanAssimilate_Implementation(bool newCanAssimilate);
	virtual bool ServerSetCanAssimilate_Validate(bool newCanAssimilate);


	// canReveal

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
		bool canReveal;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetCanReveal(bool newParam);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetCanReveal(bool newParam);
	virtual void ServerSetCanReveal_Implementation(bool newParam);
	virtual bool ServerSetCanReveal_Validate(bool newParam);

	// canBomb

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
		bool canBomb;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetCanBomb(bool newParam);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetCanBomb(bool newParam);
	virtual void ServerSetCanBomb_Implementation(bool newParam);
	virtual bool ServerSetCanBomb_Validate(bool newParam);

	// standing

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
		EStanding standing;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetStanding(EStanding newParam);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetStanding(EStanding newParam);
	virtual void ServerSetStanding_Implementation(EStanding newParam);
	virtual bool ServerSetStanding_Validate(EStanding newParam);

	// carrying

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
		bool isCarrying;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetIsCarrying(bool newParam);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetIsCarrying(bool newParam);
	virtual void ServerSetIsCarrying_Implementation(bool newParam);
	virtual bool ServerSetIsCarrying_Validate(bool newParam);

	// throwing

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
		bool isThrowing;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetIsThrowing(bool newParam);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetIsThrowing(bool newParam);
	virtual void ServerSetIsThrowing_Implementation(bool newParam);
	virtual bool ServerSetIsThrowing_Validate(bool newParam);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetIsPunchingFromBP(bool punch);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool canActivate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FString activatableName;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		AActor* getActorInFront();

	void Exit();



protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void FirePressed();
	void FireReleased();

	void SprintPressed();
	void SprintReleased();
	
	void RestartPressed();

	UFUNCTION(Server, Reliable, WithValidation)
		void Activate();
	virtual void Activate_Implementation();
	virtual bool Activate_Validate();




protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

