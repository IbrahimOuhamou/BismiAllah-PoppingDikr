# بسم الله الرحمن الرحيم
project('Dikr', 'cpp',
        default_options: 'default_library=static')


sdl_dep_text = [
    dependency('sdl2'),
    dependency('sdl2_ttf')
]

sdl_dep_image = [
    dependency('sdl2'),
    dependency('sdl2_image')
#    dependency('harfbuzz')
]

Dikr_files = [
    'Dikr_exe/main.cpp'
]

executable('BismiAllah',
            Dikr_files,
            dependencies: sdl_dep_text)

executable('BismiAllah1',
            'Dikr_exe/main1.cpp',
            dependencies: sdl_dep_image)

Settings_files = [
    'settings_exe/main.cpp'
]

