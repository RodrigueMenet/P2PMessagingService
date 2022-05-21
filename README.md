# P2PMessagingService

#
# INTRODUCTION
#


Developed with Visual Studio 2022 (toolset **142**, then VS2019 is enough to build)

P2PMessagingService.sln availabe containing 2 projects producing executables:
* P2PService (C++14 console application)
* P2PUIClient (C++14 console application)

Each project have its own unit test project beside (Project.Tests)

ZMQ middleware is used as messaging layer 
https://zeromq.org/

Shortcuts for demo purpose:
* only ***DEBUG / x64*** configuration is supported
* only one test class per test project, would be better to create one classe per tested class Class.Tests.cpp
* everything has been done locally (127.0.0.1 ip adress used)
* plain structures have been used ; any serialization would bring a lot more flexibility (e.g. JSON)
* no namespace used
* Zmq classes are not unit tested, only Service and Client aspect (assuming they are delivered as a third party)
* No ServiceStarter (on server side) created, would be cleaner to do so (here P2PService class, start async task, would be the purpose of the ServiceStarter not to hide this from Service Class Perspective and tests)
* Error or Empty Answer are not well managed
* No log system
* Would be better to use std::chrono (or homemade class overriding std::chrono ; e.g. stdx::chrono) instead of timeoutMs everywhere ; to bring more flexibility about units usage
* exceptions handling can be a lot improved
* parameter handling in client execution ; to be improved (to be replaced by a real GUID)
* no hearbeat management (to detect client disappearing -> updating the peer lists)

#
# HOW TO BUILD
#

> Open the P2PMessagingService.sln
> Select Debug / x64 configuration
> Build the whole solution
> You shall find 4 executables, under x64/debug folder
	* P2PService.exe
	* P2PUIClient.exe
	* P2PService.Test.exe
	* P2PUIClient.Test.exe


#
# HOW TO TEST
#

You can start:
* either unit tests by launching _unit_tests.cmd
* Or you can start manual tests by launching the _tests.cmd


