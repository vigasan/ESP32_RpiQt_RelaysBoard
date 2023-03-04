/**************************************************************************************************************************************************
* File name     : ESP32CustomRelays.ino
* Compiler      : 
* Autor         : VIGASAN   
* Created       : 02/03/2023
* Modified      : 
* Last modified :
*
*
* Description   : 
*
* Other info    : Custom ESP32 Relays Board
**************************************************************************************************************************************************/

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------Include Files----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------  Constants  ----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
#define UNPRESSED                       0
#define DEBOUNCE                        1
#define PRESSED                         2

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------I/O Definitions--------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
const int IN_DIN1 = 34;
const int IN_DIN2 = 35;
const int IN_DIN3 = 5;
const int IN_DIN4 = 4;
const int OUT_RELAY1 = 32;
const int OUT_RELAY2 = 33;
const int OUT_RELAY3 = 25;
const int OUT_RELAY4 = 26;
const int OUT_RELAY5 = 27;
const int OUT_RELAY6 = 14;
const int OUT_RELAY7 = 13;
const int OUT_RELAY8 = 15;
const int OUT_RELAY9 = 16;
const int OUT_RELAY10 = 18;
const int OUT_RELAY11 = 19;
const int OUT_RELAY12 = 21;
const int OUT_STATUS_LED = 17;

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------MQTT DISCOVERY PARAMETERS----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
const char* g_ssid = "your Wifi Name";                              // Wifi Name
const char* g_password = "Wifi Password";                           // Wifi Password
const char* g_mqtt_server = "192.168.1.25";                         // MQTT Server IP, same of Home Assistant
const char* g_mqttUser = "mqttUser";                                // MQTT Server User Name
const char* g_mqttPsw = "password";                                 // MQTT Server password
int         g_mqttPort = 1883;                                      // MQTT Server Port
const char* g_mqtt_DeviceName = "CustomRelays";          // Device Name for Home Assistant

String      g_TopicRelay1 = "CustomRelays/relay1";       // Topic for entity relay1
String      g_TopicRelay2 = "CustomRelays/relay2";       // Topic for entity relay2
String      g_TopicRelay3 = "CustomRelays/relay3";       // Topic for entity relay3
String      g_TopicRelay4 = "CustomRelays/relay4";       // Topic for entity relay4
String      g_TopicRelay5 = "CustomRelays/relay5";       // Topic for entity relay5
String      g_TopicRelay6 = "CustomRelays/relay6";       // Topic for entity relay6
String      g_TopicRelay7 = "CustomRelays/relay7";       // Topic for entity relay7
String      g_TopicRelay8 = "CustomRelays/relay8";       // Topic for entity relay8
String      g_TopicRelay9 = "CustomRelays/relay9";       // Topic for entity relay9
String      g_TopicRelay10 = "CustomRelays/relay10";     // Topic for entity relay10
String      g_TopicRelay11 = "CustomRelays/relay11";     // Topic for entity relay11
String      g_TopicRelay12 = "CustomRelays/relay12";     // Topic for entity relay12

