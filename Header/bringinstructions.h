#ifndef BRINGINSTRUCTIONS_H
#define BRINGINSTRUCTIONS_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <Header/define.h>

class BringInstructions
{
public:
    BringInstructions();
    ~BringInstructions();
    QFile file;
    QList<QJsonObject> matchingInstructions;
    QJsonArray instructionsArray;
    QList<QJsonObject> getInstructions(InstructionPrefixes * instructionPrefixes);

};

#endif // BRINGINSTRUCTIONS_H
