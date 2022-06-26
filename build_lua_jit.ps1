Invoke-WebRequest https://luajit.org/download/LuaJIT-2.1.0-beta3.zip -OutFile LuaJIT-2.1.0-beta3.zip
Expand-Archive LuaJIT-2.1.0-beta3.zip -DestinationPath .

cd .\LuaJIT-2.1.0-beta3\src

.\msvcbuild.bat static

New-Item .\LuaJIT\include -ItemType Directory
New-Item .\LuaJIT\lib\x64 -ItemType Directory

@("lauxlib.h", "lua.h", "lua.hpp", "luaconf.h", "luajit.h", "lualib.h") | Move-Item -Destination .\LuaJIT\include
Move-Item -Path .\lua51.lib -Destination .\LuaJIT\lib\x64\
Move-Item -Path .\LuaJIT -Destination .\..\..\contrib

cd ..\..

Remove-Item .\LuaJIT-2.1.0-beta3\ -Recurse
Remove-Item .\LuaJIT-2.1.0-beta3.zip
