#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "fakeit.hpp"
#include "P2PService.h"

TEST_CASE("P2PService")
{
  SECTION("Service start")
  {
    fakeit::Mock<IReplier> mock_registry;
    fakeit::Mock<IPublisher> mock_notifier;
    P2PService service(mock_registry.get(), mock_notifier.get());

    fakeit::When(Method(mock_registry, Start)).Return();
    fakeit::When(Method(mock_notifier, Start)).Return();

    SECTION("No message have been received")
    {
      fakeit::When(Method(mock_registry, Receive)).AlwaysDo([](int& timeoutMs)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));
        return nullptr;
      });
    }

    CHECK_NOTHROW(service.Start("1.2.3.4"));
    fakeit::Verify(Method(mock_registry, Start)).Once();
    fakeit::Verify(Method(mock_notifier, Start)).Once();

    fakeit::When(Method(mock_registry, Stop)).Return();
    fakeit::When(Method(mock_notifier, Stop)).Return();
    service.Stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    fakeit::Verify(Method(mock_registry, Stop)).Once();
    fakeit::Verify(Method(mock_notifier, Stop)).Once();
  }
}
