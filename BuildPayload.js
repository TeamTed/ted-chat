/**
 * Created by mac on 11/10/16.
 */
/**
 * Created by mac on 11/10/16.
 */
const sjcl = require('sjcl'); //import crypto library
const readline = require('readline');

var keys = sjcl.ecc.elGamal.generateKeys(256);
var signKeys = sjcl.ecc.ecdsa.generateKeys(256);

var pubkem = keys.pub.kem(); //Key Encapsulation Mechanism
var pubkey = pubkem.key;
var seckey = keys.sec.unkem(pubkem.tag); //tag is used to derive the secret (private) key

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question("Please enter message: ", function(plaintext) {
    var cipher = sjcl.encrypt(pubkey, plaintext); //defaults to AES
    console.log(cipher);
    var signature = signKeys.sec.sign(cipher);
    //console.log(signature);
    
    //below will be moved to decrypt function
    console.log(signKeys.pub.verify(cipher, signature)); //=> true
    var result = sjcl.decrypt(seckey, cipher);
    console.log(result);
    rl.close();
});


