#include "vulintus_arduino_ble/BLERemoteDevice.h"

namespace VulintusArduinoBLE
{
    /// <summary>
    /// Constructor
    /// </summary>
    BLERemoteDevice::BLERemoteDevice()
    {
        memset(peer_connection.peer_address.addr, 0, 6);
        peer_connection.peer_address.type = at_ble_addr_type_t::AT_BLE_ADDRESS_INVALID;
        peer_connection.connection_handle = 0xffff;
    }

    /// <summary>
    /// Constructor given an address and an existing handle
    /// </summary>
    BLERemoteDevice::BLERemoteDevice(at_ble_addr_t address, at_ble_handle_t handle)
    {
        peer_connection.peer_address = address;
        peer_connection.connection_handle = handle;
    }

    BLERemoteDevice::BLERemoteDevice(BLEPeerConnection connection)
    {
        peer_connection = connection;
    }

    /// <summary>
    /// Destructor
    /// </summary>
    BLERemoteDevice::~BLERemoteDevice()
    {
        //empty
    }

    /// <summary>
    /// This method defines a boolean operator for the BLERemoteDevice,
    /// allowing us to evaluate the entire object to either "true" or "false".
    /// </summary>
    /// <returns></returns>
    BLERemoteDevice::operator bool() const
    {
        uint8_t zeros[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};
        return (memcmp(peer_connection.peer_address.addr, zeros, sizeof(zeros)) != 0);
    }

    String BLERemoteDevice::GetAddress (bool include_addr_type)
    {
        at_ble_addr_t address = peer_connection.peer_address;
        String result = "MAC ";
        for (int i = 5; i >= 0; i--)
        {
            String t = "";
            if (address.addr[i] < 0x10)
            {
                t += "0";
            }

            t += String(address.addr[i], HEX);

            if (i > 0)
            {
                t += ":";
            }

            result += t;
        }

        if (include_addr_type)
        {
            result += ", address type = ";
            switch (address.type)
            {
                case at_ble_addr_type_t::AT_BLE_ADDRESS_INVALID:
                    result += "AT_BLE_ADDRESS_INVALID";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_PUBLIC:
                    result += "AT_BLE_ADDRESS_PUBLIC";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_RANDOM_PRIVATE_NON_RESOLVABLE:
                    result += "AT_BLE_ADDRESS_RANDOM_PRIVATE_NON_RESOLVABLE";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_RANDOM_PRIVATE_RESOLVABLE:
                    result += "AT_BLE_ADDRESS_RANDOM_PRIVATE_RESOLVABLE";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_RANDOM_STATIC:
                    result += "AT_BLE_ADDRESS_RANDOM_STATIC";
                    break;
                default:
                    result += "UNKNOWN";
                    break;
            }
        }

        return result;
    }    

    bool BLERemoteDevice::IsConnected ()
    {
        return ATT.DoesConnectionExist(peer_connection);
    }
}