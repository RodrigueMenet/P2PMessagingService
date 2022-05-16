#pragma once

#include <string>
#include <vector>
#include <list>

#include "IRequester.h"
#include "ISubscriber.h"
#include "IReplier.h"


struct P2PClient
{
  P2PClient(IRequester& serverRequester, ISubscriber& serverSubscriber, IReplier & peerReplier);

  void AddPeer(int id, const std::shared_ptr<IRequester>& peerRequester);
  void SendMessageToPeer(int id, const std::wstring& msg);
  // @return empty if timeout ; message else
  std::wstring ReceiveMessageFromAnyPeer(int timeoutMs) const;
  // @return empty if timeout ; list of available peer else
  std::list<int> ReceiveMessageFromServer(int timeoutMs);

private:
  IRequester& mServerRequester;
  ISubscriber& mServerSubscriber;
  IReplier& mPeerReplier;  
  std::vector<std::shared_ptr<IRequester>> mPeerRequesters;
};
