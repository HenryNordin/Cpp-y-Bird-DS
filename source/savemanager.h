#pragma once

struct SaveData {
    char tag[8] = { 'B', 'I', 'R', 'D', ' ', 'S', 'A', 'V' };
    int highscore = 0;
};

class SaveManager {
public:
    SaveManager();
    void Save(const SaveData& data);
    SaveData Load();
    void Reset();
};
