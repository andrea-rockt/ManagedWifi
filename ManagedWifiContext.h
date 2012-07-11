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
		enum class NWlanVersion{
					WindowsXP=1, 
					WindowsVista=2
				};

		ManagedWifiContext(ManagedWifiContext::NWlanVersion  requiredClientVersion);
		
		~ManagedWifiContext();
		
		virtual property ReadOnlyCollection<Interface^> ^ Interfaces{
			ReadOnlyCollection<Interface^> ^ get(void);
		};

		property bool IsDisposed{
			bool get();
		};

	private:
		bool _isDisposed;
		HANDLE _nwlanHandle;
		DWORD _obtainedVersion;
		Guid ManagedWifiContext::FromGUID( _GUID& guid );
		_GUID ManagedWifiContext::ToGUID( Guid& guid );
	protected:
		!ManagedWifiContext();
		// TODO: aggiungere qui i metodi per la classe.

	internal:
		IList<Network ^> ^ GetAvailableNetworks(Interface^ i);
	};
}
