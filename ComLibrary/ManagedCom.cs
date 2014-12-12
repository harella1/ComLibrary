using System;
using System.Runtime.InteropServices;



namespace CSlib
{
    public delegate void EventDelegate(int val);

    [ComVisible(true)]
    [Guid("EAA4976A-45C3-4BC5-BC0B-E474F4C3C83F")]
   public interface IEventSource
    {
        void FireEvent();
    }

    [ComVisible(true)]
    [Guid("7BD20046-DF8C-44A6-8F6B-687FAA26FA71"),
    InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IEvents
    {
        void MyEvent(int val);
    }


    [ComVisible(true)]
    [Guid("0D53A3E8-E51A-49C7-944E-E72A2064F938"),
    ClassInterface(ClassInterfaceType.None),
    ComSourceInterfaces(typeof(IEvents))]
    public class CSource : IEventSource
    {
        public event EventDelegate MyEvent;


        public void FireEvent()
        {
            Console.WriteLine("CauseClickEvent called");
            MyEvent(123);
        }
    }
}

