/**
 * Created by mac on 12/6/16.
 */
const sjcl = require('sjcl');

//takes sending user's signing keys and signs ciphertext
function Sign(signingKeys, cipher) {
    var signature = signingKeys.sec.sign(cipher);
    return signature;
}

module.exports = Sign;