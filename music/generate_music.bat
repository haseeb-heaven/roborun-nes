@echo off
rm music.s
rm ..\sfx\sounds.s
..\utils\nsf2data ..\sfx\sounds.nsf -ca65 -pal
..\utils\text2data music.txt -ca65 -pal
echo MUSIC AND SFX CREATED!
