/**
 * Created by mac on 12/1/16.
 */
const sjcl = require('sjcl');

function Decrypt(Payload) {

     Tag = JSON.parse(Payload) ["tag"];
     console.log(Tag);
     Ciphertext = JSON.parse(Payload) ["ciphertext"];
     console.log(Ciphertext);
    /*
     NewPub = JSON.parse(Payload) ["nk"];
     console.log(NewPub);
     */
    //console.log(cipher);//BuildPayload will need to append tag to cipher

    /*
     In order for Bob to decrypt he needs to generate the kem from his secret keys?
     */

     var keyFromTag = bobsecretkey.unkem(Tag);

     var result = sjcl.decrypt(keyFromTag, Ciphertext);
     console.log(result);

    /*
     var NewPub = new sjcl.ecc.elGamal.publicKey(
     sjcl.ecc.curves.c256,
     sjcl.codec.base64.toBits(NewPub)
     )
     */
}

