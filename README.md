# P2PMessagingService

Developed with Visual Studio 2022 (toolset **142**)

P2PMessagingService.sln availabe containing 3 projects producing executables:
* P2PService (C++14 console application)
* P2PNativeClientA (C++14 console application)
* P2PManagedClientB (.NET 5.0)

Each project have its own unit test project beside (Project.Tests)

ZMQ / NetMQ middleware is used as messaging layer 
https://zeromq.org/

Shortcuts for test purpose:
* only ***DEBUG / x64*** configuration is supported
* only one test class per test project, would be better to create one classe per tested class Class.Tests.cpp