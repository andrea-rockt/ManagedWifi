#include "StdAfx.h"
#include "Network.h"

namespace ManagedWifi{
	Network::Network(BSSType type, String ^ ssid, IList<PhysicalAddress^> ^ bssids, ULONG signal_strength)
			{
				this->_type=type;
				this->_ssid=ssid;
				this->_bssids=bssids;
				this->_signalStrength=signal_strength;
			}

			Network::BSSType Network::Type::get(){
				return this->_type;
			}

			String ^ Network::SSID::get(){
				return this->_ssid;
			}

			ReadOnlyCollection<PhysicalAddress^> ^ Network::BSSIDs::get(){
				return gcnew ReadOnlyCollection<PhysicalAddress^>(this->_bssids);
			}

			ULONG Network::SignalStrength::get(){
				return this->_signalStrength;
			}
}