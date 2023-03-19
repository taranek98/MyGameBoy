#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#define CARTRIDGE_FIRST_ROM 1

typedef struct {                                        //Memory Address on ROM  $0100 - $014F
    unsigned char EntryPoint [4];                       //$0100 - $0103
    unsigned char NintendoLogo[0x30];                   //#0104 - $0133
    char Title[16];                                     //$0134 - $0143
    unsigned short NewLicenseeCode;                     //$0144 - $0145
    unsigned char SGB_Flag;                             //$0146
    unsigned char CartridgeType;                        //$0147
    unsigned char ROM_Size;                             //$0148
    unsigned char RAM_Size;                             //$0149
    unsigned char DestinationCode;                      //$014A
    unsigned char OldLicenseeCode;                      //$014B
    unsigned char Version;                              //$014C
    unsigned char Checksum;                             //$014D
    unsigned short GlobalChecksum;                      //$014E - $014F
} ROM_Header;

typedef struct{
    unsigned char *ROM_Data;
    ROM_Header * header;
} Cartridge;

void Cartridge_RomLoad();
Cartridge * Cartridge_GetPointer();
const char * Cartridge_GetTypeName();
const char *cart_lic_name();

#endif