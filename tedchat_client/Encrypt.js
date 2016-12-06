/**
 * Created by mac on 12/1/16.
 */
const sjcl = require('sjcl');

function Encrypt(publicKEM, payload) {
    var publicKey = publicKEM.key;
    var cipher = sjcl.encrypt(publicKey, payload);
    return cipher;
}

module.exports = Encrypt;
/*
var keys = sjcl.ecc.elGamal.generateKeys(384, 1); //choose a stronger/weaker curve

var pubkem = keys.pub.kem(); //KEM is Key Encapsulation Mechanism
var pubkey = pubkem.key;
var seckey = keys.sec.unkem(pubkem.tag); //tag is used to derive the secret (private) key

var plain = "hello world!";
var cipher = sjcl.encrypt(pubkey, plain); //defaults to AES

var result = sjcl.decrypt(seckey, cipher);
console.log(plain === result);
*/