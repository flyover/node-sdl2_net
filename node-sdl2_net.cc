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

#if defined(__ANDROID__)
#include <android/log.h>
#define printf(...) __android_log_print(ANDROID_LOG_INFO, "printf", __VA_ARGS__)
#endif

#define countof(_a) (sizeof(_a)/sizeof((_a)[0]))

namespace node_sdl2_net {

NANX_EXPORT(SDLNet_LinkedVersion) { Nan::ThrowError("TODO"); }

NANX_EXPORT(SDLNet_Init)
{
	int err = SDLNet_Init();
	if (err < 0)
	{
		printf("SDLNet_Init error: %d\n", err);
	}
	info.GetReturnValue().Set(Nan::New(err));
}

NANX_EXPORT(SDLNet_Quit)
{
	SDLNet_Quit();
}

NANX_EXPORT(SDLNet_GetError)
{
	const char* sdl_net_error = SDLNet_GetError();
	info.GetReturnValue().Set(NANX_STRING(sdl_net_error));
}

NANX_EXPORT(SDLNet_ClearError)
{
	SDL_ClearError();
}

NAN_MODULE_INIT(init)
{
	// SDL_net.h

	NANX_CONSTANT(target, SDL_NET_MAJOR_VERSION);
	NANX_CONSTANT(target, SDL_NET_MINOR_VERSION);
	NANX_CONSTANT(target, SDL_NET_PATCHLEVEL);

	NANX_EXPORT_APPLY(target, SDLNet_LinkedVersion);
	NANX_EXPORT_APPLY(target, SDLNet_Init);
	NANX_EXPORT_APPLY(target, SDLNet_Quit);
	NANX_EXPORT_APPLY(target, SDLNet_GetError);
	NANX_EXPORT_APPLY(target, SDLNet_ClearError);
}

} // namespace node_sdl2_net

NODE_MODULE(node_sdl2_net, node_sdl2_net::init)
