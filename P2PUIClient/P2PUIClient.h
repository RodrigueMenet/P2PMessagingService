
// P2PUIClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CP2PUIClientApp:
// See P2PUIClient.cpp for the implementation of this class
//

class CP2PUIClientApp : public CWinApp
{
public:
	CP2PUIClientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CP2PUIClientApp theApp;
