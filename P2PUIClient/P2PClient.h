#pragma once

#include <map>
#include <vector>
#include <string>

#include "IRequester.h"
#include "ISubscriber.h"
#include "IReplier.h"


struct P2PClient
{
  P2PClient(IRequester& serverRequester, ISubscriber& serverSubscriber, IReplier& peerReplier, uint8_t uid);

  void ConnectToServer() const;

  void AddPeer(int id, const std::shared_ptr<IRequester>& peerRequester);
  void SendMessageToPeer(int id, const std::wstring& msg);
  // @return empty if timeout ; message else
  std::wstring ReceiveMessageFromAnyPeer(int timeoutMs) const;
  // @return empty if timeout ; list of available peer else
  std::vector<int> ReceiveMessageFromServer(int timeoutMs);

  void Stop();

private:
  const uint8_t mUID;
  IRequester& mServerRequester;
  ISubscriber& mServerSubscriber;
  IReplier& mPeerReplier;
  std::map<int, std::shared_ptr<IRequester>> mPeerRequesters;
};
