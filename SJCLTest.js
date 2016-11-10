/**
 * Created by mac on 11/8/16.
 */

const sjcl = require('sjcl');

console.log('SJCL sanity test start.');

var ciphertext = sjcl.encrypt("password", "Hello World!")
var plaintext = sjcl.decrypt("password", ciphertext)

console.log(ciphertext)
console.log(plaintext)

console.log('SJCL sanity test done.');

//Encrypt
var keys = sjcl.ecc.elGamal.generateKeys(256);

var pubkem = keys.pub.kem(); //KEM is Key Encapsulation Mechanism
var pubkey = pubkem.key;
var seckey = keys.sec.unkem(pubkem.tag); //tag is used to derive the secret (private) key

var plain = "hello world!";
var cipher = sjcl.encrypt(pubkey, plain); //defaults to AES
var result = sjcl.decrypt(seckey, cipher);

console.log(plain === result); //true

//Sign
var signKeys = sjcl.ecc.ecdsa.generateKeys(256);

var hashOfPlainText = "abc123"; //dummy hash
var signature = signKeys.sec.sign(hashOfPlainText);

console.log(signKeys.pub.verify(hashOfPlainText, signature)) //=> true
console.log(signKeys.pub.verify("abc124", signature)) //=> throws "signature didn't check out"


//Generate keys -> run EC hash on key -> pass that to encryption