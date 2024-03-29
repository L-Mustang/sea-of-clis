# Sea of CLIs
A small turn-based CLI game with support for cross-platform CMake development. Additionally supports CRT memory leak detection and ASAN in VS 2022.

# Justifications

### Code conventions and style
Joint Strike Fighter Air Vehicle C++ Coding Standards - Dec 2005 (Doc. 2RDU00001 Rev. C)

### String pass by value with move semantics
https://clang.llvm.org/extra/clang-tidy/checks/modernize/pass-by-value.html
https://stackoverflow.com/a/63468679/10787114

### Noexcept on move ctors and operators
https://stackoverflow.com/a/32225460/10787114

### map over unordered_map
https://stackoverflow.com/a/69490123/10787114

### static members functions because no members are accessed
https://softwareengineering.stackexchange.com/a/423306

### final else clause
See AV Rule 192

### Deleted copy
https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rc-copy-virtual

### ASan exceptions
https://developercommunity.visualstudio.com/t/access-violation-writing-location-in-output-window/1383196

### Credits
Old-Fashioned Pirate Ship by KokoroReflections, unmodified.
https://opengameart.org/content/old-fashioned-pirate-ship
Licensed under CC BY 4.0.
