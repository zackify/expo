// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include <folly/dynamic.h>
#include <ABI33_0_0jsi/ABI33_0_0jsi.h>
#include <ReactABI33_0_0/uimanager/UIManager.h>
#include <ReactABI33_0_0/uimanager/primitives.h>

namespace facebook {
namespace ReactABI33_0_0 {

/*
 * Exposes UIManager to JavaScript realm.
 */
class UIManagerBinding : public ABI33_0_0jsi::HostObject {
 public:
  /*
   * Installs UIManagerBinding into JavaSctipt runtime.
   * Thread synchronization must be enforced externally.
   */
  static void install(
      ABI33_0_0jsi::Runtime &runtime,
      std::shared_ptr<UIManagerBinding> uiManagerBinding);

  UIManagerBinding(std::unique_ptr<UIManager> uiManager);

  /*
   * Starts ReactABI33_0_0 Native Surface with given id, moduleName, and props.
   * Thread synchronization must be enforced externally.
   */
  void startSurface(
      ABI33_0_0jsi::Runtime &runtime,
      SurfaceId surfaceId,
      const std::string &moduleName,
      const folly::dynamic &initalProps) const;

  /*
   * Stops ReactABI33_0_0 Native Surface with given id.
   * Thread synchronization must be enforced externally.
   */
  void stopSurface(ABI33_0_0jsi::Runtime &runtime, SurfaceId surfaceId) const;

  /*
   * Delivers raw event data to JavaScript.
   * Thread synchronization must be enforced externally.
   */
  void dispatchEvent(
      ABI33_0_0jsi::Runtime &runtime,
      const EventTarget *eventTarget,
      const std::string &type,
      const ValueFactory &payloadFactory) const;

  /*
   * Invalidates the binding and underlying UIManager.
   * Allows to save some resources and prevents UIManager's delegate to be
   * called.
   * Calling public methods of this class after calling this method is UB.
   * Can be called on any thread.
   */
  void invalidate() const;

  /*
   * `ABI33_0_0jsi::HostObject` specific overloads.
   */
  ABI33_0_0jsi::Value get(ABI33_0_0jsi::Runtime &runtime, const ABI33_0_0jsi::PropNameID &name) override;

 private:
  std::unique_ptr<UIManager> uiManager_;
  std::unique_ptr<const EventHandler> eventHandler_;
};

} // namespace ReactABI33_0_0
} // namespace facebook
