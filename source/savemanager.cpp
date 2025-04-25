#include "savemanager.h"
#include <nds.h>
#include <stdio.h>
#include <fat.h>

#define FILE_NAME "Cpp-y-Bird.sav"

SaveManager::SaveManager() {
}

void SaveManager::Save(const SaveData& data) {
    FILE* file = fopen(FILE_NAME, "wb");
    if (file) {
        iprintf("%d",data.highscore);
        fwrite(&data, sizeof(SaveData), 1, file);
        fclose(file);
    }
}

SaveData SaveManager::Load() {
    SaveData data;
    FILE* file = fopen(FILE_NAME, "rb");
    if (file) {
        fread(&data, sizeof(SaveData), 1, file);
        fclose(file);
    }
    return data;
}

void SaveManager::Reset() {
    SaveData empty;
    Save(empty);
}
