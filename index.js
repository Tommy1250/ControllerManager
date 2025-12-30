const bt = require('./build/Release/btaddon.node');

/**
 * 
 * @param {string} mac The mac adress of the bluetooth device
 * @returns {boolean} the disconnect status of the device
 */
function disconnectBT(mac) {
    const result = bt.disconnectBT(mac);
    return result;
}

module.exports = disconnectBT;