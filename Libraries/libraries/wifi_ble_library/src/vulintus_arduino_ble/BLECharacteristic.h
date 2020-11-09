#ifndef VULINTUS_ARDUINO_BLE_CHARACTERISTIC_H
#define VULINTUS_ARDUINO_BLE_CHARACTERISTIC_H

#include <stdint.h>

#include "BLEDescriptor.h"

namespace VulintusArduinoBLE
{
    enum BLECharacteristicEvent 
    {
        BLESubscribed = 0,
        BLEUnsubscribed = 1,
        //BLERead = 2, // defined in BLEProperties.h
        BLEWritten = 3,
        BLEUpdated = BLEWritten, // alias
        BLECharacteristicEventLast
    };

    class BLECharacteristic;
    class BLEDevice;

    typedef void (*BLECharacteristicEventHandler)(BLEDevice device, BLECharacteristic characteristic);

    class BLELocalCharacteristic;
    class BLERemoteCharacteristic;

    class BLECharacteristic  
    {
        public:
            BLECharacteristic();
            BLECharacteristic(const char* uuid, uint8_t properties, int valueSize, bool fixedLength = false);
            BLECharacteristic(const char* uuid, uint8_t properties, const char* value);
            BLECharacteristic(const BLECharacteristic& other);
            virtual ~BLECharacteristic();

            const char* uuid() const;

            uint8_t properties() const;

            int valueSize() const;
            const uint8_t* value() const;
            int valueLength() const;
            uint8_t operator[] (int offset) const;

            int readValue(uint8_t value[], int length);
            int readValue(void* value, int length);
            int readValue(uint8_t& value);
            int readValue(int8_t& value);
            int readValue(uint16_t& value);
            int readValue(int16_t& value);
            int readValue(uint32_t& value);
            int readValue(int32_t& value);

            int writeValue(const uint8_t value[], int length);
            int writeValue(const void* value, int length);
            int writeValue(const char* value);
            int writeValue(uint8_t value);
            int writeValue(int8_t value);
            int writeValue(uint16_t value);
            int writeValue(int16_t value);
            int writeValue(uint32_t value);
            int writeValue(int32_t value);

            int broadcast();

            bool written();
            bool subscribed();
            bool valueUpdated();

            void addDescriptor(BLEDescriptor& descriptor);

            operator bool() const;

            void setEventHandler(int event, BLECharacteristicEventHandler eventHandler);

            int descriptorCount() const;
            bool hasDescriptor(const char* uuid) const;
            bool hasDescriptor(const char* uuid, int index) const;
            BLEDescriptor descriptor(int index) const;
            BLEDescriptor descriptor(const char * uuid) const;
            BLEDescriptor descriptor(const char * uuid, int index) const;

            bool canRead();
            bool read();
            bool canWrite();
            bool canSubscribe();
            bool subscribe();
            bool canUnsubscribe();
            bool unsubscribe();

        protected:
            friend class BLELocalCharacteristic;
            friend class BLELocalService;

            BLECharacteristic(BLELocalCharacteristic* local);

            BLELocalCharacteristic* local();

        protected:
            friend class BLEDevice;
            friend class BLEService;
            friend class BLERemoteCharacteristic;

            BLECharacteristic(BLERemoteCharacteristic* remote);

        private:
            BLELocalCharacteristic* _local;
            BLERemoteCharacteristic* _remote;
    };
}

#endif /* VULINTUS_ARDUINO_BLE_CHARACTERISTIC_H */
