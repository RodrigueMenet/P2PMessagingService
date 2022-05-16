
#include "pch.h"

#include "P2PClient.h"

#include <iostream>

#include "SimpleMessage.h"


P2PClient::P2PClient(IRequester& serverRequester, ISubscriber& serverSubscriber, IReplier& peerReplier)
  : mServerRequester(serverRequester)
  , mServerSubscriber(serverSubscriber)
  , mPeerReplier(peerReplier)
{
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
  catch (const std::exception & ex)
  {
    std::cerr << __FUNCTION__ << " Error sending message ( " << msg.c_str() << " to peer " << id << " (err : " << ex.what() << ")" << std::endl;
  }
}


std::wstring P2PClient::ReceiveMessageFromAnyPeer(int timeoutMs) const
{
  const auto msg = mPeerReplier.Receive(timeoutMs);

  if (msg)
  {
    const auto payload = msg->Payload<PeerDisplayMessage>();
    return std::wstring(payload.Message, wcslen(payload.Message) );
  }
  return L"";
}


std::list<int> P2PClient::ReceiveMessageFromServer(int timeoutMs)
{
  const auto msg = mServerSubscriber.Receive(timeoutMs);

  if (msg)
  {
    std::list<int> ret;
    const auto payload = msg->Payload<PeersAvailablePayload>();
    for (auto i = 0; i < MAX_CLIENT_NUMBER && payload.UIDs[i] != 0; ++i)
    {
      ret.push_back(payload.UIDs[i]);
    }
    return ret;      
  }

  return {};
}
