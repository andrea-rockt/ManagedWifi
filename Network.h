#pragma once

#include "BSSType.h"
#include "INetwork.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Net::NetworkInformation;

namespace ManagedWifi{
	public ref class Network : INetwork
	{
	public:
		virtual property BSSType Type{BSSType get();};

		virtual property String ^ SSID{String ^ get();};

		virtual property IEnumerable<PhysicalAddress^> ^ BSSIDs{IEnumerable<PhysicalAddress^> ^ get();};

		virtual property ULONG SignalStrength {ULONG get();};
		
		Network(BSSType type, String ^ ssid, IList<PhysicalAddress^> ^ bssids, ULONG signal_strength);

	private:
		initonly BSSType _type;
		initonly String ^ _ssid;
		initonly IList<PhysicalAddress^>^ _bssids;
		initonly ULONG _signalStrength;
	};
}
