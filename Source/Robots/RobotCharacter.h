// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "RobotCharacter.generated.h"


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

	// isAiming

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation, Replicated)
	//	bool isAiming;
	//void SetIsAiming(bool newisAiming);
	//UFUNCTION(Reliable, Server, WithValidation)
	//	void ServerSetIsAiming(bool newIsAiming);
	//virtual void ServerSetIsAiming_Implementation(bool newIsAiming);
	//virtual bool ServerSetIsAiming_Validate(bool newIsAiming);


	// canLaser

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		bool canLaser;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetCanLaser(bool newCanLaser);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetCanLaser(bool newCanLaser);
	virtual void ServerSetCanLaser_Implementation(bool newCanLaser);
	virtual bool ServerSetCanLaser_Validate(bool newCanLaser);

	// canAssimilate

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		bool canAssimilate;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetCanAssimilate(bool newCanAssimilate);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetCanAssimilate(bool newCanAssimilate);
	virtual void ServerSetCanAssimilate_Implementation(bool newCanAssimilate);
	virtual bool ServerSetCanAssimilate_Validate(bool newCanAssimilate);


	// canReveal

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		bool canReveal;
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SetCanReveal(bool newParam);
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetCanReveal(bool newParam);
	virtual void ServerSetCanReveal_Implementation(bool newParam);
	virtual bool ServerSetCanReveal_Validate(bool newParam);


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

	//UFUNCTION(BlueprintCallable, Category = "Gameplay")
	//void SetIsAimingFromBP(bool aim);



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

