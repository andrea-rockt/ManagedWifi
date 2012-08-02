#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Net::NetworkInformation;

namespace ManagedWifi {
	public interface class INetwork{
	public:
		virtual property BSSType Type{BSSType get();};

		virtual property String ^ SSID{String ^ get();};

		virtual property IEnumerable<PhysicalAddress^> ^ BSSIDs{IEnumerable<PhysicalAddress^> ^ get();};

		virtual property ULONG SignalStrength {ULONG get();};
	};
}