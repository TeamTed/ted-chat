/**
 * Created by mac on 12/1/16.
 */
const sjcl = require('sjcl');

//takes recipient's diffie-hellman keys(to decrypt secret) and decrypts message
function Decrypt(dhkeys, message) {
     var cipher = message[0];                         //TEMP: message components are stored in array
     var pubKEM = message[3];
     var key = dhkeys.sec.unkem(pubKEM.tag);          //Reveals decrypted key
     var plaintext = sjcl.decrypt(key, cipher);
     console.log(plaintext);
}

module.exports = Decrypt;