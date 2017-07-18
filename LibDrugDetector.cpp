#include "LibDrugDetector.h"


LibDrugDetector::LibDrugDetector()
{
    m_iIndexCount = 0;
    // 二维码模拟定时
    m_pQRCodeInfoTimer = new QTimer();
    m_pQRCodeInfoTimer->setInterval(1000);
    m_pQRCodeInfoTimer->setSingleShot(true);
    connect(m_pQRCodeInfoTimer, SIGNAL(timeout()), this, SLOT(_SlotUpdataQRCodeTimer()));
    // 测试值定时器
    m_pTestResultTimer = new QTimer();
    m_pTestResultTimer->setInterval(100);
    connect(m_pTestResultTimer, SIGNAL(timeout()), this, SLOT(_SlotUpdataTestTimer()));
}
// 发送二维码
void LibDrugDetector::_SlotUpdataQRCodeTimer()
{
    _SendQRCodeInfo();
}
// 发送测试结果
void LibDrugDetector::_SlotUpdataTestTimer()
{
    _SendTestResultData();
}
// 测试，发送结束
void LibDrugDetector::UIEndTest()
{
    emit SignalEndTest();
}
// test 计时器
void LibDrugDetector::UIBeginTest()
{
    m_pQRCodeInfoTimer->start();
    m_pTestResultTimer->start();
}
// 二维码结构体数据demo
void LibDrugDetector::_SendQRCodeInfo()
{
    QRCodeInfo qRCodeInfo;
    qRCodeInfo.iProductID = 1001;
    qRCodeInfo.iProductLot = 1002;
    qRCodeInfo.iProgramCount = 12;
    qRCodeInfo.qExprationDate = QDate::currentDate();
    //
    QVariant qVariantData;
    qVariantData.setValue(qRCodeInfo);
    emit SignalSendQRCodeInfo(qVariantData);
}
// 结果结构体demo
void LibDrugDetector::_SendTestResultData()
{
    if(m_iIndexCount > 11)
    {
        emit SignalEndTest();
        m_pTestResultTimer->stop();
        return;
    }
    ++m_iIndexCount;
    // 发送结构体数据demo
    TestResultData testResultData;
    testResultData.iCutoffValue = 200 + m_iIndexCount;
    testResultData.iCValue =  3 + m_iIndexCount;
    testResultData.iTValue = 4 + m_iIndexCount;
    testResultData.strControlLine = "";
    testResultData.strProgramName = "program_name" + QString::number(m_iIndexCount);
    testResultData.strResult = "result" + QString::number(m_iIndexCount);
    //
    QVariant qVariantData;
    qVariantData.setValue(testResultData);
    emit SignalSendTestResultData(qVariantData);
}

void LibDrugDetector::_SendEndTest()
{
    emit SignalEndTest();
}
