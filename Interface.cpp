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
}