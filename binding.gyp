{
    'targets':
    [
        {
            'target_name': "node-sdl2_net",
            'include_dirs':
            [
                "<(module_root_dir)",
                "<!(node -e \"require('@flyover/node-sdl2/include')\")",
                "<!(node -e \"require('nan')\")"
            ],
            'sources':
            [
                "node-sdl2_net.cc"
            ],
            'conditions':
            [
                [
                    'OS=="linux"',
                    {
                        'include_dirs': [ "/usr/local/include/SDL2", "/usr/local/include/SDL2_net" ],
                        'cflags': [ "<!@(sdl2-config --cflags)" ],
                        'ldflags': [ "<!@(sdl2-config --libs)" ],
                        'libraries': [ "-lSDL2", "-lSDL2_net" ]
                    }
                ],
                [
                    'OS=="mac"',
                    {
                        'include_dirs': [ "/usr/local/include/SDL2", "/usr/local/include/SDL2_net" ],
                        'cflags': [ "<!@(sdl2-config --cflags)" ],
                        'ldflags': [ "<!@(sdl2-config --libs)" ],
                        'libraries': [ "-L/usr/local/lib", "-lSDL2", "-lSDL2_net" ]
                    }
                ],
                [
                    'OS=="win"',
                    {
                        'include_dirs': [ "$(SDL2_ROOT)/include", "$(SDL2_NET_ROOT)/include" ],
                        'libraries':
                        [
                            "$(SDL2_ROOT)/lib/x64/SDL2.lib",
                            "$(SDL2_NET_ROOT)/lib/x64/SDL2_net.lib"
                        ],
                        'copies':
                        [
                            {
                                'destination': "<!(echo %USERPROFILE%)/bin",
                                'files':
                                [
                                    "$(SDL2_NET_ROOT)/lib/x64/SDL2_net.dll"
                                ]
                            }
                        ]
                    }
                ]
            ]
        }
    ]
}
