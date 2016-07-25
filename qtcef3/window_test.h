#pragma once
#include <set>

#include "include/wrapper/cef_message_router.h"
typedef std::set<CefMessageRouterBrowserSide::Handler*> MessageHandlerSet;
namespace window_test{

	void CreateMessageHandlers(MessageHandlerSet& handlers);

}