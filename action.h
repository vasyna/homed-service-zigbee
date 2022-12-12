#ifndef ACTION_H
#define ACTION_H

#include <QSharedPointer>
#include <QVariant>
#include "zcl.h"

class ActionObject;
typedef QSharedPointer <ActionObject> Action;

class ActionObject
{

public:

    ActionObject(const QString &name, quint16 clusterId, quint16 manufacturerCode, quint16 attributeId) :
        m_name(name), m_clusterId(clusterId), m_manufacturerCode(manufacturerCode), m_attributes({attributeId}), m_transactionId(0) {}

    ActionObject(const QString &name, quint16 clusterId, quint16 manufacturerCode = 0, QList <quint16> attributes = {}) :
        m_name(name), m_clusterId(clusterId), m_manufacturerCode(manufacturerCode), m_attributes(attributes), m_transactionId(0) {}

    virtual ~ActionObject(void) {}
    virtual QByteArray request(const QVariant &data) = 0;

    inline QString name(void) { return m_name; }
    inline quint16 clusterId(void) { return m_clusterId; }
    inline quint16 manufacturerCode(void) { return m_manufacturerCode; }
    inline QList <quint16> &attributes(void) { return m_attributes; }
    inline void setParent(QObject *value) { m_parent = value; }

    static void registerMetaTypes(void);

protected:

    QString m_name;
    quint16 m_clusterId, m_manufacturerCode;
    QList <quint16> m_attributes;

    QObject *m_parent;
    quint8 m_transactionId;

    QVariant deviceOption(const QString &key);

};

namespace Actions
{
    class Status : public ActionObject
    {

    public:

        Status(void) : ActionObject("status", CLUSTER_ON_OFF, 0x0000, 0x0000) {}
        QByteArray request(const QVariant &data) override;

    };

    class PowerOnStatus : public ActionObject
    {

    public:

        PowerOnStatus(void) : ActionObject("powerOnStatus", CLUSTER_ON_OFF, 0x0000, 0x4003) {}
        QByteArray request(const QVariant &data) override;

    };

    class Level : public ActionObject
    {

    public:

        Level(void) : ActionObject("level", CLUSTER_LEVEL_CONTROL, 0x0000, 0x0000) {}
        QByteArray request(const QVariant &data) override;

    };

    class ColorHS : public ActionObject
    {

    public:

        ColorHS(void) : ActionObject("color", CLUSTER_COLOR_CONTROL, 0x0000, {0x0000, 0x0001}) {}
        QByteArray request(const QVariant &data) override;

    };

    class ColorXY : public ActionObject
    {

    public:

        ColorXY(void) : ActionObject("color", CLUSTER_COLOR_CONTROL, 0x0000, {0x0003, 0x0004}) {}
        QByteArray request(const QVariant &data) override;

    };

    class ColorTemperature : public ActionObject
    {

    public:

        ColorTemperature(void) : ActionObject("colorTemperature", CLUSTER_COLOR_CONTROL, 0x0000, 0x0007) {}
        QByteArray request(const QVariant &data) override;

    };
}

namespace ActionsPTVO
{
    class Status : public ActionObject
    {

    public:

        Status(const QString &name) : ActionObject(name, CLUSTER_ON_OFF, 0x0000, 0x0000) {}
        QByteArray request(const QVariant &data) override;

    };

    class AnalogInput : public ActionObject
    {

    public:

        AnalogInput(const QString &name) : ActionObject(name, CLUSTER_ANALOG_INPUT, 0x0000, 0x0055) {}
        QByteArray request(const QVariant &data) override;

    };

    class ChangePattern : public Status
    {

    public:

        ChangePattern(void) : Status("changePattern") {}

    };

    class Count : public AnalogInput
    {

    public:

        Count(void) : AnalogInput("count") {}

    };

    class Pattern : public AnalogInput
    {

    public:

        Pattern(void) : AnalogInput("pattern") {}

    };
}

namespace ActionsLUMI
{
    class CoverPosition : public ActionObject
    {

    public:

        CoverPosition(void) : ActionObject("position", CLUSTER_ANALOG_OUTPUT, 0x115F, 0x0055) {}
        QByteArray request(const QVariant &data) override;

    };

    class OperationMode : public ActionObject
    {

    public:

        OperationMode(void) : ActionObject("mode", CLUSTER_LUMI, 0x115F, 0x0009) {}
        QByteArray request(const QVariant &data) override;

    };

    class Sensitivity : public ActionObject
    {

    public:

        Sensitivity(void) : ActionObject("sensitivity", CLUSTER_LUMI, 0x115F, 0x010C) {}
        QByteArray request(const QVariant &data) override;

    };

