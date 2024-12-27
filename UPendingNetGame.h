
class UPendingNetGame :
	public UObject,
	public FNetworkNotify
{
	void InitNetDriver()
	{
		if (GEngine->CreateNamedNetDriver(this, NAME_PendingNetDriver, NAME_GameNetDriver))
		{
			NetDriver = GEngine->FindNamedNetDriver(this, NAME_PendingNetDriver);
		}

		if(NetDriver->InitConnect( this, URL, ConnectionError ))
		{

			UNetConnection* ServerConn = NetDriver->ServerConnection;
		}

		SendInitialJoin();
	}
};
