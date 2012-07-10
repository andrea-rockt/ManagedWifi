// File DLL principale.

#include "stdafx.h"
#include "ManagedWifiClient.h"

using namespace System::Collections::Generic;

namespace ManagedWifi {
	
	ManagedWifiClient::ManagedWifiClient(){
	}
	
	ManagedWifiClient::~ManagedWifiClient(){
	}
	
	ManagedWifiClient::!ManagedWifiClient(){
	}

	ReadOnlyCollection<Interface^> ^ ManagedWifiClient::Interfaces::get(){
		return nullptr;
	}

	IList<Network ^> ^ GetAvailableNetworks(Interface^ i){
		return nullptr;
	}
}