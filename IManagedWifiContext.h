#pragma once
#include "Interface.h"

using namespace System;
using namespace System::Collections::Generic;
namespace ManagedWifi {
	public interface class IManagedWifiContext:IDisposable{
	public:
		virtual property IEnumerable<IInterface^> ^ Interfaces{
			IEnumerable<IInterface^> ^ get();
		}

		IEnumerable<INetwork ^> ^ GetAvailableNetworks(IInterface ^ wlan_interface);	

		virtual property Boolean ^ IsDisposed{

			Boolean ^ get();
		}
	};
}