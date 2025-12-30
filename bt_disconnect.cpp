#include <windows.h>
#include <bluetoothapis.h>
#include <iostream>
#include <string>
#include <sstream>

#pragma comment(lib, "Bthprops.lib")

#define IOCTL_BTH_DISCONNECT_DEVICE 0x41000c

bool DisconnectBT(const std::string& mac)
{
    BLUETOOTH_FIND_RADIO_PARAMS params{};
    params.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);

    HANDLE hRadio = NULL;
    HBLUETOOTH_RADIO_FIND hFind =
        BluetoothFindFirstRadio(&params, &hRadio);

    if (!hFind)
        return false;

    // Parse MAC
    BYTE addr[8] = {0};
    unsigned int b[6];

    if (sscanf_s(
        mac.c_str(),
        "%02x:%02x:%02x:%02x:%02x:%02x",
        &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]
    ) != 6)
    {
        BluetoothFindRadioClose(hFind);
        return false;
    }

    // Bluetooth expects reverse order
    for (int i = 0; i < 6; i++)
        addr[5 - i] = (BYTE)b[i];

    ULONGLONG btAddr = *(ULONGLONG*)addr;

    DWORD bytesReturned = 0;
    BOOL success = FALSE;

    do
    {
        success = DeviceIoControl(
            hRadio,
            IOCTL_BTH_DISCONNECT_DEVICE,
            &btAddr,
            sizeof(btAddr),
            NULL,
            0,
            &bytesReturned,
            NULL
        );

        CloseHandle(hRadio);

        if (success)
            break;

    } while (BluetoothFindNextRadio(hFind, &hRadio));

    BluetoothFindRadioClose(hFind);
    return success == TRUE;
}
