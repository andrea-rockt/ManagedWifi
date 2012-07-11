using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ManagedWifi;

namespace ManagedWifiTest
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var context = new ManagedWifiContext(ManagedWifiContext.NWlanVersion.WindowsXP))
            {
                var a = context.IsDisposed;

                foreach (var iface in context.Interfaces)
                {
                        Console.WriteLine("Interface:");
                        Console.WriteLine("\tDescription: {0}",iface.Description);
                        Console.WriteLine("\tState: {0}",iface.State.ToString());
                        Console.WriteLine("\tGUID: {0}",iface.Guid.ToString());
                }
            }
        }
    }
}
