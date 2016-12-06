/**
 * Created by mac on 12/6/16.
 */
const sjcl = require('sjcl');

module.exports = {
    //creates elliptic curve diffie-hellman key pair
    GenerateDHKeys: function() {
        return dhKeys = sjcl.ecc.elGamal.generateKeys(256);
    },

    //creates elliptic curve digital signature key pair
    GenerateSigningKeys: function() {
        return signKeys = sjcl.ecc.ecdsa.generateKeys(256);
    },

    //returns diffie-hellman public key
    GetPublicKey: function(dhKeys) {
        return dhKeys.pub;
    }
};
