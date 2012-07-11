// File DLL principale.

#include "stdafx.h"
#include "Exceptions.h"
#include "ManagedWifiContext.h"
#pragma comment (lib,"wlanapi.lib")

using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace ManagedWifi {

	ManagedWifiContext::ManagedWifiContext(ManagedWifiContext::NWlanVersion  requiredClientVersion){
		_isDisposed=false;
		DWORD result = 0;
		DWORD negotiated_version;
		HANDLE nwlan_handle;

		this->_nwlanHandle=INVALID_HANDLE_VALUE;

		result = WlanOpenHandle((DWORD)requiredClientVersion, NULL, &negotiated_version, &nwlan_handle);

		if(result==ERROR_SUCCESS){
			this->_nwlanHandle=nwlan_handle;
		}else{
			throw gcnew WlanApiInitException("An error occurred initializing native wlan subsystem");
		}

		this->_obtainedVersion=negotiated_version;
	}

	ManagedWifiContext::~ManagedWifiContext(){
		if (_isDisposed)
			return;

		this->!ManagedWifiContext();
		_isDisposed = true;
	}

	ManagedWifiContext::!ManagedWifiContext(){
		if(this->_nwlanHandle==INVALID_HANDLE_VALUE){ 
			//We should do nothing regarding closing the handle or other cleanup
			return;
		}

		WlanCloseHandle( _nwlanHandle, NULL );
	}

	ReadOnlyCollection<Interface^> ^ ManagedWifiContext::Interfaces::get(){

		IList<Interface ^> ^ interfaceList = gcnew List<Interface ^>();

		PWLAN_INTERFACE_INFO_LIST interface_info_list;
		PWLAN_INTERFACE_INFO interface_info;
		DWORD result;

		result = WlanEnumInterfaces(this->_nwlanHandle, NULL, &interface_info_list); 

		if (result != ERROR_SUCCESS)  {
			throw gcnew WlanApiException("Unable to enumerate interfaces");
		}

		for(DWORD i =0;i<interface_info_list->dwNumberOfItems;i++){
			interface_info = (WLAN_INTERFACE_INFO *) &interface_info_list->InterfaceInfo[i];
			Interface ^ wlan_interface = gcnew Interface(
				Marshal::PtrToStringAuto((IntPtr)interface_info->strInterfaceDescription), // Description String
				FromGUID(interface_info->InterfaceGuid), //WlanInterface Guid
				(Interface::InterfaceState)interface_info->isState //WlanInterface state
				);

			wlan_interface->Context= gcnew WeakReference(this);
			interfaceList->Add(wlan_interface);
		}

		WlanFreeMemory(interface_info_list);

		return gcnew ReadOnlyCollection<Interface ^>(interfaceList);
	}

	bool ManagedWifiContext::IsDisposed::get(){
		return _isDisposed;
	}

	IList<Network ^> ^ ManagedWifiContext::GetAvailableNetworks(Interface^ i){
		return nullptr;
	}

	Guid ManagedWifiContext::FromGUID( _GUID& guid ) {
		return Guid( guid.Data1, guid.Data2, guid.Data3, 
			guid.Data4[ 0 ], guid.Data4[ 1 ], 
			guid.Data4[ 2 ], guid.Data4[ 3 ], 
			guid.Data4[ 4 ], guid.Data4[ 5 ], 
			guid.Data4[ 6 ], guid.Data4[ 7 ] );
	}

	_GUID ManagedWifiContext::ToGUID( Guid& guid ) {
		array<Byte>^ guidData = guid.ToByteArray();
		pin_ptr<Byte> data = &(guidData[ 0 ]);

		return *(_GUID *)data;
	}
}