![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_logo.png?raw=true "")

# RoboRun-NES
_Robo**RUN**-NES_ is open-source **2D-platform** game written in *C* using [CC65-compiler](https://www.cc65.org/) for NES homebrew projects to check limitation of C against CC65 Assembly. 
Initially this was meant to upload in [NESDev competition 2021](https://neshomebrew.ca/contest19/) but unfortunately the deadline was over so couldn't submit there. :( 

## Game Features :
Multiple _Levels_ with different enemies.<br/>
Invincible state with star and player animation.<br/>
Countdown timers for low health.<br/>
Collision detection with **_Hitbox mechanism._**<br/>
Improved **Graphics and sounds.**<br/>
Supports only **PAL/Dendy .** video region.<br/>

## Code Features :
Easy to understand and well written.<br/>
Uses structures for Player/Enemy/Collectables instead plain c-array/vars.<br/>
All libraries used are well documented.<br/>

## Game title : <br/>
![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_title.png?raw=true "")<br/>

## Game Help : <br/>
![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_help.png?raw=true "")<br/>

## Game Total Score : <br/>
![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_over.png?raw=true "")<br/>

## Gameplay levels : <br/>
![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_level_1.png?raw=true "")<br/>
![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_level_2.png?raw=true "")<br/>
![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_level_3.png?raw=true "")<br/>
## Final level : <br/>
![](https://github.com/haseeb-heaven/RoboRun-NES/blob/main/res/game_level_5.png?raw=true "")<br/>

## Directory Structure :
**build** - Contains final build of game along source code in assembly.<br/>
**cfg** - Contains various configurations that can be used in different type of **NES** games .<br/>
**chr** - Contains CHR Graphics tileset used in this game.<br/>
**gfx** - Contains all Graphics related items used in game like Player/Enemies levels etc .<br/>
**lib** - Contains libraries used Neslib by [Shiru](http://shiru.untergrund.net/) and NesUtils by [Doug Fraker](https://nesdoug.com/) and Nes**C**lib by myself .<br/>
**music** - Contains music and sound effects created using [Famitracker](http://famitracker.com/) and [Famitone2 lib](http://shiru.untergrund.net/files/src/famitone2.zip)  .<br/>
**sfx** - Contains sound effects used in this game also created using **Famitracker** & **Famitone2**.<br/>
**palettes** - Contains different palettes used in game.<br/>
**res** - Contains resources for this README. .<br/>
**scripts** - Contains **Tiled** custom scripts for exporting data directly to C-Code.<br/>
**src** - Contains full source code of this game.<br/>
**utils** - Contains various utils for Meta sprites and Sounds.<br/>
**tools** - Contains various necessary tools used for creating game resources graphics/sounds etc .<br/>
**.vscode** - Contains extensions for Visual studio code to run your NES C-Code directly.<br/>

## How to build/Run :<br/>
## PRE-REQUIESTE :<br/>
You need to download [CC65-compiler](https://www.cc65.org/) first and the it to your system **PATH** variable.
after that add your favourite emulator also to your system path for testing.<br/>

Game can be compiled and run using 2 different methods.<br/>
1)Windows **Batch file** method.<br/>
2)GNU **Make file** method.<br/>

## Batch file method :<br/>
Just run **_Compile.bat_** file and it will automatically compile and build game along music.<br/>
Or run **_BuildGame.bat_** provide arguments like this **_BuildGame.bat_** RoboRun-NES.c mesen to try on mesen Emulator.<br/>

## GNU Make file method :<br/>
Run command _make_ or **_make compile_** then after it run **_make run_**.<br/>
To clean the build of game run **_make clean_**.<br/>
To support your own emulator edit Makefile change **EMULATOR = fceux** to **EMULATOR = your emulator**.<br/>

## Software tools used in making this game :<br/>
**1)Tiled:** For game Level designing. <br/>
**2)FamiTracker:** For Sound and music.<br/>
**3)NES Screen Tool(NESst):** For Intros/Outros and game titles.<br/>
**4)yychr:** For game sprites editor. <br/>
**5)meta2c:** For converting meta-tiles and meta-sprites to c code.<br/>
**6)NES-Sprite-Convertor:** For converting resources PNG/BMP to CHR.<br/>
Most of these tools can be found under _tools_ directory.<br/>


## NESDev open-source community Contribution list :<br/>
**1)Shiru:** For contributing to various libraries/tools to open-source community. <br/>
**Work:** Neslib,Famitone2,NESst,Space Checker,Sort and more. [Check Website](http://shiru.untergrund.net/software.shtml)

**2)NESDoug:** For contributing to various tutorials/tools to open-source community. <br/>
**Work:** Open source Platformer games and Utils Nesdoug.h. [Check Website](https://nesdoug.com/l)

**3)Mojontwins:** For contributing to various games/tools [Game engine for C](https://github.com/mojontwins/MK1_NES) to open-source community.<br/> 
**Work:** MK1_NES Game engine,Super Uwol,cheril_perils,sgt_helmet, and tools like mkts,eneexp3,rle44mapMK1 etc. [Check Website](https://www.mojontwins.com/)<br/>

**4)Chriscpp:** For contributing to modular game engine aKa [Nes starter kit](https://github.com/cppchriscpp/nes-starter-kit) to open-source community. <br/>
**Work:** Modular Game engine,Nesnet,nes-c-boilerplate and more. [Check Website](http://cpprograms.net/)

If you think someone is missing from list then please create PR and expand this list thanks.<br/>

**VERSION INFO :**<br/>
RoboRun Version : V 1.0  Dated : 30/03/2021.<br/>
