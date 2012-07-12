#include "StdAfx.h"
#include "Interface.h"
#include "ManagedWifiContext.h"
using namespace System::Collections::Generic;

namespace ManagedWifi{

	Interface::InterfaceState Interface::State::get(){
		return _state;
	}

	String ^ Interface::Description::get(){
		return _description;
	}

	System::Guid Interface::Guid::get(){
		return _guid;
	}

	Interface::Interface(String ^ description, System::Guid guid, InterfaceState state )
	{
		_description=description;
		_guid=guid;
		_state=state;
	}

	ReadOnlyCollection<Network^> ^ Interface::Networks::get(){
		if(this->Context->IsAlive){

			ManagedWifiContext ^ Context =(ManagedWifiContext ^) this->Context->Target;

			if(Context->IsDisposed->Equals(false)){
				IList<Network ^> ^ networks = ((ManagedWifiContext ^)(this->Context->Target))->GetAvailableNetworks(this);
				return gcnew ReadOnlyCollection<Network^>(networks);
			}
		}
		
		throw gcnew ObjectDisposedException("Parent ManagedWifiContext was disposed");		
	}
}