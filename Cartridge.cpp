#include "Cartridge.h"
#include "Display.h"
#include <SD.h>
#include "Pins.h"
#include "Button.h"

static Cartridge CartridgeObj;

static const char *ROM_Types[] = {
"ROM ONLY",
"MBC1",
"MBC1+RAM",
"MBC1+RAM+BATTERY",
"0x04 ???",
"MBC2",
"MBC2+BATTERY",
"0x07 ???",
"ROM+RAM 1",
"ROM+RAM+BATTERY 1",
"$0A ???",
"MMM01",
"MMM01+RAM",
"MMM01+RAM+BATTERY",
"0x0E ???",
"MBC3+TIMER+BATTERY",
"MBC3+TIMER+RAM+BATTERY 2",
"MBC3",
"MBC3+RAM 2",
"MBC3+RAM+BATTERY 2",
"0x14 ???",
"0x15 ???",
"0x16 ???",
"0x17 ???",
"0x18 ???",
"MBC5",
"MBC5+RAM",
"MBC5+RAM+BATTERY",
"MBC5+RUMBLE",
"MBC5+RUMBLE+RAM",
"MBC5+RUMBLE+RAM+BATTERY",
"0x1F ???",
"MBC6",
"0x21 ???",
"MBC7+SENSOR+RUMBLE+RAM+BATTERY"
};

static const char *LicenseeCode[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x02] = "None",
    [0x03] = "None",
    [0x04] = "None",
    [0x05] = "None",
    [0x06] = "None",
    [0x07] = "None",
    [0x08] = "Capcom",
    [0x09] = "None",
    [0x0A] = "None",
    [0x0B] = "None",
    [0x0C] = "None",
    [0x0D] = "None",
    [0x0E] = "None",
    [0x0F] = "None",
    [0x10] = "None",
    [0x11] = "None",
    [0x12] = "None",
    [0x13] = "Electronic Arts",
    [0x14] = "None",
    [0x15] = "None",
    [0x16] = "None",
    [0x17] = "None",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x1A] = "None",
    [0x1B] = "None",
    [0x1C] = "None",
    [0x1D] = "None",
    [0x1E] = "None",
    [0x1F] = "None",
    [0x20] = "kss",
    [0x21] = "None",
    [0x22] = "pow",
    [0x23] = "None",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x26] = "None",
    [0x27] = "None",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x2A] = "None",
    [0x2B] = "None",
    [0x2C] = "None",
    [0x2D] = "None",
    [0x2E] = "None",
    [0x2F] = "None",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x36] = "None",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x3A] = "None",
    [0x3B] = "None",
    [0x3C] = "None",
    [0x3D] = "None",
    [0x3E] = "None",
    [0x3F] = "None",
    [0x40] = "None",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x43] = "None",
    [0x44] = "Malibu",
    [0x45] = "None",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x48] = "None",
    [0x49] = "irem",
    [0x4A] = "None",
    [0x4B] = "None",
    [0x4C] = "None",
    [0x4D] = "None",
    [0x4E] = "None",
    [0x4F] = "None",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x5A] = "None",
    [0x5B] = "None",
    [0x5C] = "None",
    [0x5D] = "None",
    [0x5E] = "None",
    [0x5F] = "None",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x62] = "None",
    [0x63] = "None",
    [0x64] = "LucasArts",
    [0x65] = "None",
    [0x66] = "None",
    [0x67] = "Ocean",
    [0x68] = "None",
    [0x69] = "Electronic Arts",
    [0x6A] = "None",
    [0x6B] = "None",
    [0x6C] = "None",
    [0x6D] = "None",
    [0x6E] = "None",
    [0x6F] = "None",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x74] = "None",
    [0x75] = "sci",
    [0x76] = "None",
    [0x77] = "None",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x7A] = "None",
    [0x7B] = "None",
    [0x7C] = "None",
    [0x7D] = "None",
    [0x7E] = "None",
    [0x7F] = "None",
    [0x80] = "misawa",
    [0x81] = "None",
    [0x82] = "None",
    [0x83] = "lozc",
    [0x84] = "None",
    [0x85] = "None",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x88] = "None",
    [0x89] = "None",
    [0x8A] = "None",
    [0x8B] = "None",
    [0x8C] = "None",
    [0x8D] = "None",
    [0x8E] = "None",
    [0x8F] = "None",
    [0x90] = "None",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x94] = "None",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x98] = "None",
    [0x99] = "Pack in soft",
    [0x9A] = "None",
    [0x9B] = "None",
    [0x9C] = "None",
    [0x9D] = "None",
    [0x9E] = "None",
    [0x9F] = "None",
    [0xA0] = "None",
    [0xA1] = "None",
    [0xA2] = "None",
    [0xA3] = "None",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
};

static void Cartridge_SdInitialize()
{
    if(!SD.begin(SDCARD_CS_PIN))
    {
        Display_PrintError("Inicjalizacja karty SD nie powiodla sie");
        while(true);
    }
}

static void Cartridge_ResetGameCouter(unsigned char * counter)
{
    *counter = CARTRIDGE_FIRST_ROM;
}

void Cartridge_RomLoad()
{
    Cartridge_SdInitialize();

    File root = SD.open("/");
    unsigned char gameCounter = 0;
    unsigned char selectorNumber = 1;
    bool isGameSelect = false;
    
    Display_StartRomMenu();
    
    while(true)
    {
        File file = root.openNextFile();                            
        if (!file)
        {
            //no more files
            break;
        }
        Display_AddRomName(file.name());
        gameCounter++;
    }

    Display_StartSelector();

    while(isGameSelect != true)
    {
        if(Button_IsDownClick() == true)
        {
            if(selectorNumber < gameCounter)
            {
                Display_SelectorDown();
                selectorNumber++;
            }
        }

        if(Button_IsUpClick() == true)
        {
            if(selectorNumber > 1)
            {
                Display_SelectorUp();
                selectorNumber--;
            }
        }

        if(Button_IsSelectClick() == true)
        {
            isGameSelect = true;
        }
    }
    root.rewindDirectory();                                     //Back to the begin list of files

    Cartridge_ResetGameCouter(&gameCounter);

    while(true)
    {
        File file = root.openNextFile();
        if(gameCounter == selectorNumber)
        {
            unsigned int romSize = file.available();
            CartridgeObj.ROM_Data = new unsigned char [romSize];
            file.read(CartridgeObj.ROM_Data, romSize);
            file.close();
            break;
        }
        gameCounter++;
    }
    CartridgeObj.header = (ROM_Header *)(CartridgeObj.ROM_Data + 0x100);
    
}

Cartridge * Cartridge_GetPointer()
{
    return &CartridgeObj;
}

const char * Cartridge_GetTypeName()
{
    if (CartridgeObj.header->CartridgeType <= 0x22)
    {
        return ROM_Types[CartridgeObj.header->CartridgeType];
    }
    return "UNKNOW";
}

const char * Cartridge_GetLicenseeName() 
{
    if (CartridgeObj.header->NewLicenseeCode <= 0xA4) 
    {
        return LicenseeCode[CartridgeObj.header->NewLicenseeCode];
    }
    return "UNKNOWN";
}