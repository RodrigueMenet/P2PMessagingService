#include "pch.h"

#include "P2PClient.h"

#include <iostream>

#include "SimpleMessage.h"
#include "thread"


P2PClient::P2PClient(IRequester& serverRequester, ISubscriber& serverSubscriber, IReplier& peerReplier, uint8_t UID)
  : mServerRequester(serverRequester)
    , mServerSubscriber(serverSubscriber)
    , mPeerReplier(peerReplier)
    , mUID(UID)
{
  
}


void P2PClient::Start() const
{
  mServerSubscriber.Start();
  mServerRequester.Start();
  mPeerReplier.Start();

  std::thread([this]
  {
    // wait for subscriber to be fully connected before registering
    std::this_thread::sleep_for(std::chrono::seconds(5));
    mServerRequester.Request(PayloadMessage<PeerRegisterPayload>(MessageType::PeerRegister, {mUID}));

  }).detach();
}


void P2PClient::AddPeer(int id, const std::shared_ptr<IRequester>& peerRequester)
{
  mPeerRequesters[id] = peerRequester;
}


void P2PClient::SendMessageToPeer(int id, const std::wstring& msg)
{
  try
  {
    PeerDisplayMessage payload;
    msg.copy(payload.Message, min(msg.size(), MAX_MESSAGE_SIZE));
    mPeerRequesters.at(id)->Request(PayloadMessage<PeerDisplayMessage>(MessageType::PeerMessage, payload));
  }
  catch(const std::exception& ex)
  {
    std::cerr << __FUNCTION__ << " Error sending message ( " << msg.c_str() << " to peer " << id << " (err : " << ex.what() << ")" << std::endl;
  }
}


std::wstring P2PClient::ReceiveMessageFromAnyPeer(int timeoutMs) const
{
  const auto msg = mPeerReplier.Receive(timeoutMs);

  if(msg)
  {
    const auto payload = msg->SpecificPayload<PeerDisplayMessage>();
    return std::wstring(payload->Message, wcslen(payload->Message));
  }
  return L"";
}


std::vector<int> P2PClient::ReceiveMessageFromServer(int timeoutMs)
{
  const auto msg = mServerSubscriber.Receive(timeoutMs);

  if(msg)
  {
    std::vector<int> ret;
    const auto payload = msg->SpecificPayload<PeersAvailablePayload>();
    for(auto i = 0; i < MAX_CLIENT_NUMBER && payload->UIDs[i] != 0; ++i)
    {
      ret.push_back(payload->UIDs[i]);
    }
    return ret;
  }

  return {};
}


void P2PClient::Stop()
{
  mServerRequester.Stop();
  mServerSubscriber.Stop();
  mPeerReplier.Stop();
  for(const auto& peer : mPeerRequesters)
  {
    peer.second->Stop();
  }
}