String      g_TopicState_din1 = "CustomRelays/din1/state";   // State Topic for entity input din1
String      g_TopicState_din2 = "CustomRelays/din2/state";   // State Topic for entity input din2
String      g_TopicState_din3 = "CustomRelays/din3/state";   // State Topic for entity input din3
String      g_TopicState_din4 = "CustomRelays/din4/state";   // State Topic for entity input din4

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------Global variables-------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
WiFiClient          g_WiFiClient;
PubSubClient        g_mqttPubSub(g_WiFiClient);
int                 g_mqttCounterConn = 0;
unsigned long       g_TimeInputs = 0;
unsigned long       g_TimeLed = 0;
String              g_UniqueId;
bool                g_InitSystem = true;
int                 g_canPublish = 0;
byte                g_Input1 = 0;
byte                g_Input2 = 0;
byte                g_Input3 = 0;
byte                g_Input4 = 0;
byte                g_RelayStatus1 = 0;
byte                g_RelayStatus2 = 0;
byte                g_RelayStatus3 = 0;
byte                g_RelayStatus4 = 0;
byte                g_RelayStatus5 = 0;
byte                g_RelayStatus6 = 0;
byte                g_RelayStatus7 = 0;
byte                g_RelayStatus8 = 0;
byte                g_RelayStatus9 = 0;
byte                g_RelayStatus10 = 0;
byte                g_RelayStatus11 = 0;
byte                g_RelayStatus12 = 0;
byte                g_st_input1 = UNPRESSED;
byte                g_st_input2 = UNPRESSED;
byte                g_st_input3 = UNPRESSED;
byte                g_st_input4 = UNPRESSED;

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------ SETUP ----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
void setup() 
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // I/O Configuration
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pinMode(OUT_STATUS_LED, OUTPUT);
    pinMode(IN_DIN1, INPUT);
    pinMode(IN_DIN2, INPUT);
    pinMode(IN_DIN3, INPUT);
    pinMode(IN_DIN4, INPUT);
    pinMode(OUT_RELAY1, OUTPUT);
    pinMode(OUT_RELAY2, OUTPUT);
    pinMode(OUT_RELAY3, OUTPUT);
    pinMode(OUT_RELAY4, OUTPUT);
    pinMode(OUT_RELAY5, OUTPUT);
    pinMode(OUT_RELAY6, OUTPUT);
    pinMode(OUT_RELAY7, OUTPUT);
    pinMode(OUT_RELAY8, OUTPUT);
    pinMode(OUT_RELAY9, OUTPUT);
    pinMode(OUT_RELAY10, OUTPUT);
    pinMode(OUT_RELAY11, OUTPUT);
    pinMode(OUT_RELAY12, OUTPUT);

    
    Serial.begin(115200);
    delay(500); 
    Serial.println("");
    Serial.println("");
    Serial.println("-------- ESP32 RELAYS ----------");
   
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Wifi Init
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    setup_wifi();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MQTT Init
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    g_mqttPubSub.setServer(g_mqtt_server, g_mqttPort);
    g_mqttPubSub.setCallback(MqttReceiverCallback);
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------ LOOP -----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
void loop() 
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MQTT Connection
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(WiFi.status() == WL_CONNECTED)
    {
        if(!g_mqttPubSub.connected())
            MqttReconnect();
        else
            g_mqttPubSub.loop();
    } else
    {
        Serial.println("WiFi NOT connected!!!");
        setup_wifi();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MQTT Discovery Init
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(g_InitSystem)
    {
        delay(1000);
        g_InitSystem = false;
        Serial.println("INIT SYSTEM...");
        MqttHomeAssistantDiscovery();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Inputs Monitor
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(millis() - g_TimeInputs > 200)
    {
        g_TimeInputs = millis();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Inputs 1
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        switch(g_st_input1)
        {
            case UNPRESSED:
            {
                if(digitalRead(IN_DIN1) == 0)            
                {
                    g_st_input1 = DEBOUNCE;
                }
            } break;
    
            case DEBOUNCE:
            {
                if(digitalRead(IN_DIN1) == 0)           
                {
                    g_st_input1 = PRESSED;
                    g_Input1 = 1;                       
                } else                                  
                {
                    g_st_input1 = UNPRESSED;
                    g_Input1 = 0;                       
                }
                MqttPublishStatus_dIn1();
            } break;
    
            case PRESSED:
            {
                if(digitalRead(IN_DIN1) == 1)
                {
                    g_st_input1 = DEBOUNCE;
                }
            } break;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Inputs 2
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        switch(g_st_input2)
        {
            case UNPRESSED:
            {
                if(digitalRead(IN_DIN2) == 0)
                {
                    g_st_input2 = DEBOUNCE;
                }
            } break;
    
            case DEBOUNCE:
            {
                if(digitalRead(IN_DIN2) == 0)
                {
                    g_st_input2 = PRESSED;
                    g_Input2 = 1; 
                   
                } else                                  
                {
                    g_st_input2 = UNPRESSED;
                    g_Input2 = 0;  
                }
                MqttPublishStatus_dIn2();
            } break;
    
            case PRESSED:
            {
                if(digitalRead(IN_DIN2) == 1)  
                {
                    g_st_input2 = DEBOUNCE;
                }
            } break;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Inputs 3
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        switch(g_st_input3)
        {
            case UNPRESSED:
            {
                if(digitalRead(IN_DIN3) == 0)  
                {
                    g_st_input3 = DEBOUNCE;
                }
            } break;
    
            case DEBOUNCE:
            {
                if(digitalRead(IN_DIN3) == 0)  
                {
                    g_st_input3 = PRESSED;
                    g_Input3 = 1;         
                   
                } else                                  
                {
                    g_st_input3 = UNPRESSED;
                    g_Input3 = 0;     
                }
                MqttPublishStatus_dIn3();
            } break;
    
            case PRESSED:
            {
                if(digitalRead(IN_DIN3) == 1)  
                {
                    g_st_input3 = DEBOUNCE;
                }
            } break;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Inputs 4
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        switch(g_st_input4)
        {
            case UNPRESSED:
            {
                if(digitalRead(IN_DIN4) == 0)  
                {
                    g_st_input4 = DEBOUNCE;
                }
            } break;
    
            case DEBOUNCE:
            {
                if(digitalRead(IN_DIN4) == 0)   
                {
                    g_st_input4 = PRESSED;
                    g_Input4 = 1;       
                   
                } else                                  
                {
                    g_st_input4 = UNPRESSED;
                    g_Input4 = 0;          
                }
                MqttPublishStatus_dIn4();
            } break;
    
            case PRESSED:
            {
                if(digitalRead(IN_DIN4) == 1)      
                {
                    g_st_input4 = DEBOUNCE;
                }
            } break;
        }
    }

    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Status Led
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(millis() - g_TimeLed > 500)
    {
        g_TimeLed = millis();
        digitalWrite(OUT_STATUS_LED, !digitalRead(OUT_STATUS_LED));
    }
 
}


/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------ Public Functions -----------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

void setup_wifi() 
{
    int counter = 0;
    byte mac[6];
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(g_ssid);

    WiFi.begin(g_ssid, g_password);

    WiFi.macAddress(mac);
    g_UniqueId =  String(mac[0],HEX) +String(mac[1],HEX) +String(mac[2],HEX) +String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);

    Serial.print("Unique ID: ");
    Serial.println(g_UniqueId); 
    
    while(WiFi.status() != WL_CONNECTED && counter++ < 5) 
    {
        delay(500);
        Serial.print(".");
    }

    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else
    {
        Serial.println("WiFi NOT connected!!!");
    }
}

void MqttReconnect() 
{
    // Loop until we're MqttReconnected
    while (!g_mqttPubSub.connected()  && (g_mqttCounterConn++ < 4))
    {
        Serial.print("Attempting MQTT connection...");
        if (g_mqttPubSub.connect(g_mqtt_DeviceName, g_mqttUser, g_mqttPsw)) 
        {
            Serial.println("connected");
            //ESP32 Subscribe following topics
            g_mqttPubSub.subscribe((g_TopicRelay1 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay2 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay3 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay4 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay5 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay6 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay7 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay8 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay9 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay10 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay11 + "/set").c_str());
            g_mqttPubSub.subscribe((g_TopicRelay12 + "/set").c_str());
            delay(500);
        } else 
        {
            Serial.print("failed, rc=");
            Serial.print(g_mqttPubSub.state());
            Serial.println(" try again in 3 seconds");
            delay(3000);
        }
    }  
    g_mqttCounterConn = 0;
}

void MqttHomeAssistantDiscovery()
{
    String discoveryTopic;
    String payload;
    String strPayload;
    
    if(g_mqttPubSub.connected())
    {
        Serial.println("SEND HOME ASSISTANT DISCOVERY!!!");
        StaticJsonDocument<600> payload;
        JsonObject device;
        JsonArray identifiers;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 1
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay1/config";      // Discovery Topic for entity relay1

        payload["name"] = "CustomRelays.relay1";                 
        payload["uniq_id"] = g_UniqueId + "_relay1";                                                          
        payload["stat_t"] = g_TopicRelay1 + "/state";    
        payload["cmd_t"] = g_TopicRelay1 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 2
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay2/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay2";                 
        payload["uniq_id"] = g_UniqueId + "_relay2";                                                          
        payload["stat_t"] = g_TopicRelay2 + "/state";    
        payload["cmd_t"] = g_TopicRelay2 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 3
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay3/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay3";                 
        payload["uniq_id"] = g_UniqueId + "_relay3";                                                          
        payload["stat_t"] = g_TopicRelay3 + "/state";    
        payload["cmd_t"] = g_TopicRelay3 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 4
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay4/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay4";                 
        payload["uniq_id"] = g_UniqueId + "_relay4";                                                          
        payload["stat_t"] = g_TopicRelay4 + "/state";    
        payload["cmd_t"] = g_TopicRelay4 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 5
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay5/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay5";                 
        payload["uniq_id"] = g_UniqueId + "_relay5";                                                          
        payload["stat_t"] = g_TopicRelay5 + "/state";    
        payload["cmd_t"] = g_TopicRelay5 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 6
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay6/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay6";                 
        payload["uniq_id"] = g_UniqueId + "_relay6";                                                          
        payload["stat_t"] = g_TopicRelay6 + "/state";    
        payload["cmd_t"] = g_TopicRelay6 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 7
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay7/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay7";                 
        payload["uniq_id"] = g_UniqueId + "_relay7";                                                          
        payload["stat_t"] = g_TopicRelay7 + "/state";    
        payload["cmd_t"] = g_TopicRelay7 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 8
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay8/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay8";                 
        payload["uniq_id"] = g_UniqueId + "_relay8";                                                          
        payload["stat_t"] = g_TopicRelay8 + "/state";    
        payload["cmd_t"] = g_TopicRelay8 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 9
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay9/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay9";                 
        payload["uniq_id"] = g_UniqueId + "_relay9";                                                          
        payload["stat_t"] = g_TopicRelay9 + "/state";    
        payload["cmd_t"] = g_TopicRelay9 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 10
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay10/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay10";                 
        payload["uniq_id"] = g_UniqueId + "_relay10";                                                          
        payload["stat_t"] = g_TopicRelay10 + "/state";    
        payload["cmd_t"] = g_TopicRelay10 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 11
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay11/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay11";                 
        payload["uniq_id"] = g_UniqueId + "_relay11";                                                          
        payload["stat_t"] = g_TopicRelay11 + "/state";    
        payload["cmd_t"] = g_TopicRelay11 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relay 12
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/switch/relay12/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.relay12";                 
        payload["uniq_id"] = g_UniqueId + "_relay12";                                                          
        payload["stat_t"] = g_TopicRelay12 + "/state";    
        payload["cmd_t"] = g_TopicRelay12 + "/set"; 
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Digital Input 1
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/binary_sensor/din1/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.din1";      
        payload["uniq_id"] = g_UniqueId + "_din1";
        payload["stat_t"] = g_TopicState_din1;
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Digital Input 2
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/binary_sensor/din2/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.din2";      
        payload["uniq_id"] = g_UniqueId + "_din2";
        payload["stat_t"] = g_TopicState_din2;
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Digital Input 3
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/binary_sensor/din3/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.din3";      
        payload["uniq_id"] = g_UniqueId + "_din3";
        payload["stat_t"] = g_TopicState_din3;
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Digital Input 4
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        discoveryTopic = "homeassistant/binary_sensor/din4/config";
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();

        payload["name"] = "CustomRelays.din4";      
        payload["uniq_id"] = g_UniqueId + "_din4";
        payload["stat_t"] = g_TopicState_din4;
        device = payload.createNestedObject("device");
        device["name"] = g_mqtt_DeviceName;
        device["model"] = "CustomRelays_RevA";
        device["manufacturer"] = "Vigasan";
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(g_UniqueId);
        
        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        g_mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

        // Send Current status of Relays and Inputs 
        MqttPublishStatus_Relay1();
        MqttPublishStatus_Relay2();
        MqttPublishStatus_Relay3();
        MqttPublishStatus_Relay4();
        MqttPublishStatus_Relay5();
        MqttPublishStatus_Relay6();
        MqttPublishStatus_Relay7();
        MqttPublishStatus_Relay8();
        MqttPublishStatus_Relay9();
        MqttPublishStatus_Relay10();
        MqttPublishStatus_Relay11();
        MqttPublishStatus_Relay12();

        MqttPublishStatus_dIn1();
        MqttPublishStatus_dIn2();
        MqttPublishStatus_dIn3();
        MqttPublishStatus_dIn4();
    }
}

void MqttReceiverCallback(char* topic, byte* inFrame, unsigned int length) 
{
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    byte state = 0;
    String payload;
    String topicMsg;
    
    for (int i = 0; i < length; i++) 
    {
        Serial.print((char)inFrame[i]);
        payload += (char)inFrame[i];
    }
    Serial.println();

    if(payload == "ON") 
        state = 1;
    else if(payload == "OFF") 
        state = 0;

    if(String(topic) == String("homeassistant/status")) 
    {
        if(payload == "online")
        {
            MqttHomeAssistantDiscovery();
        }
    }
    
    if(String(topic) == String(g_TopicRelay1 + "/set")) 
    {
        g_RelayStatus1 = state;
        digitalWrite(OUT_RELAY1, state);
        MqttPublishStatus_Relay1();
    }

    if(String(topic) == String(g_TopicRelay2 + "/set")) 
    {
        g_RelayStatus2 = state;
        digitalWrite(OUT_RELAY2, state);
        MqttPublishStatus_Relay2();
    }
    
    if(String(topic) == String(g_TopicRelay3 + "/set")) 
    {
        g_RelayStatus3 = state;
        digitalWrite(OUT_RELAY3, state);
        MqttPublishStatus_Relay3();
    }
        
    if(String(topic) == String(g_TopicRelay4 + "/set")) 
    {
        g_RelayStatus4 = state;
        digitalWrite(OUT_RELAY4, state);
        MqttPublishStatus_Relay4();
    }
        
    if(String(topic) == String(g_TopicRelay5 + "/set")) 
    {
        g_RelayStatus5 = state;
        digitalWrite(OUT_RELAY5, state);
        MqttPublishStatus_Relay5();
    }
        
    if(String(topic) == String(g_TopicRelay6 + "/set"))  
    {
        g_RelayStatus6 = state;
        digitalWrite(OUT_RELAY6, state);
        MqttPublishStatus_Relay6();
    }
        
    if(String(topic) == String(g_TopicRelay7 + "/set"))  
    {
        g_RelayStatus7 = state;
        digitalWrite(OUT_RELAY7, state);
        MqttPublishStatus_Relay7();
    }

    if(String(topic) == String(g_TopicRelay8 + "/set"))  
    {
        g_RelayStatus8 = state;
        digitalWrite(OUT_RELAY8, state);
        MqttPublishStatus_Relay8();
    }

    if(String(topic) == String(g_TopicRelay9 + "/set"))  
    {
        g_RelayStatus9 = state;
        digitalWrite(OUT_RELAY9, state);
        MqttPublishStatus_Relay9();
    }

    if(String(topic) == String(g_TopicRelay10 + "/set"))  
    {
        g_RelayStatus10 = state;
        digitalWrite(OUT_RELAY10, state);
        MqttPublishStatus_Relay10();
    }

    if(String(topic) == String(g_TopicRelay11 + "/set"))  
    {
        g_RelayStatus11 = state;
        digitalWrite(OUT_RELAY11, state);
        MqttPublishStatus_Relay11();
    }

    if(String(topic) == String(g_TopicRelay12 + "/set"))  
    {
        g_RelayStatus12 = state;
        digitalWrite(OUT_RELAY12, state);
        MqttPublishStatus_Relay12();
    }
    
}

void MqttPublishStatus_Relay1()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus1 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay1 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay2()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus2 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay2 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay3()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus3 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay3 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay4()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus4 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay4 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay5()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus5 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay5 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay6()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus6 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay6 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay7()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus7 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay7 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay8()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus8 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay8 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay9()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus9 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay9 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay10()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus10 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay10 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay11()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus11 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay11 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_Relay12()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_RelayStatus12 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish((g_TopicRelay12 + "/state").c_str(), strPayload.c_str());
    }
}

void MqttPublishStatus_dIn1()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_Input1 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish(g_TopicState_din1.c_str(), strPayload.c_str());
    }   
}

void MqttPublishStatus_dIn2()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_Input2 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish(g_TopicState_din2.c_str(), strPayload.c_str());
    }    
}

void MqttPublishStatus_dIn3()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_Input3 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish(g_TopicState_din3.c_str(), strPayload.c_str());
    }    
}

void MqttPublishStatus_dIn4()
{
    String strPayload;
    if(g_mqttPubSub.connected())
    {
        if(g_Input4 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";
        
        g_mqttPubSub.publish(g_TopicState_din4.c_str(), strPayload.c_str());
    }   
}
