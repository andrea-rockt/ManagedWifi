// ManagedWifi.h
#pragma once
#include"IManagedWifiContext.h"
#include "Interface.h"
#include "Network.h"

using namespace System;
using namespace System::Collections::Generic;


namespace ManagedWifi {

	public ref class ManagedWifiContext : IManagedWifiContext
	{

	public:
		enum class NWlanVersion{
					WindowsXP=1, 
					WindowsVista=2
				};

		ManagedWifiContext(ManagedWifiContext::NWlanVersion  requiredClientVersion);
		
		~ManagedWifiContext();
		
		virtual property IEnumerable<IInterface^> ^ Interfaces {
			IEnumerable<IInterface^> ^ get();
		};

		virtual property Boolean ^ IsDisposed{
			Boolean ^ get(){
				return gcnew Boolean(_isDisposed);
			};
		};
		
		virtual IEnumerable<INetwork ^> ^ GetAvailableNetworks(IInterface ^ wlan_interface);	

	private:
		bool _isDisposed;
		HANDLE _nwlanHandle;
		DWORD _obtainedVersion;
		Guid ManagedWifiContext::FromGUID( _GUID& guid );
		_GUID ManagedWifiContext::ToGUID( Guid& guid );
	protected:
		!ManagedWifiContext();
		// TODO: aggiungere qui i metodi per la classe.
	};
}
