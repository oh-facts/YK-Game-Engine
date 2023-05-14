# C/C++ build environment template

Tired of getting restricted to development environments designed by mega corporations?
Tired of waiting 15 seconds for beefy IDEs to start up? (saved time can be used to fix bugs (can't relate, I don't make bugs))

Ever wanted a solid build environment to use with a text editor of your choice?
Ever wanted to build dependencies from source and link them yourself? Like a true degenerate instead of using a package manager like vcpkg or conan like a sane person?

Want a solution that is truly cross platform, bareboned enough to not be bloated, but functional enough to seamlessly replace your current workflow?

What a time to be alive!

Introducing the revolutionary (woah slow down) C/C++ build environment template that lets you do all of the above and much more! 

## Requirements

1. cmake cli
2. ninja build system *
3. clang *

 *You can tinker and change them to something else if you want. I picked these because they have native support for Linux, Windows and Mac.


## Quickstart
Run the ``gen.bat``or ``gen.sh`` file in the ``scripts`` folder to generate the build (generated in an ``out`` folder). You can open the scripts  in a text editor to see what commands are used.
The comments in the cmake detail out how to extend it, wherever needed. 
I used ``glfw`` (platform agnostic windowing library) as an example to show 3rd party linking.
Compile commands are generated which help with your text editor with syntax highlighting for custom libraries too.

Open issues for suggestions/questions/contributions/abuses

cheers,

facts (spacelemon)