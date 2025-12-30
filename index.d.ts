declare module 'controllermanager' {
  /**
   * Disconnects a Bluetooth device by MAC address.
   * @param mac The MAC address of the Bluetooth device
   * @returns The disconnect status of the device
   */
  export function disconnectBT(mac: string): boolean;
}
