# بسم الله الرحمن الرحيم
project('Dikr', 'cpp',
        default_options: 'default_library=static')


sdl_dep = [
    dependency('sdl2'),
    dependency('sdl2_ttf')
]

executable('BismiAllah',
          'Dikr_exe/main.cpp',
           dependencies: sdl_dep)

executable('BismiAllah1',
            'Dikr_exe/main1.cpp',
            dependencies: sdl_dep)

executable('PoppingDikr',
            'popping_Dikr.cpp',
            dependencies: sdl_dep)

Settings_files = [
    'settings_exe/main.cpp'
]

