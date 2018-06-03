#include <string>
using std::string;

#include <iostream>
using std::cout;
#include "Miner/CMinerAuthor.h"

static CMinerAuthor miner;

string getRandomStr(int length) {
    string baseStr = "abcdefghijklmnopqrstuvwxyz";
    string ret;
    int range = baseStr.size();
    for (int i = 0; i < length; i++) {
        ret += baseStr[lrand48() % range];
    }

    return ret;
}


void testByStep(string seqence) {
    miner.setInputSequeuece(seqence);

    clock_t start = clock();
    miner.cutAccessSequence();
    miner.generateFirstDs();

    // mining
    SubseqnenceSuffix ss = miner.getSeqFromDs();
    miner.candidateFreSubsequences(ss.getSubsequence(), ss.getOccurtimes());

    miner.genClosedFreSubsequences();   // filter: close frequent subsequence
    miner.generateRules();
    clock_t end = clock();

    cout << "================== Generating Corrlation Rules ======================\n";
    cout << "Window size:\t" << miner.getWindowSize() << "\n";
    cout << "Max Gap:\t" << miner.getMaxGap() << "\n";
    cout << "Min Support:\t" << miner.getMinSupport() << "\n";
    cout << "Min Confidence:\t" << miner.getMinConfidence() << "\n";

    cout << "Input Sequence Length:\t\t" << miner.getInputSequeuece().size() << "\n";
    cout << "Input Segments Length:\t\t" << miner.getInputSegments().size() << "\n";
    cout << "Frequent Subsequences:\t\t{";
    for (const auto &entry : miner.getFreSubsequences()) {
        cout << entry.first << "=" << entry.second << ", ";
    }
    cout << "\b}\n";
    cout << "Closed Frequent Subsequences:\t{";
    for (const auto &entry : miner.getCloseFreSubsequencs()) {
        cout << entry.first << "=" << entry.second << ", ";
    }
    cout << "\b}\n";
    cout << "Rules Numer:\t" << miner.getRules().size() <<"\n";
    for (const auto &entry : miner.getRules()) {
        cout << entry.first << "=" << entry.second << "\n";

    }

    cout << "Mining Time: " << (end - start) / CLOCKS_PER_SEC << "\n";

    miner.clear();
}

int main(int argc, char* argv[]) {
    // 输出关联关系挖掘过程中的每一步中间结果
    string seqence = getRandomStr(100000);

    testByStep(seqence);
}