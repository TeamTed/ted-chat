/**
 * Created by mac on 12/6/16.
 */
const sjcl = require('sjcl');
const BuildPayload = require('./BuildPayload');
const Encrypt = require('./Encrypt');
const Sign = require('./Sign');
const VerifySignature = require('./VerifySignature');
const Decrypt = require('./Decrypt');
var Friend = require('./Friend');

//user object
function User(name, pw, dhKeys, signingKeys, publicKey, friends) {
    this.name = name;
    this.pw = sjcl.hash.sha256.hash(pw); //passwords are hashed
    this.dhKeys = dhKeys;
    this.signingKeys = signingKeys;
    this.publicKey = publicKey;
    this.friends = [];
};

//adds a friend to user's friends array
User.prototype.addFriend = function(name, publicKey) {
    var newFriend = new Friend(name, publicKey);
    this.friends.push(newFriend);
    /*
    should also write friend to some sort of dictionary so friend's name
    can be called instead of friend array index
     */
};

//takes plaintext and the recipient's public key and returns the full message payload
User.prototype.sendMessage = function(plaintext, friendPublicKey) {
    var pubKEM = friendPublicKey.kem();                                 //create an encrypted shared secret
    var payload = BuildPayload(plaintext);                              //append reneg key to plaintext
    var cipher = Encrypt(pubKEM, payload);                              //encrypt payload with shared secret
    var signature = Sign(this.signingKeys, cipher);                     //sign the ciphertext
    var message = [cipher, signature, this.signingKeys.pub, pubKEM];    //TEMP: will need to be a JSON object
    return message;
};

//takes the message and returns the plaintext
User.prototype.receiveMessage = function(message) {
    VerifySignature(message);       //returns true if signature passes, error if false
    Decrypt(this.dhKeys, message);  //returns plaintext
};

module.exports = User;


