
##------------------------------------------------------------------------------
$PROJECT_NAME = "mines";


##------------------------------------------------------------------------------
## Make tiles image from the Photoshop source.
psd-to-png --input-path "./res/tiles.psd" --output-path "./res/tiles.png";

##------------------------------------------------------------------------------
## Create the Gameboy Tile data from the image.
./tools/png2gbtiles.exe "./res/tiles.png" -csource -pal="./res/pal" "game_tiles";
Move-Item -Force ./game_tiles* "./game/resources/"

##------------------------------------------------------------------------------
## Create GameBoy Map information from the Tiled.
tiled-to-map --input-path "./res/TestMap.tmx"    --output-path "./game/resources/TestMap";
tiled-to-map --input-path "./res/MenuMap.tmx"    --output-path "./game/resources/MenuMap";
tiled-to-map --input-path "./res/CreditsMap.tmx" --output-path "./game/resources/CreditsMap";

tiled-to-map --input-path "./res/HudWin.tmx" --output-path "./game/resources/HudWin";

#------------------------------------------------------------------------------
## Compile the game.
./libs/gbdk/bin/lcc -Igame -Wm-yc -c         -o build/main.o  game/main.c
./libs/gbdk/bin/lcc -Igame -Wa-l -Wl-m -Wl-j -o build/${PROJECT_NAME}.gb build/main.o
