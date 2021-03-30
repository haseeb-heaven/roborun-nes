@echo off
set argfile=%1
set emulator=%2
set inpfile=%argfile:~0,-2%

utils\nsf2data sfx\sounds.nsf -ca65 -pal
utils\text2data music\music.txt -ca65 -pal
echo MUSIC AND SFX DONE!

cc65 -Oirs %inpfile%.c --add-source
ca65 crt0.s
ca65 %inpfile%.s -g
ld65 -C nrom_32k_vert.cfg -o %inpfile%.nes crt0.o %inpfile%.o nes.lib -Ln labels.txt

IF %ERRORLEVEL% EQU 0 ( 
echo BUILD DONE!
%emulator% %inpfile%.nes
move /Y labels.txt BUILD 
move /Y %inpfile%.s BUILD 
move /Y %inpfile%.nes BUILD 

rm -f ./%inpfile%.s
rm -f ./*.o
)


