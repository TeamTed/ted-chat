/**
 * Created by mac on 12/1/16.
 */
const sjcl = require('sjcl');

//takes shared secret and payload and returns ciphertext
function Encrypt(publicKEM, payload) {
    var publicKey = publicKEM.key; //derive sending user's public key from shared secret
    var cipher = sjcl.encrypt(publicKey, payload);
    return cipher;
}

module.exports = Encrypt;