

UCLASS(BlueprintType, Blueprintable, config=Engine, meta=(ShortTooltip="An Actor is an object that can be placed or spawned in the world."))
class ENGINE_API AActor : public UObject
{
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Replication)
	uint8 bReplicates:1;


	/** If true, this actor is only relevant to its owner. If this flag is changed during play, all non-owner channels would need to be explicitly closed. */
	UPROPERTY(Category=Replication, EditDefaultsOnly, BlueprintReadOnly)
	uint8 bOnlyRelevantToOwner:1;


	UPROPERTY(ReplicatedUsing=OnRep_Owner)
	TObjectPtr<AActor> Owner;

	/** If actor has valid Owner, call Owner's IsNetRelevantFor and GetNetPriority */
	UPROPERTY(Category=Replication, EditDefaultsOnly, BlueprintReadWrite)
	uint8 bNetUseOwnerRelevancy:1;

	/** How often (per second) this actor will be considered for replication, used to determine NetUpdateTime */
	UPROPERTY(Category=Replication, EditDefaultsOnly, BlueprintReadWrite)
	float NetUpdateFrequency;

	/** Used to determine what rate to throttle down to when replicated properties are changing infrequently */
	UPROPERTY(Category=Replication, EditDefaultsOnly, BlueprintReadWrite)
	float MinNetUpdateFrequency;

	/** Priority for this actor when checking for replication in a low bandwidth or saturated situation, higher priority means it is more likely to replicate */
	UPROPERTY(Category=Replication, EditDefaultsOnly, BlueprintReadWrite)
	float NetPriority;



	/** Return the owning UPlayer (if any) of this actor. This will be a local player, a net connection, or nullptr. */
	virtual class UPlayer* GetNetOwningPlayer()
	{
		// We can only replicate RPCs to the owning player
		if (GetLocalRole() == ROLE_Authority)
		{
			if (Owner)
			{
				return Owner->GetNetOwningPlayer();
			}
		}
		return nullptr;
	}

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
	{
		// ALWAYS RELEVANT TO OWNER
		if (bAlwaysRelevant || IsOwnedBy(ViewTarget) || IsOwnedBy(RealViewer) || this == ViewTarget || ViewTarget == GetInstigator())
		{
			return true;
		}
		else if (bNetUseOwnerRelevancy && Owner)
		{
			return Owner->IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
		}
		else if (bOnlyRelevantToOwner)
		{
			return false;
		}
		else if(IsHidden() && (!RootComponent || !RootComponent->IsCollisionEnabled()))
		{
			return false;
		}

		return IsWithinNetRelevancyDistance(SrcLocation);
	}

	bool IsWithinNetRelevancyDistance(const FVector& SrcLocation) const
	{
		return FVector::DistSquared(SrcLocation, GetActorLocation()) < NetCullDistanceSquared;
	}
};
