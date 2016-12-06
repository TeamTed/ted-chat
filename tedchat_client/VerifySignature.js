/**
 * Created by mac on 12/6/16.
 */
const sjcl = require('sjcl');

function VerifySignature(message) {
    var cipher = message[0];
    var signature = message[1];
    var publicSigningKey = message[2];
    console.log(publicSigningKey.verify(cipher, signature));
}

module.exports = VerifySignature;