// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_CHROME_COOKIE_NOTIFICATION_DETAILS_H_
#define CHROME_BROWSER_NET_CHROME_COOKIE_NOTIFICATION_DETAILS_H_

#include "net/base/cookie_monster.h"

struct ChromeCookieDetails {
 public:
  ChromeCookieDetails(net::CookieMonster::CookieListPair* cookie_pair_copy,
                      bool is_removed)
      : cookie_pair(cookie_pair_copy),
        removed(is_removed) {
  }

  net::CookieMonster::CookieListPair* cookie_pair;
  bool removed;
};

#endif  // CHROME_BROWSER_NET_CHROME_COOKIE_NOTIFICATION_DETAILS_H_
