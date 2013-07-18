// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/bind.h"
#include "base/message_loop/message_loop.h"
#include "content/browser/geolocation/win7_location_api_win.h"
#include "content/browser/geolocation/win7_location_provider_win.h"
#include "content/public/common/geoposition.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using testing::_;
using testing::AtLeast;
using testing::DoDefault;
using testing::Invoke;
using testing::Return;

namespace content {

class MockWin7LocationApi : public Win7LocationApi {
 public:
  static MockWin7LocationApi* CreateMock() {
    return new MockWin7LocationApi();
  }

  // Used to signal when the destructor is called.
  MOCK_METHOD0(Die, void());
  // Win7LocationApi
  MOCK_METHOD1(GetPosition, void(Geoposition*));
  MOCK_METHOD1(SetHighAccuracy, bool(bool));

  virtual ~MockWin7LocationApi() {
    Die();
  }

  void GetPositionValid(Geoposition* position) {
    position->latitude = 4.5;
    position->longitude = -34.1;
    position->accuracy = 0.5;
    position->timestamp = base::Time::FromDoubleT(200);
    position->error_code = Geoposition::ERROR_CODE_NONE;
  }
  void GetPositionInvalid(Geoposition* position) {
    position->latitude = 4.5;
    position->longitude = -340000.1;
    position->accuracy = 0.5;
    position->timestamp = base::Time::FromDoubleT(200);
    position->error_code = Geoposition::ERROR_CODE_POSITION_UNAVAILABLE;
  }

 private:
  MockWin7LocationApi() {
    ON_CALL(*this, GetPosition(_))
        .WillByDefault(Invoke(this,
                              &MockWin7LocationApi::GetPositionValid));
    ON_CALL(*this, SetHighAccuracy(true))
        .WillByDefault(Return(true));
    ON_CALL(*this, SetHighAccuracy(false))
        .WillByDefault(Return(false));
  }
};

class LocationProviderListenerLoopQuitter {
 public:
  explicit LocationProviderListenerLoopQuitter(base::MessageLoop* message_loop)
      : message_loop_to_quit_(message_loop) {
    CHECK(message_loop_to_quit_ != NULL);
  }

  void LocationUpdateAvailable(const LocationProvider* provider,
                               const Geoposition& position) {
    EXPECT_EQ(base::MessageLoop::current(), message_loop_to_quit_);
    provider_ = provider;
    message_loop_to_quit_->Quit();
  }

  base::MessageLoop* message_loop_to_quit_;
  const LocationProvider* provider_;
};

class GeolocationProviderWin7Tests : public testing::Test {
 public:
  GeolocationProviderWin7Tests(): location_listener_(&main_message_loop_) {
  }

  virtual void SetUp() {
    api_ = MockWin7LocationApi::CreateMock();
    provider_ = new Win7LocationProvider(api_);
    provider_->SetUpdateCallback(base::Bind(
        &LocationProviderListenerLoopQuitter::LocationUpdateAvailable,
        base::Unretained(&location_listener_)));
  }
  virtual void TearDown() {
    provider_->StopProvider();
    delete provider_;
    main_message_loop_.RunUntilIdle();
  }

 protected:
  Win7LocationProvider* provider() {
    return static_cast<Win7LocationProvider*>(provider_);
  }

  MockWin7LocationApi* api_;
  LocationProviderListenerLoopQuitter location_listener_;
  base::MessageLoop main_message_loop_;
  LocationProvider* provider_;
};

TEST_F(GeolocationProviderWin7Tests, StartStop) {
  EXPECT_CALL(*api_, SetHighAccuracy(true))
      .WillOnce(Return(true));
  EXPECT_TRUE(provider()->StartProvider(true));
  provider()->StopProvider();
  EXPECT_CALL(*api_, SetHighAccuracy(false))
      .WillOnce(Return(true));
  EXPECT_TRUE(provider()->StartProvider(false));
}

TEST_F(GeolocationProviderWin7Tests, GetValidPosition) {
  EXPECT_CALL(*api_, GetPosition(_))
      .Times(AtLeast(1));
  EXPECT_CALL(*api_, SetHighAccuracy(true))
      .WillOnce(Return(true));
  EXPECT_TRUE(provider()->StartProvider(true));
  main_message_loop_.Run();
  Geoposition position;
  provider()->GetPosition(&position);
  EXPECT_TRUE(position.Validate());
}

TEST_F(GeolocationProviderWin7Tests, GetInvalidPosition) {
  EXPECT_CALL(*api_, GetPosition(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Invoke(api_,
      &MockWin7LocationApi::GetPositionInvalid));
  EXPECT_CALL(*api_, SetHighAccuracy(true))
      .WillOnce(Return(true));
  EXPECT_TRUE(provider()->StartProvider(true));
  main_message_loop_.Run();
  Geoposition position;
  provider()->GetPosition(&position);
  EXPECT_FALSE(position.Validate());
}

}  // namespace content
