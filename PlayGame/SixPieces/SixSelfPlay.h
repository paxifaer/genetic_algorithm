//
// Created by Parsifal on 2022/10/13.
//

#ifndef GENETIC_SIXSELFPLAY_H
#define GENETIC_SIXSELFPLAY_H
#include "SixPiece.h"
#include "SixInitialize.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/filewritestream.h"
#include <windows.h>
#include <mutex>
class SelfPlay:public SixPiece
{
public:
    void WriteData(const std::shared_ptr<TrainPiectElement> board,string path,int sleep_time);
    void writeToJsonFile(string filepath,const std::shared_ptr<TrainPiectElement> board);
    string readfile(string path);
    string MakeIterateData(const std::shared_ptr<TrainPiectElement> board);
    void ParseIteratrDate(std::shared_ptr<TrainPiectElement> board,string &str);
    bool IsConfigEmpty(string path);
    void ReadData(string filepath,const std::shared_ptr<TrainPiectElement> board);
    void Train();
    std::shared_ptr<TrainPiectElement> MakeTestData(SixPiece &test);
};
#endif //GENETIC_SIXSELFPLAY_H
