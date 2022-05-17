// P2PServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "P2PService.h"
#include "ZmqFactory.h"


int main()
{
  ZmqFactory factory;
  const auto replier = factory.BuildReplier(BuildServerCompleteUrl(false));
  const auto publisher = factory.BuildPublisher(BuildServerCompleteUrl(true));
  P2PService service(*replier, *publisher);
  service.Start();
  service.WaitForShutDown();
  service.Stop();
}
