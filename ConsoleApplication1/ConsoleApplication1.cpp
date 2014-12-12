// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//########################################
//
//
//Here is my client C++ code:
//########################################

#define _ATL_ATTRIBUTES 1
#include <atlbase.h>
#include <atlcom.h>
#include <stdio.h>

//#include "C:\Users\Ella\Documents\visual studio 2015\Projects\ComLibrary\ConsoleApplication1\Debug\comlibrary.tlh"
#import "..\ComLibrary\bin\Debug\ComLibrary.tlb" raw_interfaces_only, named_guids, embedded_idl 
using namespace ComLibrary;


[module(exe, name = "EventReceiver")];

[event_receiver(com)]
class CReceiver
{
public:
	HRESULT MyHandler1(long nValue)
	{
		printf("MyHandler1 was called with value %d.\n", nValue);
		return S_OK;
	}

	HRESULT MyHandler2(long nValue)
	{
		printf("MyHandler2 was called with value %d.\n", nValue);
		return S_OK;
	}

	void HookEvent(IEventSource* pSource)
	{
		__hook(&IEvents::MyEvent, pSource, &CReceiver::MyHandler1);
		__hook(&IEvents::MyEvent, pSource, &CReceiver::MyHandler2);
	}

	void UnhookEvent(IEventSource* pSource)
	{
		__unhook(&IEvents::MyEvent, pSource, &CReceiver::MyHandler1);
		__unhook(&IEvents::MyEvent, pSource, &CReceiver::MyHandler2);
	}
};

int main()
{
	CoInitialize(NULL);
	IEventSourcePtr pSource = nullptr;
	try
	{
		 pSource = IEventSourcePtr(CLSID_CSource);
	}
	catch(...)
	{
		return -1;
	}

	// Create receiver and fire event
	CReceiver receiver;
	receiver.HookEvent(pSource);
	pSource->FireEvent();
	receiver.UnhookEvent(pSource);
	CoUninitialize();
	getchar();
	return 0;
}

