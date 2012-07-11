#pragma once

#include"Network.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace ManagedWifi{
	ref class Interface
	{
	public:
		///<summary> Enum describing possible states of a wireless interface </summary>
		enum class InterfaceState{
			NotReady = 0,
			Connected = 1,
			AdHocNetworkFormed = 2,
			Disconnecting = 3,
			Disconnected = 4,
			Associating = 5,
			Discovering = 6,
			Authenticating = 7 
		};

		///<summary>Current state of the interface</summary>
		///<seealso cref="InterfaceState"/>
		property InterfaceState State{InterfaceState get();};

		///<summary>Interface description</summary>
		property String ^ Description{String ^ get();};

		///<summary>Interface guid </summary>
		property System::Guid Guid{System::Guid get();};

		property ReadOnlyCollection<Network^> ^ Networks{
			ReadOnlyCollection<Network^> ^ get();
		}


		Interface(String ^ description, System::Guid guid, InterfaceState state);

	internal:
		WeakReference ^ Context;

	private:
		initonly String ^ _description;
		initonly System::Guid _guid;
		initonly InterfaceState _state;
	};
}