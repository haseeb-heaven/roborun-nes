/*
# written by Doug Fraker 2018
# this file parses a binary, uncompressed nametable file,
# including attribute bytes from NES Screen Tool (.nam file)
# converts to a c array of metatile data (metatiles.h)

meta2c was converted to native(C/C++) code from Runtime-Environment(Python) by Haseeb Mir
Copyleft source and binary.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TILES 64 //Max 64 tiles
#define TILE_BYTES 4 //4 bytes (2 * 2) for single tile.

int attrib_list[MAX_TILES] = {0};
int bit1, bit2, bit3, bit4;

FILE *nam_file, *c_file;
void parse_bits(int);
void show_help();
void show_version(float);

int main(int argc, char *argv[])
{
    float app_version = 1.0f;
    const char *infile_name = "metatiles.nam", *outfile_name = "metatiles.h", *meta_arr = "metatiles";

    int j, bit = 0, tile1, tile2, tile3, tile4, attrib_tile;
    size_t file_size;

    if (argc < 2)
    {
        fprintf(stderr,
                "Usage %s infile outfile array-name\n\nDefault values (if not provided with arguments):\n\ninfile [REQUIRED] -  defaults to '%s'\n\
outfile [OPTIONAL] -  defaults to '%s'\narray-name [OPTIONAL] - defaults to '%s'  it will be the name of array in output file\n\n\
Flags\n\n-h | --help\tShows help\n-v | --version Shows current version\n\n\
meta2c was written by Doug Fraker 2018\n\
And was converted to Native-Environment(C/C++) application from Runtime-Environment(Python) by Haseeb Mir",
                argv[0], infile_name, outfile_name,meta_arr);
        exit(EXIT_FAILURE);
    }

    else
    {
        //Parse the flags.
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
            show_help();

        else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))
            show_version(app_version);

        if (argc >= 2)
            infile_name = argv[1];
        if (argc >= 3)
            outfile_name = argv[2];
        if (argc == 4)
            meta_arr = argv[3];

        nam_file = fopen(infile_name, "rb");
        c_file = fopen(outfile_name, "w");

        if (nam_file == NULL || c_file == NULL)
        {
            fprintf(stderr, "ERROR: input file '%s' could not be found\n", infile_name);
            exit(EXIT_FAILURE);
        }

        //Get the file size.
        fseek(nam_file, 0L, SEEK_END);
        file_size = ftell(nam_file);

        if (file_size != 1024)
        {
            fprintf(stderr, "ERROR: wrong file size, should be 1024 bytes, but is %d bytes\n", file_size);
            fclose(nam_file);
            fclose(c_file);
            return -1;
        }

        //Add header data.
        fprintf(c_file,"/***DO NOT EDIT** This File was generated using %s Metatiles converter \nInput File: %s\nOutput file: %s\n*/\n\n",argv[0],infile_name,outfile_name);

        //Add meta data.
        fprintf(c_file, "const unsigned char %s[]=\n{\n", meta_arr);

        //Init bits.
        bit = 0;

        //0 1 16 17
        //load all the attribute bits into an array, separated
        fseek(nam_file, 960, SEEK_SET);
        j = 0;
        for (int i = 0; i < MAX_TILES / TILE_BYTES; ++i)
        {
            bit = (int)fgetc(nam_file);
            parse_bits(bit);
            attrib_list[(i * 2) + j] = bit1;
            attrib_list[(i * 2) + j + 1] = bit2;
            attrib_list[(i * 2) + j + 16] = bit3;
            attrib_list[(i * 2) + j + 17] = bit4;
            if (i == 7)
                j = 16;
        }

        j = 0;
        for (int i = 0; i < MAX_TILES; ++i)
        {
            fseek(nam_file, j, SEEK_SET);
            tile1 = (int)fgetc(nam_file);
            tile2 = (int)fgetc(nam_file);

            j += 32;
            fseek(nam_file, j, SEEK_SET);
            tile3 = (int)fgetc(nam_file);
            tile4 = (int)fgetc(nam_file);

            if (i != 0 && tile1 == 0 && tile2 == 0 && tile3 == 0 && tile4 == 0)
                break;
            if (i == 15 || i == 31 || i == 47)
                j += 2;
            else
                j = j - 30;

            attrib_tile = attrib_list[i]; //Last tile is attribute tile.
            //Print all tiles [1-5] including attribute tile.
            fprintf(c_file, "\t%d, %d, %d, %d, %d,\n", tile1, tile2, tile3, tile4, attrib_tile);
        }

        //delete that last comma
        fseek(c_file, ftell(c_file) - 3, SEEK_SET);
        fprintf(c_file, "\n};\n\n");

        fprintf(stdout, "SUCCESS: '%s' file is generated", outfile_name);
        fclose(nam_file);
        fclose(c_file);
    }
    return EXIT_SUCCESS;
}

void parse_bits(int bit)
{
    bit1 = bit & 0x03;
    bit2 = (bit & 0x0c) >> 2;
    bit3 = (bit & 0x30) >> 4;
    bit4 = (bit & 0xc0) >> 6;
}

//Give credits to dev.
void show_help()
{
    fprintf(stdout, "meta2c is metatiles converter it parses a binary, uncompressed nametable file\n\
including attribute bytes from NES Screen Tool (.nam file) \
converts to a c array of metatile data (metatiles.h)\n\
written by Doug Fraker 2018");
    exit(EXIT_SUCCESS);
}

void show_version(float version){
    fprintf(stdout,"meta2c application version is %0.3f\nCopyleft Haseeb Mir (2021)",version);
    exit(EXIT_SUCCESS);
}