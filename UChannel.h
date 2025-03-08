


/**
 * Base class of communication channels.
 */
UCLASS(abstract, transient)
class ENGINE_API UChannel
	: public UObject
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY()
	TObjectPtr<class UNetConnection>	Connection;		// Owner connection.

	void SetChannelActor(AActor* InActor, ESetChannelActorFlags Flags)
	{
		Actor = InActor;

		if (Actor)
		{
			// Add to map.
			Connection->AddActorChannel(Actor, this);
		}
	}

};

/*
 * A channel for exchanging actor and its subobject's properties and RPCs.
 * ActorChannel manages the creation and lifetime of a replicated actor. 
 * Actual replication of properties and RPCs actually happens in FObjectReplicator now (see DataReplication.h).
 */
class ENGINE_API UActorChannel : public UChannel
{
	TMap<UObject*, TSharedRef<FObjectReplicator>> ReplicationMap;
};

/**
 * A channel for exchanging connection control messages.
 */
class ENGINE_API UControlChannel : public UChannel 
{

};

class ENGINE_API UVoiceChannel : public UChannel
{

};

class ENGINE_API UDataStreamChannel final : public UChannel
{

};