#include "../Header/bringinstructions.h"

BringInstructions::BringInstructions()
{
    file.setFileName(":/Data/intelx86.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Dosya açılamadı: " << file.errorString();
                                           return;
    }

    // JSON verisini QJsonDocument kullanarak oku
    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);

    // JSON verisini QJsonObject'a çevir
    if (jsonDocument.isNull()) {
        qDebug() << "JSON belgesi geçersiz.";
            return;
    }

    if (!jsonDocument.isObject()) {
        qDebug() << "JSON belgesi bir nesne içermiyor.";
            return;
    }
    QJsonObject jsonObject = jsonDocument.object();
    instructionsArray = jsonObject["instructions"].toArray();

}
BringInstructions::~BringInstructions(){
    file.close();
}
QList<QJsonObject> BringInstructions::getInstructions(InstructionPrefixes * instructionPrefixes){
    QList<QJsonObject> matchingInstructions;
    bool ok;
    for (const auto& jsonValue : instructionsArray) {
        if (jsonValue.isObject()) {
            QJsonObject instructionObject = jsonValue.toObject();
            // Aradığınız özelliklere göre filtreleme
            QString prefix0F = instructionObject["Prefix0F"].toString();
            QString primaryOpcode = instructionObject["PrimaryOpcode"].toString();
            // İstediğiniz koşullara göre filtreleme
            if (prefix0F.toUInt(&ok,16)==instructionPrefixes->Prefix0F && primaryOpcode.toUInt(&ok,16)==instructionPrefixes->PrimaryOpcode){// && secondaryOpcode.toInt()==instructionPrefixes->SecondaryOpcode) {
                // Eşleşen veriyi listeye ekle
                matchingInstructions.append(instructionObject);
            }
        }
    }
    return matchingInstructions;
}
