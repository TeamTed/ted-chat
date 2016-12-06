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

User.prototype.addFriend = function(name, publicKey) {
    var newFriend = new Friend(name, publicKey);
    this.friends.push(newFriend);
    //should also write friend to a dictionary that matches name to array index
};

User.prototype.sendMessage = function(plaintext, friendPublicKey) {
    var pubKEM = friendPublicKey.kem();
    var payload = BuildPayload(plaintext);
    var cipher = Encrypt(pubKEM, payload);
    var signature = Sign(this.signingKeys, cipher);
    var message = [cipher, signature, this.signingKeys.pub, pubKEM];
    return message;
};

User.prototype.receiveMessage = function(message) {
    VerifySignature(message);
    Decrypt(this.dhKeys, message);
};

module.exports = User;


