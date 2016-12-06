/**
 * Created by mac on 12/6/16.
 */
const sjcl = require('sjcl');

function Sign(signingKeys, cipher) {
    var signature = signingKeys.sec.sign(cipher);
    return signature;
}
/*
var keys2 = sjcl.ecc.ecdsa.generateKeys(384, 1); //choose a stronger/weaker curve

var hashOfPlainText = "abc123"; //dummy hash

var signature = keys2.sec.sign(cipher);
console.log(keys2.pub.verify(cipher, signature))
 */

module.exports = Sign;