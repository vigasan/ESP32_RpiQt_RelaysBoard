#include "bridge.h"

Bridge::Bridge(QObject *parent) : QObject(parent)
{
    m_ClientMqtt = new QMqttClient(this);
    m_ClientMqtt->setHostname("192.168.1.25"); 	// MQTT Server IP, same of Home Assistant
    m_ClientMqtt->setUsername("mqttuser");    	// MQTT Server User Name
    m_ClientMqtt->setPassword("mqttpsw");       // MQTT Server password
    m_ClientMqtt->setPort(1883);               	// MQTT Server Port
    m_ClientMqtt->setClientId("RaspDisplay");  	// MQTT Client NAme

    QObject::connect(m_ClientMqtt, SIGNAL(connected()), this, SLOT(mqttConnected()));
    QObject::connect(m_ClientMqtt, SIGNAL(disconnected()), this, SLOT(mqttDisconnected()));
    QObject::connect(m_ClientMqtt, SIGNAL(messageReceived(const QByteArray, const QMqttTopicName)), this, SLOT(onMessageReceived(const QByteArray, const QMqttTopicName)));

    m_ClientMqtt->connectToHost();
}


void Bridge::mqttConnected()
{
    qDebug() << "MQTT - Connected!!!";
    QMqttTopicFilter relay1_state{"CustomRelays/relay1/state"};
    QMqttTopicFilter relay2_state{"CustomRelays/relay2/state"};
    QMqttTopicFilter relay3_state{"CustomRelays/relay3/state"};
    QMqttTopicFilter relay4_state{"CustomRelays/relay4/state"};
    QMqttTopicFilter relay5_state{"CustomRelays/relay5/state"};
    QMqttTopicFilter relay6_state{"CustomRelays/relay6/state"};
    QMqttTopicFilter relay7_state{"CustomRelays/relay7/state"};
    QMqttTopicFilter relay8_state{"CustomRelays/relay8/state"};
    QMqttTopicFilter relay9_state{"CustomRelays/relay9/state"};
    QMqttTopicFilter relay10_state{"CustomRelays/relay10/state"};
    QMqttTopicFilter relay11_state{"CustomRelays/relay11/state"};
    QMqttTopicFilter relay12_state{"CustomRelays/relay12/state"};

    QMqttTopicFilter digIn1_state{"CustomRelays/din1/state"};
    QMqttTopicFilter digIn2_state{"CustomRelays/din2/state"};
    QMqttTopicFilter digIn3_state{"CustomRelays/din3/state"};
    QMqttTopicFilter digIn4_state{"CustomRelays/din4/state"};

    m_ClientMqtt->subscribe(relay1_state);
    m_ClientMqtt->subscribe(relay2_state);
    m_ClientMqtt->subscribe(relay3_state);
    m_ClientMqtt->subscribe(relay4_state);
    m_ClientMqtt->subscribe(relay5_state);
    m_ClientMqtt->subscribe(relay6_state);
    m_ClientMqtt->subscribe(relay7_state);
    m_ClientMqtt->subscribe(relay8_state);
    m_ClientMqtt->subscribe(relay9_state);
    m_ClientMqtt->subscribe(relay10_state);
    m_ClientMqtt->subscribe(relay11_state);
    m_ClientMqtt->subscribe(relay12_state);

    m_ClientMqtt->subscribe(digIn1_state);
    m_ClientMqtt->subscribe(digIn2_state);
    m_ClientMqtt->subscribe(digIn3_state);
    m_ClientMqtt->subscribe(digIn4_state);
}

void Bridge::mqttDisconnected()
{
    qDebug() << "MQTT - Disconnected";
}

void Bridge::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    QString content = topic.name();

    QString payload = QString(message);

    qDebug() << "Received: " << content << " - " << payload;

    if(content == "CustomRelays/relay1/state")
        emit changedRelay1(payload.toLower());

    if(content == "CustomRelays/relay2/state")
        emit changedRelay2(payload.toLower());

    if(content == "CustomRelays/relay3/state")
        emit changedRelay3(payload.toLower());

    if(content == "CustomRelays/relay4/state")
        emit changedRelay4(payload.toLower());

    if(content == "CustomRelays/relay5/state")
        emit changedRelay5(payload.toLower());

    if(content == "CustomRelays/relay6/state")
        emit changedRelay6(payload.toLower());

    if(content == "CustomRelays/relay7/state")
        emit changedRelay7(payload.toLower());

    if(content == "CustomRelays/relay8/state")
        emit changedRelay8(payload.toLower());

    if(content == "CustomRelays/relay9/state")
        emit changedRelay9(payload.toLower());

    if(content == "CustomRelays/relay10/state")
        emit changedRelay10(payload.toLower());

    if(content == "CustomRelays/relay11/state")
        emit changedRelay11(payload.toLower());

    if(content == "CustomRelays/relay12/state")
        emit changedRelay12(payload.toLower());


    if(content == "CustomRelays/din1/state")
        emit changedDin1(payload.toLower());

    if(content == "CustomRelays/din2/state")
        emit changedDin2(payload.toLower());

    if(content == "CustomRelays/din3/state")
        emit changedDin3(payload.toLower());

    if(content == "CustomRelays/din4/state")
        emit changedDin4(payload.toLower());

}

void Bridge::setRelay(int relay, QString status)
{
    switch(relay)
    {
        case 1:
        {
            QMqttTopicName topic{"CustomRelays/relay1/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 2:
        {
            QMqttTopicName topic{"CustomRelays/relay2/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 3:
        {
            QMqttTopicName topic{"CustomRelays/relay3/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 4:
        {
            QMqttTopicName topic{"CustomRelays/relay4/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 5:
        {
            QMqttTopicName topic{"CustomRelays/relay5/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 6:
        {
            QMqttTopicName topic{"CustomRelays/relay6/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 7:
        {
            QMqttTopicName topic{"CustomRelays/relay7/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 8:
        {
            QMqttTopicName topic{"CustomRelays/relay8/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 9:
        {
            QMqttTopicName topic{"CustomRelays/relay9/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 10:
        {
            QMqttTopicName topic{"CustomRelays/relay10/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 11:
        {
            QMqttTopicName topic{"CustomRelays/relay11/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;

        case 12:
        {
            QMqttTopicName topic{"CustomRelays/relay12/set"};
            m_ClientMqtt->publish(topic, status.toUtf8());
        } break;
    }
}

