# P2PMessagingService

Developed with Visual Studio 2022

P2PMessagingService.sln availabe containing 3 projects producing executables:
* P2PService (C++14 console application)
* P2PNativeClientA (C++14 console application)
* P2PManagedClientB (.NET ??)

Each project have its own unit test project beside (Project.Tests)

ZMQ / NetMQ middleware is used as messaging layer https://zeromq.org/
rappidjson is used as serializer layer for native side https://rapidjson.org/
