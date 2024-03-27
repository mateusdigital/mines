
New-Item -Force -ItemType Directory -Path ./out/core;

cl.exe game/core/mines.c  /Zi /DEBUG  /Fo"./out/core/mines.obj"  /Fd"./out/core/mines.pdb"
cl.exe game/core/main.c   /Zi /DEBUG  /Fo"./out/core/main.obj"   /Fd"./out/core/main.pdb"
cl.exe "./out/core/mines.obj" "./out/core/main.obj" /Fe"./out/core/mines.exe" /Fd"./out/core/main.pdb"
