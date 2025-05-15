import os
from os.path import join, abspath
Import("env")

src_path = abspath(".pio/libdeps/genericCH32V003F4U6/TM16xx LEDs and Buttons/src")
needed_files = [
    "TM1652.cpp",
    "TM16xx.cpp"
]
for file in needed_files:
    file_to_build = join(src_path, file)
    obj = env.Object(file_to_build)
    env.Prepend(LIBS=[obj])
