
##~---------------------------------------------------------------------------##
##                               *       +                                    ##
##                         '                  |                               ##
##                     ()    .-.,="``"=.    - o -                             ##
##                           '=/_       \     |                               ##
##                        *   |  '=._    |                                    ##
##                             \     `=./`,        '                          ##
##                          .   '=.__.=' `='      *                           ##
##                 +                         +                                ##
##                      O      *        '       .                             ##
##                                                                            ##
##  File      : build-gb.ps1                                                  ##
##  Project   : mines                                                         ##
##  Date      : 2024-03-27                                                    ##
##  License   : See project's COPYING.TXT for full info.                      ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2024                                         ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

##------------------------------------------------------------------------------
$PROJECT_NAME = "mines";

$RES_DIR   = "res/gb";
$TOOLS_DIR = "libs/mdgb/tools";
$GAME_DIR  = "game/gb";
$CORE_DIR  = "game/core";
$MDGB_DIR  = "libs/mdgb";
$GBDK_DIR  = "${MDGB_DIR}/libs/gbdk";
$BUILD_DIR = "build/gb";

$BUILD_ASSETS = $false;

if($BUILD_ASSETS) {
    ##--------------------------------------------------------------------------
    ## Make tiles image from the Photoshop source.
    psd-to-png --input-path "$RES_DIR/tiles.psd" --output-path "$RES_DIR/tiles.png";

    ##--------------------------------------------------------------------------
    ## Create the Gameboy Tile data from the image.
    & ${TOOLS_DIR}/png2gbtiles.exe "${RES_DIR}/tiles.png" -csource -pal="${RES_DIR}/pal" "game_tiles";

    New-Item  -Force -ItemType Directory "${GAME_DIR}/resources/";
    Move-Item -Force ./game_tiles* "${GAME_DIR}/resources/";

    ##--------------------------------------------------------------------------
    ## Create GameBoy Map information from the Tiled.
    tiled-to-map --input-path "${RES_DIR}/TestMap.tmx"    --output-path "${GAME_DIR}/resources/TestMap";
    tiled-to-map --input-path "${RES_DIR}/MenuMap.tmx"    --output-path "${GAME_DIR}/resources/MenuMap";
    tiled-to-map --input-path "${RES_DIR}/CreditsMap.tmx" --output-path "${GAME_DIR}/resources/CreditsMap";
    tiled-to-map --input-path "${RES_DIR}/HudWin.tmx"     --output-path "${GAME_DIR}/resources/HudWin";

    ##--------------------------------------------------------------------------
    New-Item -Force -ItemType Directory "$BUILD_DIR";

}
## Compile the game.
& "${GBDK_DIR}/bin/lcc "                         `
   -I"${GAME_DIR}" -I"${CORE_DIR}" -I"${MDGB_DIR}" `
    -Wm-yc -c                                    `
    -o "${BUILD_DIR}/main.o"                     `
    "${GAME_DIR}/main.c"                         ;

& "${GBDK_DIR}/bin/lcc"                          `
   -I"${GAME_DIR}" -I"${CORE_DIR}" -I"${MDGB_DIR}" `
   -Wa-l -Wl-m -Wl-j                             `
   -o "${BUILD_DIR}/${PROJECT_NAME}.gb"          `
   "${BUILD_DIR}/main.o"                         ;


# ./libs/mdgb/libs/gbdk/bin/lcc  -Igame/gb -Ilibs/mdgb -Wm-yc -c -o ./build/gb/main.o ./game/gb/main.c
# ./libs/mdgb/libs/gbdk/bin/lcc  -Igame/gb -Ilibs/mdgb -Wa-l -Wl-m -Wl-j -o ./build/gb/mines.gb ./build/gb/main.o