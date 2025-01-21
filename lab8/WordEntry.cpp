#include "WordEntry.h"

WordEntry::WordEntry(const string &text, int score)
    : word(text), numAppearances(1), totalScore(score) {
}

void WordEntry::addNewAppearance(int s) {
    totalScore += s;
    ++numAppearances;
}

const string &WordEntry::getWord() {
    return word;
}

double WordEntry::getAverage() {
    return static_cast<double>(totalScore) / numAppearances;
}