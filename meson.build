# بسم الله الرحمن الرحيم
project('Dikr', 'cpp',
        default_options: 'default_library=static')


sdl_dep = [
    dependency('sdl2'),
    dependency('sdl2_ttf')
]

Dikr_files = [
    'Dikr_exe/main.cpp'
]

executable('BismiAllah',
            Dikr_files,
            dependencies: sdl_dep)

executable('BismiAllah1',
            'Dikr_exe/main1.cpp',
            dependencies: sdl_dep)

Settings_files = [
    'settings_exe/main.cpp'
]

