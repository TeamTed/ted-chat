/**
 * Created by mac on 12/1/16.
 */
const sjcl = require('sjcl');

var keys = sjcl.ecc.elGamal.generateKeys(256);
var signKeys = sjcl.ecc.ecdsa.generateKeys(256);
var pubkem = keys.pub.kem();
var pubkey = pubkem.key;
var plaintext = "HelloWorld";

function Encrypt(publicKey, signingKeys, payload) {
    var cipher = sjcl.encrypt(publicKey, payload);
    console.log(cipher);
    var signature = signingKeys.sec.sign(cipher);
}

Encrypt(pubkey, signKeys, plaintext);