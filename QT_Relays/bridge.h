#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QMqttClient>

class Bridge : public QObject
{
    Q_OBJECT
public:
    explicit Bridge(QObject *parent = nullptr);

private:
    QMqttClient *m_ClientMqtt;

signals:
    void changedDin1(QString value);
    void changedDin2(QString value);
    void changedDin3(QString value);
    void changedDin4(QString value);
    void changedRelay1(QString value);
    void changedRelay2(QString value);
    void changedRelay3(QString value);
    void changedRelay4(QString value);
    void changedRelay5(QString value);
    void changedRelay6(QString value);
    void changedRelay7(QString value);
    void changedRelay8(QString value);
    void changedRelay9(QString value);
    void changedRelay10(QString value);
    void changedRelay11(QString value);
    void changedRelay12(QString value);


public slots:
    void mqttConnected();
    void mqttDisconnected();
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void setRelay(int relay, QString status);
};

#endif // BRIDGE_H
