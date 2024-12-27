
typedef TMap<TWeakObjectPtr<AActor>, UActorChannel*, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<AActor>, UActorChannel*>> FActorChannelMap;


class UNetConnection : public UPlayer
{
	/** Owning net driver */
	UPROPERTY()
	TObjectPtr<class UNetDriver> Driver;	

	/** Reference to controlling actor (usually PlayerController) */
	UPROPERTY()
	TObjectPtr<class AActor> OwningActor;

	UPROPERTY()
	TArray<TObjectPtr<class UChannel>> OpenChannels;

	TArray<UChannel*>	Channels;

	FActorChannelMap ActorChannels;

	FActorChannelMap ActorChannels;
	TMap<int32, FNetworkGUID> IgnoringChannels;

	/** Set of channels we may need to ignore when processing a delta checkpoint */
	TSet<int32> IgnoredBunchChannels;
	
	/** Set of channel index values to reserve so GetFreeChannelIndex won't use them */
	TSet<int32> ReservedChannels;

	void AddActorChannel(AActor* Actor, UActorChannel* Channel)
	{
		ActorChannels.Add(Actor, Channel);
		if (ReplicationConnectionDriver)
		{
			ReplicationConnectionDriver->NotifyActorChannelAdded(Actor, Channel);
		}
	}

	ENGINE_API UChannel* CreateChannelByName( const FName& ChName, EChannelCreateFlags CreateFlags, int32 ChannelIndex=INDEX_NONE )
	{
		// Create channel.
		UChannel* Channel = Driver->GetOrCreateChannelByName(ChName);
		check(Channel);
		Channel->Init( this, ChIndex, CreateFlags );
		Channels[ChIndex] = Channel;
		OpenChannels.Add(Channel);
	}
};
