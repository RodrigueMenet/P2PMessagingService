# P2PMessagingService

## INTRODUCTION

Developed with Visual Studio 2022 (toolset **142**, then VS2019 is enough to build)

P2PMessagingService.sln availabe containing 2 projects producing executables:
* P2PService (C++14 console application)
* P2PUIClient (C++14 MFC application)

Each project have its own unit test project beside (Project.Tests)

Beside that a dummy project have been added, just to be able to debug two instances of the client from the same visual studio instance.

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

## HOW TO BUILD

* Open the P2PMessagingService.sln
* Select Debug / x64 configuration
* Build the whole solution
* You shall find 4 executables, under x64/debug folder
	* P2PService.exe
	* P2PUIClient.exe
	* P2PService.Test.exe
	* P2PUIClient.Test.exe


## HOW TO TEST

You can start:
* either unit tests by launching ./_unit_tests.cmd
* Or you can start manual tests by launching the ./_tests.cmd


## OPEN QUESTIONS

● What are the limitations of this solution? Are there cases where your service will not work?
	Listed in the "shortcuts for demo purpose" section
	
● Does your system scale? Where is the bottleneck? How many users can it support?
	It can scale up to the current situation sure, I intentionally limited the structure containing Peer IDS to 15, but of course it can be increased, there would be a UI concern regarding Combobox
	I guess there is of course an uppper limitation for a single service, there could be several in that case, and associated redirection

● What is the attack surface on the system? How could you reduce it?
	We can connect to both service and any peer, by only knowing the ipaddress / port, then the attack surface is at its maximum. 
	Could be reduced by at least creating authentification step to the service. Messaging between service and peer would be encrypted to send the authorized key to the peers and peers could be authorized to connect to other peers this way.
	
● Compatibility: which OS/browsers/systems is our service compatible with?
	In this current situation UI is really tightly linked to Windows, because of the MFC UI chosen.
	For logic it would be pretty easy to port as, ZMQ is portable and only std objects have been used.