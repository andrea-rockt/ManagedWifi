#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Net::NetworkInformation;

namespace ManagedWifi{
	public ref class Network
	{
	public:
		enum class BSSType{
			Infrastructure=1,
			Independent=2,
			Any=3
		};


		property BSSType Type{BSSType get();};

		property String ^ SSID{String ^ get();};

		property ReadOnlyCollection<PhysicalAddress^> ^ BSSIDs{ReadOnlyCollection<PhysicalAddress^> ^ get();};

		property ULONG SignalStrength {ULONG get();};
		
		Network(BSSType type, String ^ ssid, IList<PhysicalAddress^> ^ bssids, ULONG signal_strength);

	private:
		initonly BSSType _type;
		initonly String ^ _ssid;
		initonly IList<PhysicalAddress^>^ _bssids;
		initonly ULONG _signalStrength;
	};
}
