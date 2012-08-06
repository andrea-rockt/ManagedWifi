#pragma once
#include "InterfaceState.h"
#include "INetwork.h"

using namespace System;
using namespace System::Collections::Generic;

namespace ManagedWifi {
	public interface class IInterface{
	public:
		virtual property String ^ Description{String ^ get();}

		virtual property InterfaceState State{InterfaceState get();}
	
		virtual property System::Guid Guid{System::Guid get();}
	};
}