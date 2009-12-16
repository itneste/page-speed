/**
 * Copyright 2008-2009 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Author: Bryan McQuade
//
// HttpActivityDistributor distributes events to
// nsIHttpActivityObservers registered via the nsIObserverService. The
// nsIObserverService is a Firefox service that allows publishers to
// communicate with subscribers on string-named topics. There can be
// multiple publishers and subscribers for a given topic. The
// HttpActivityDistributor publishes on the
// 'http-activity-observer' topic.
//
// The events generated by the HttpActivityDistributor describe
// the HTTP activity taking place in Firefox's network
// thread. Registered observers are notified of HTTP activity on the
// main thread.

#ifndef HTTP_ACTIVITY_DISTRIBUTOR_H_
#define HTTP_ACTIVITY_DISTRIBUTOR_H_

#include "base/basictypes.h"
#include "base/scoped_ptr.h"

#include "nsCOMPtr.h"
#include "nsIHttpActivityObserver.h"
#include "nsIRunnable.h"
#include "nsISupports.h"
#include "nsStringAPI.h"

class nsACString;
class nsIThread;

namespace activity {

class ClockInterface;
class Timer;

class HttpActivityDistributor : public nsIHttpActivityObserver {
 public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIHTTPACTIVITYOBSERVER

  HttpActivityDistributor();

 private:
  ~HttpActivityDistributor();

  scoped_ptr<ClockInterface> clock_;
  scoped_ptr<Timer> timer_;
  nsCOMPtr<nsIThread> main_thread_;

  DISALLOW_COPY_AND_ASSIGN(HttpActivityDistributor);
};

/**
 * MainThreadDistributor is an nsIRunnable that is used to proxy
 * events from the nsIHttpActivityObserver instance running in the
 * network thread to observers listening on the main thread.
 */
class MainThreadDistributor : public nsIRunnable {
 public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIRUNNABLE

  /**
   * Construct a MainThreadDistributor that publishes the event
   * described by the constructor arguments to all observers
   * subscribed to the http-activity-observer topic. The constructor
   * takes the same arguments as
   * nsIHttpActivityObserver::ObserveActivity().
   */
  MainThreadDistributor(
      nsISupports *http_channel,
      PRUint32 activity_type,
      PRUint32 activity_subtype,
      PRTime timestamp,
      PRUint64 extra_size_data,
      const nsACString &extra_string_data);

 private:
  ~MainThreadDistributor();

  nsCOMPtr<nsISupports> http_channel_;
  PRUint32 activity_type_;
  PRUint32 activity_subtype_;
  PRTime timestamp_;
  PRUint64 extra_size_data_;
  nsCString extra_string_data_;
};

}  // namespace activity

#endif  // HTTP_ACTIVITY_DISTRIBUTOR_H_
