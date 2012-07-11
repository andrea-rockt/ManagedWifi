// File DLL principale.

#include "stdafx.h"
#include "ManagedWifiContext.h"

using namespace System::Collections::Generic;

namespace ManagedWifi {
	
	ManagedWifiContext::ManagedWifiContext(){
	}
	
	ManagedWifiContext::~ManagedWifiContext(){
	}
	
	ManagedWifiContext::!ManagedWifiContext(){
	}

	ReadOnlyCollection<Interface^> ^ ManagedWifiContext::Interfaces::get(){
		return nullptr;
	}

	IList<Network ^> ^ ManagedWifiContext::GetAvailableNetworks(Interface^ i){
		return nullptr;
	}
}