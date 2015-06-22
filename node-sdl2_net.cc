/**
 * Copyright (c) Flyover Games, LLC.  All rights reserved. 
 *  
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated 
 * documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to 
 * whom the Software is furnished to do so, subject to the 
 * following conditions: 
 *  
 * The above copyright notice and this permission notice shall 
 * be included in all copies or substantial portions of the 
 * Software. 
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY 
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 */

#include "node-sdl2_net.h"

#include <v8.h>
#include <node.h>
#include <SDL.h>
#include <SDL_net.h>

#if defined(__ANDROID__)
#include <android/log.h>
#define printf(...) __android_log_print(ANDROID_LOG_INFO, "printf", __VA_ARGS__)
#endif

#define countof(_a) (sizeof(_a)/sizeof((_a)[0]))

using namespace v8;

namespace node_sdl2_net {

MODULE_EXPORT_IMPLEMENT_TODO(SDLNet_LinkedVersion)

MODULE_EXPORT_IMPLEMENT(SDLNet_Init)
{
	NanScope();
	int err = SDLNet_Init();
	if (err < 0)
	{
		printf("SDLNet_Init error: %d\n", err);
	}
	NanReturnValue(NanNew<Integer>(err));
}

MODULE_EXPORT_IMPLEMENT(SDLNet_Quit)
{
	NanScope();
	SDLNet_Quit();
	NanReturnUndefined();
}

MODULE_EXPORT_IMPLEMENT(SDLNet_GetError)
{
	NanScope();
	const char* sdl_net_error = SDLNet_GetError();
	NanReturnValue(NanNew<String>(sdl_net_error));
}

MODULE_EXPORT_IMPLEMENT(SDLNet_ClearError)
{
	NanScope();
	SDL_ClearError();
	NanReturnUndefined();
}

#if NODE_VERSION_AT_LEAST(0,11,0)
void init(Handle<Object> exports, Handle<Value> module, Handle<Context> context)
#else
void init(Handle<Object> exports/*, Handle<Value> module*/)
#endif
{
	NanScope();

	// SDL_net.h

	MODULE_CONSTANT(exports, SDL_NET_MAJOR_VERSION);
	MODULE_CONSTANT(exports, SDL_NET_MINOR_VERSION);
	MODULE_CONSTANT(exports, SDL_NET_PATCHLEVEL);

	MODULE_EXPORT_APPLY(exports, SDLNet_LinkedVersion);
	MODULE_EXPORT_APPLY(exports, SDLNet_Init);
	MODULE_EXPORT_APPLY(exports, SDLNet_Quit);
	MODULE_EXPORT_APPLY(exports, SDLNet_GetError);
	MODULE_EXPORT_APPLY(exports, SDLNet_ClearError);
}

} // namespace node_sdl2_net

#if NODE_VERSION_AT_LEAST(0,11,0)
NODE_MODULE_CONTEXT_AWARE_BUILTIN(node_sdl2_net, node_sdl2_net::init)
#else
NODE_MODULE(node_sdl2_net, node_sdl2_net::init)
#endif

