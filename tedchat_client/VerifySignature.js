/**
 * Created by mac on 12/6/16.
 */
const sjcl = require('sjcl');

//takes message and returns true if signature passes, error if signature fails
function VerifySignature(message) {
    var cipher = message[0];                                    //TEMP: message components are stored in array
    var signature = message[1];
    var publicSigningKey = message[2];
    console.log(publicSigningKey.verify(cipher, signature));
}

module.exports = VerifySignature;