cd shnell && make
cd bin
chmod 666 zero
chmod 666 one
chmod 666 banner

cp * /usr/local/bin

cd ../../blinkingProc/ && make
cd bin
cp blink ../../shnell/bin