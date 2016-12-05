/**
 * Created by mac on 12/1/16.
 */
const sjcl = require('sjcl');
const readline = require('readline');

/*
Each user must call generateDHKeys upon install

*/

//generates a public/private key pair
function generateDHKeys() {
    var keys = sjcl.ecc.elGamal.generateKeys(256);
    return keys
}
//generates signing key pair
function generateSigningKeys() {
    var signKeys = sjcl.ecc.ecdsa.generateKeys(256);
    return signKeys;
}

function showPublicKey(keys) {
    var publickey = keys.pub;
    //publickey = sjcl.codec.base64.fromBits(publickey.x.concat(publickey.y))
    return publickey;
}

function showSecretKey(keys) {  //FOR TEST PURPOSES ONLY DELETE LATER
    var secretkey = keys.sec;
    return secretkey;
}

function testKeyGeneration() {
    //These keys are generated locally on client machine
    var alicekey = generateDHKeys();
    var bobkey = generateDHKeys();

    //These keys will be transmitted
    var alicepublickey = showPublicKey(alicekey);
    //console.log(alicepublickey);
    var bobpublickey = showPublicKey(bobkey);
    //console.log(bobpublickey);

    var alicesecretkey = showSecretKey(alicekey);
    //console.log(alicesecretkey);
    var bobsecretkey = showSecretKey(bobkey);
    //console.log(bobsecretkey);

    var alicesharedsecret = alicesecretkey.dh(bobpublickey);
    //console.log(alicesharedsecret);
    var bobsharedsecret = bobsecretkey.dh(alicepublickey);
    //console.log(bobsharedsecret);

    /*
    In order for Alice to send a message to Bob, she runs KEM on Bob's public key
     */
    var plain = "Hello World";
    var A = bobpublickey.kem();
    var ATag = A.tag;
    //console.log(ATag);
    var AKey = A.key;
    var newKey = sjcl.ecc.elGamal.generateKeys(256);
    //console.log(newKey);
    var newPublicKey = newKey.pub.get();
    var testnewPublicKey = newPublicKey;
    newPublicKey = sjcl.codec.base64.fromBits(newPublicKey.x.concat(newPublicKey.y));
    //console.log(newPublicKey);
    var cipher = sjcl.encrypt(AKey, plain);
    //console.log(cipher);
    Payload = JSON.stringify({tag: ATag, ciphertext: cipher, nk: newPublicKey});
    console.log(Payload);

    /*
    Tag = JSON.parse(Payload) ["tag"];
    console.log(Tag);
    Ciphertext = JSON.parse(Payload) ["ciphertext"];
    console.log(Ciphertext);
    NewPub = JSON.parse(Payload) ["nk"];
    console.log(NewPub);
    */
    //console.log(cipher);//BuildPayload will need to append tag to cipher

    /*
    In order for Bob to decrypt he needs to generate the kem from his secret keys?
     */
    /*
    var keyFromTag = bobsecretkey.unkem(Tag);

    var result = sjcl.decrypt(keyFromTag, Ciphertext);
    console.log(result);

    var NewPub = new sjcl.ecc.elGamal.publicKey(
        sjcl.ecc.curves.c256,
        sjcl.codec.base64.toBits(NewPub)
    )
    */
}

testKeyGeneration();



