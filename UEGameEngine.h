
class UNetConnection : public UPlayer
{
	
};

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

USTRUCT()
struct FNetDriverDefinition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FName DefName;

	UPROPERTY()
	FName DriverClassName;

}

class UGameEngine : public UEngine 
{
	UPROPERTY(Config, transient)
	TArray<FNetDriverDefinition> NetDriverDefinitions;

	UPROPERTY(transient)
	TArray<FNamedNetDriver> ActiveNetDrivers;



	UNetDriver* CreateNetDriver_Local(UEngine* Engine, FWorldContext& Context, FName NetDriverDefinition, FName InNetDriverName)
	{
		UNetDriver* ReturnVal;

		Definition = Engine->NetDriverDefinitions.FindByPredicate(FindNetDriverDefPred);

		new(Context.ActiveNetDrivers) FNamedNetDriver(ReturnVal, Definition);

		return ReturnVal;
	};
};



