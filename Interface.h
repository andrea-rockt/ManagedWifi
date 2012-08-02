#pragma once

#include"Network.h"
#include"IInterface.h"
#include"InterfaceState.h"

using namespace System;
using namespace System::Collections::Generic;

namespace ManagedWifi{
		///<summary> Enum describing possible states of a wireless interface </summary>
	

	public ref class Interface : IInterface
	{
	public:
	
		///<summary>Current state of the interface</summary>
		///<seealso cref="InterfaceState"/>
		virtual property  InterfaceState State{InterfaceState get();};

		///<summary>Interface description</summary>
		virtual property  String ^ Description{String ^ get();};

		///<summary>Interface guid </summary>
		virtual property System::Guid Guid{System::Guid get();};

		virtual property IEnumerable<INetwork^> ^ Networks{
			IEnumerable<INetwork^> ^ get();
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