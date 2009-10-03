// Copyright (c) 2009 The Chromium Authors. All rights reserved.  Use of this
// source code is governed by a BSD-style license that can be found in the
// LICENSE file.

#ifndef WEBCLIPBOARD_IMPL_H_
#define WEBCLIPBOARD_IMPL_H_

#include "app/clipboard/clipboard.h"
#include "webkit/api/public/WebClipboard.h"

#include <string>

namespace webkit_glue {

class WebClipboardImpl : public WebKit::WebClipboard {
 public:
  static std::string URLToMarkup(const WebKit::WebURL& url,
      const WebKit::WebString& title);
  static std::string URLToImageMarkup(const WebKit::WebURL& url,
      const WebKit::WebString& title);

  virtual ~WebClipboardImpl() {}

  // WebClipboard methods:
  virtual bool isFormatAvailable(Format, Buffer);
  virtual WebKit::WebString readPlainText(Buffer);
  virtual WebKit::WebString readHTML(Buffer, WebKit::WebURL* source_url);
  virtual void writeHTML(
      const WebKit::WebString& html_text,
      const WebKit::WebURL& source_url,
      const WebKit::WebString& plain_text,
      bool write_smart_paste);
  virtual void writePlainText(const WebKit::WebString& plain_text);
  virtual void writeURL(
      const WebKit::WebURL&,
      const WebKit::WebString& title);
  virtual void writeImage(
      const WebKit::WebImage&,
      const WebKit::WebURL& source_url,
      const WebKit::WebString& title);

 private:
  bool ConvertBufferType(Buffer, Clipboard::Buffer*);
};

}  // namespace webkit_glue

#endif  // WEBCLIPBOARD_IMPL_H_
