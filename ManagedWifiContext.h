// ManagedWifi.h
#pragma once
#include"IManagedWifiContext.h"
#include "Interface.h"
#include "Network.h"

using namespace System;
using namespace System::Collections::Generic;


namespace ManagedWifi {

	public ref class ManagedWifiContext : public IManagedWifiContext
	{
	public:
		ManagedWifiContext();
		
		~ManagedWifiContext();
		
		virtual property ReadOnlyCollection<Interface^> ^ Interfaces{
			ReadOnlyCollection<Interface^> ^ get(void);
		};

		virtual bool Scan();

		property bool IsDisposed{
			bool get();
		};

	private:
		bool _isDisposed;

	protected:
		!ManagedWifiContext();
		// TODO: aggiungere qui i metodi per la classe.

	internal:
		IList<Network ^> ^ GetAvailableNetworks(Interface^ i);
	};
}
