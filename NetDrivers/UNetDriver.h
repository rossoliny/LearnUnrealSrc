
USTRUCT()
struct FNetDriverDefinition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FName DefName;

	UPROPERTY()
	FName DriverClassName;

}

// Returns true if this actor should replicate to *any* of the passed in connections
static FORCEINLINE_DEBUGGABLE bool IsActorRelevantToConnection( const AActor* Actor, const TArray<FNetViewer>& ConnectionViewers );


UCLASS (Abstract, CustomConstructor, Transient, MinimalAPI, Config=Engine)  
class UNetDriver : public UObject, public FExec
{
	TArray<TObjectPtr<UNetConnection>> ClientConnections;
	
	TObjectPtr<UNetConnection> ServerConnection;


	virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error);

	virtual bool InitListen(FNetworkNotify* InNotify, FURL& ListenURL, bool bReuseAddressAndPort, FString& Error);


	void UNetDriver::PostInitProperties()
	{
		Super::PostInitProperties();

		// By default we're the game net driver and any child ones must override this
		NetDriverName = NAME_GameNetDriver;
	}

	ENGINE_API virtual bool InitListen(
		class FNetworkNotify* InNotify, 
		FURL& ListenURL, 
		bool bReuseAddressAndPort, 
		FString& Error) PURE_VIRTUAL(UNetDriver::InitListen, return true;);

	UChannel* GetOrCreateChannelByName(const FName& ChName);


	int32 UNetDriver::ServerReplicateActors_ProcessPrioritizedActors(
		UNetConnection* Connection,
		const TArray<FNetViewer>& ConnectionViewers, 
		FActorPriority** PriorityActors, 
		const int32 FinalSortedCount, 
		int32& OutUpdated )
	{
		UActorChannel* Channel = PriorityActors[j]->Channel;
		if ( !Channel || Channel->Actor ) //make sure didn't just close this channel
		{
			AActor* Actor = ActorInfo->Actor;
			if ( IsActorRelevantToConnection( Actor, ConnectionViewers ) )
			{
				// Create UActorChannel for AActor
				if (Channel == NULL)
				{
					// Create a new channel for this actor.
					Channel = Connection->CreateChannelByName(NAME_Actor);
					if (Channel)
					{
						Channel->SetChannelActor(Actor, ESetChannelActorFlags::None);
					}
				}
			}

			Channel->ReplicateActor();

			// If the actor wasn't recently relevant, or if it was torn off, close the actor channel if it exists for this connection
			if (!bIsRecentlyRelevant)
			{
				Channel->Close(Actor->GetTearOff() ? EChannelCloseReason::TearOff : EChannelCloseReason::Relevancy);
			}
		}
		
	};

};


UCLASS(transient, config = Engine)
class WEBSOCKETNETWORKING_API UWebSocketNetDriver : public UNetDriver
{

};


UCLASS(transient, config=Engine)
class ONLINESUBSYSTEMUTILS_API UIpNetDriver : public UNetDriver
{

};

UCLASS(transient, config=Engine)
class ENGINE_API UDemoNetDriver : public UNetDriver
{

};