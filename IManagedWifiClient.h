#pragma once

#include "Interface.h"
using namespace System;
using namespace System::Collections::ObjectModel;
namespace ManagedWifi {
	public interface class IManagedWifiClient : IDisposable{
	public:
		virtual property ReadOnlyCollection<Interface^> ^ Interfaces{
			ReadOnlyCollection<Interface^> ^ get();
		}

		virtual bool Scan();
	};
}