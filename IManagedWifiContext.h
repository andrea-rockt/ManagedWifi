#pragma once
#include "Interface.h"

using namespace System;
using namespace System::Collections::Generic;

namespace ManagedWifi {
	public interface class IManagedWifiContext{
	public:
		virtual property IEnumerable<IInterface^> ^ Interfaces{
			IEnumerable<IInterface^> ^ get();
		}

		virtual IEnumerable<INetwork ^> ^ GetAvailableNetworks(IInterface ^ wlan_interface);	

	};
}