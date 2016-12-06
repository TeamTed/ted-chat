/**
 * Created by mac on 12/1/16.
 */
const sjcl = require('sjcl');

function Decrypt(dhkeys, message) {
     var cipher = message[0];
     var pubKEM = message[3];
     var secret = dhkeys.sec.unkem(pubKEM.tag);
     var plaintext = sjcl.decrypt(secret, cipher);
     console.log(plaintext);
}

module.exports = Decrypt;