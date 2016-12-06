/**
 * Created by mac on 12/4/16.
 */
const sjcl = require('sjcl');

//takes plaintext and appends renegotiation key for session renegotiation(WIP)
function buildPayload(plaintext) {
    var renegKey = sjcl.ecc.elGamal.generateKeys(256);
    renegPublicKey = renegKey.pub;
    var payload = renegPublicKey + plaintext;
    return payload;
}

module.exports = buildPayload;
