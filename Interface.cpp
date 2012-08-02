#include "StdAfx.h"
#include "Interface.h"
#include "ManagedWifiContext.h"

using namespace System::Collections::Generic;

namespace ManagedWifi{

	InterfaceState Interface::State::get(){
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

	IEnumerable<INetwork^> ^ Interface::Networks::get(){
		if(this->Context->IsAlive){

			ManagedWifiContext ^ Context =(ManagedWifiContext ^) this->Context->Target;

			if(Context->IsDisposed->Equals(false)){
				IList<INetwork ^> ^ networks = ((ManagedWifiContext ^)(this->Context->Target))->GetAvailableNetworks(this);
				return gcnew List<INetwork^>(networks);
			}
		}
		
		throw gcnew ObjectDisposedException("Parent ManagedWifiContext has been disposed");		
	}
}