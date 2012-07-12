#pragma once

#include "Interface.h"
using namespace System;
using namespace System::Collections::ObjectModel;
namespace ManagedWifi {
	public interface class IManagedWifiContext : IDisposable{
	public:
		virtual property ReadOnlyCollection<Interface^> ^ Interfaces{
			ReadOnlyCollection<Interface^> ^ get();
		}

		virtual property Boolean ^ IsDisposed{

			Boolean ^ get();
		}
	};
}