    class DetectionMode : public ActionObject
    {

    public:

        DetectionMode(void) : ActionObject("mode", CLUSTER_LUMI, 0x115F, 0x0144) {}
        QByteArray request(const QVariant &data) override;

    };

    class Distance : public ActionObject
    {

    public:

        Distance(void) : ActionObject("distance", CLUSTER_LUMI, 0x115F, 0x0146) {}
        QByteArray request(const QVariant &data) override;

    };

    class ResetPresence : public ActionObject
    {

    public:

        ResetPresence(void) : ActionObject("resetPresence", CLUSTER_LUMI, 0x115F) {}
        QByteArray request(const QVariant &data) override;

    };
}

namespace ActionsTUYA
{
    class Request
    {

    protected:

        QByteArray makeRequest(quint8 transactionId, quint8 dataPoint, quint8 dataType, void *data);

    };

    class Volume : public Request, public ActionObject
    {

    public:

        Volume(void) : ActionObject("volume", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class Duration : public Request, public ActionObject
    {

    public:

        Duration(void) : ActionObject("duration", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class Alarm : public Request, public ActionObject
    {

    public:

        Alarm(void) : ActionObject("alarm", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class Melody : public Request, public ActionObject
    {

    public:

        Melody(void) : ActionObject("melody", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class Sensitivity : public Request, public ActionObject
    {

    public:

        Sensitivity(void) : ActionObject("sensitivity", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class DistanceMin :  public Request, public ActionObject
    {

    public:

        DistanceMin(void) : ActionObject("distanceMin", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class DistanceMax :  public Request, public ActionObject
    {

    public:

        DistanceMax(void) : ActionObject("distanceMax", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class DetectionDelay : public Request, public ActionObject
    {

    public:

        DetectionDelay(void) : ActionObject("detectionDelay", CLUSTER_TUYA_DATA) {}
        QByteArray request(const QVariant &data) override;

    };

    class ChildLock : public ActionObject
    {

    public:

        ChildLock(void) : ActionObject("childLock", CLUSTER_ON_OFF, 0x0000, 0x8000) {}
        QByteArray request(const QVariant &data) override;

    };

    class BacklightMode : public ActionObject
    {

    public:

        BacklightMode(void) : ActionObject("backlightMode", CLUSTER_ON_OFF, 0x0000, 0x8001) {}
        QByteArray request(const QVariant &data) override;

    };

    class IndicatorMode : public ActionObject
    {

    public:

        IndicatorMode(void) : ActionObject("indicatorMode", CLUSTER_ON_OFF, 0x0000, 0x8001) {}
        QByteArray request(const QVariant &data) override;

    };

    class SwitchMode : public ActionObject
    {

    public:

        SwitchMode(void) : ActionObject("switchMode", CLUSTER_TUYA_SWITCH_MODE, 0x0000, 0xD030) {}
        QByteArray request(const QVariant &data) override;

    };

    class PowerOnStatus : public ActionObject
    {

    public:

        PowerOnStatus(void) : ActionObject("powerOnStatus", CLUSTER_ON_OFF, 0x0000, 0x8002) {}
        QByteArray request(const QVariant &data) override;

    };
}

namespace ActionsPerenio
{
    class PowerOnStatus : public ActionObject
    {

    public:

        PowerOnStatus(void) : ActionObject("powerOnStatus", CLUSTER_PERENIO, 0x0000, 0x0000) {}
        QByteArray request(const QVariant &data) override;

    };

    class ResetAlarms : public ActionObject
    {

    public:

        ResetAlarms(void) : ActionObject("resetAlarms", CLUSTER_PERENIO, 0x0000, 0x0001) {}
        QByteArray request(const QVariant &data) override;

    };

    class VoltageMin : public ActionObject
    {

    public:

        VoltageMin(void) : ActionObject("voltageMin", CLUSTER_PERENIO, 0x0000, 0x0004) {}
        QByteArray request(const QVariant &data) override;

    };

    class VoltageMax : public ActionObject
    {

    public:

        VoltageMax(void) : ActionObject("voltageMax", CLUSTER_PERENIO, 0x0000, 0x0005) {}
        QByteArray request(const QVariant &data) override;

    };

    class PowerMax : public ActionObject
    {

    public:

        PowerMax(void) : ActionObject("powerMax", CLUSTER_PERENIO, 0x0000, 0x000B) {}
        QByteArray request(const QVariant &data) override;

    };

    class EnergyLimit : public ActionObject
    {

    public:

        EnergyLimit(void) : ActionObject("energyLimit", CLUSTER_PERENIO, 0x0000, 0x000F) {}
        QByteArray request(const QVariant &data) override;

    };
}

#endif
