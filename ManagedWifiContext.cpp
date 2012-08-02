// File DLL principale.

#include "stdafx.h"
#include "Exceptions.h"
#include "ManagedWifiContext.h"
#pragma comment (lib,"wlanapi.lib")

using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace System::Net::NetworkInformation;

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
		Console::WriteLine("Disposed");
		_isDisposed = true;
	}

	ManagedWifiContext::!ManagedWifiContext(){
		if(this->_nwlanHandle==INVALID_HANDLE_VALUE){ 
			//We should do nothing regarding closing the handle or other cleanup
			return;
		}

		WlanCloseHandle( _nwlanHandle, NULL );
	}
	
	IEnumerable<IInterface^> ^ ManagedWifiContext::Interfaces::get(){

		IList<IInterface ^> ^ interfaceList = gcnew List<IInterface ^>();
		
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
				(InterfaceState)interface_info->isState //WlanInterface state
				);

			wlan_interface->Context= gcnew WeakReference(this);
			interfaceList->Add(wlan_interface);
		}

		WlanFreeMemory(interface_info_list);
	
		return gcnew List<IInterface ^>(interfaceList);
	}	

	IList<INetwork ^> ^ ManagedWifiContext::GetAvailableNetworks(Interface^ i){
			List<INetwork ^> ^ networkList = gcnew List<INetwork ^>();

				DWORD result;
				GUID guid = ToGUID(i->Guid);
				PWLAN_AVAILABLE_NETWORK_LIST available_network_list;
				PWLAN_AVAILABLE_NETWORK available_network;

				result = WlanGetAvailableNetworkList(this->_nwlanHandle,
					&guid,
					0, 
					NULL, 
					&available_network_list);

				if(result == ERROR_NDIS_DOT11_POWER_STATE_INVALID){
					throw gcnew WlanApiException("WlanInterface is turned off");
				}else if (result != ERROR_SUCCESS){
					throw gcnew WlanApiException("An error occurred retrieving networks list");
				}

				for(DWORD i =0 ; i<available_network_list->dwNumberOfItems;i++){
					available_network = (WLAN_AVAILABLE_NETWORK *) & available_network_list->Network[i];


					String ^ ssid= Marshal::PtrToStringAnsi((IntPtr)available_network->dot11Ssid.ucSSID,(Int32)available_network->dot11Ssid.uSSIDLength);
					BSSType type = (BSSType)available_network->dot11BssType;
					ULONG signalStrength=available_network->wlanSignalQuality;

					for each (Network ^ n in networkList){
						if(n->SSID->Equals(ssid)){
							goto endloop; //Quickly escape outer loop
						}
					}
					List<PhysicalAddress^>^ bssids = gcnew List<PhysicalAddress^>();

					PWLAN_BSS_LIST bss_list;
					PWLAN_BSS_ENTRY bss_entry;

					result = WlanGetNetworkBssList(this->_nwlanHandle,
						&guid,
						&(available_network->dot11Ssid),
						available_network->dot11BssType,
						available_network->bSecurityEnabled,
						NULL,
						&bss_list);

					if(result == ERROR_NDIS_DOT11_POWER_STATE_INVALID){
						throw gcnew WlanApiException("WlanInterface is turned off");
					}else if (result != ERROR_SUCCESS){
						throw gcnew WlanApiException("An error occurred retrieving networks list");
					}

					for(DWORD j=0; j<bss_list->dwNumberOfItems;j++){
						bss_entry=(PWLAN_BSS_ENTRY) &bss_list->wlanBssEntries[j];

						array<byte> ^ mac_bytes = gcnew array<byte>(6);
						Marshal::Copy((IntPtr)bss_entry->dot11Bssid,mac_bytes,0,6);
						PhysicalAddress ^ mac = gcnew PhysicalAddress(mac_bytes);

						bssids->Add(mac);
					}

					WlanFreeMemory(bss_list);

					INetwork ^ Wlan_Network= gcnew Network(type,ssid,bssids,signalStrength);

					networkList->Add(Wlan_Network);

endloop:			;
				}

				WlanFreeMemory(available_network_list);

				return networkList;
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