export GBDKDIR=/opt/gbdk/

CC=${GBDKDIR}/bin/lcc
FLAGS="-Wa-l -Wl-m -Wl-j";

$CC -Igame -Ilibs/pw_gb $FLAGS -c -o build/main_linux.o  game/main.c
$CC -Igame -Ilibs/pw_gb $FLAGS    -o build/main_linux.gb build/main_linux.o

#  -DUSE_SFR_FOR_REG
#  -DUSE_SFR_FOR_REG
${GBDKDIR}/bin/lcc -v
echo "---------------------------------------------------------------------"
