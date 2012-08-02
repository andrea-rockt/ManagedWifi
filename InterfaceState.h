#pragma once

namespace ManagedWifi{
	public enum class InterfaceState{
			NotReady = 0,
			Connected = 1,
			AdHocNetworkFormed = 2,
			Disconnecting = 3,
			Disconnected = 4,
			Associating = 5,
			Discovering = 6,
			Authenticating = 7 
	};
}
