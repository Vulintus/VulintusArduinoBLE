/*
  This file is part of the Vulintus Arduino BLE library.
  Copyright (c) 2020 Vulintus Inc. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __VULINTUS_ARDUINO_BLE_ATT_H
#define __VULINTUS_ARDUINO_BLE_ATT_H

#include <Arduino.h>

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
    #include "ble/atmel_ble_api/include/m2m_ble.h"
}

#include "vulintus_arduino_ble/BLELinkedList.h"
#include "vulintus_arduino_ble/BLEPeerConnection.h"

namespace VulintusArduinoBLE
{
    class ATTClass
    {
        public:

            ATTClass ();
            ~ATTClass ();

            void SendIndication (at_ble_handle_t value_handle);
            void SendNotification (at_ble_handle_t value_handle);

            BLEPeerConnection GetFirstPeerConnectionOrDefault ();
            bool DoesConnectionExist (BLEPeerConnection connection);
            void ProcessEvents ();
            
        private:

            at_ble_event_parameter_t gu8BleParam;
            void ble_event_manager(at_ble_events_t events, void *event_params);

            BLELinkedList<BLEPeerConnection> peers;

    };

    extern ATTClass ATT;
}

#endif /* __VULINTUS_ARDUINO_BLE_ATT_H */