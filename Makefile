#Makefile to Compile RoboRun-NES.c to binary NES file.

NAME = RoboRun-NES
EMULATOR = fceux

compile:
	cc65 -Oirs $(NAME).c --add-source
	ca65 crt0.s
	ca65 $(NAME).s -g
	ld65 -C nrom_32k_vert.cfg -o $(NAME).nes crt0.o $(NAME).o nes.lib -Ln labels.txt
	mv labels.txt build 
	mv $(NAME).s build
	mv $(NAME).nes build 
	cmd /C music\generate_music.bat
	
clean:
	rm -f build/$(NAME).s
	rm -f *.o
	rm -f build/labels.txt
	rm -f build/$(NAME).nes
	
	
run: 
	@[ "${EMULATOR}" ] || ( echo "Emulator name is not provided"; exit 1 )
	$(EMULATOR) build/$(NAME).nes

