#pragma once
using namespace System;

namespace ManagedWifi{

	///<summary>Exception throwed by ManagedWifiContext ctor when native wlan interface init fails</summary>
	[Serializable]
	public ref class WlanApiInitException : public Exception
	{
	public:
		WlanApiInitException() : Exception() {}
		WlanApiInitException(String^ message) : Exception(message) {}
		WlanApiInitException(String^ message, Exception^ inner) : Exception(message, inner) {}
	protected:
		WlanApiInitException(System::Runtime::Serialization::SerializationInfo^ info, System::Runtime::Serialization::StreamingContext context) : Exception(info, context) {}
	};

	//<summary>Exception throwed by ManagedWifiContext ctor when native wlan interface init fails</summary>
	[Serializable]
	public ref class WlanApiException : public Exception
	{
	public:
		WlanApiException() : Exception() {}
		WlanApiException(String^ message) : Exception(message) {}
		WlanApiException(String^ message, Exception^ inner) : Exception(message, inner) {}
	protected:
		WlanApiException(System::Runtime::Serialization::SerializationInfo^ info, System::Runtime::Serialization::StreamingContext context) : Exception(info, context) {}
	};

}
