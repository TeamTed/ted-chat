/**
 * Created by mac on 12/6/16.
 */
const createKeys = require('./createKeys');
var User = require('./User');

//creates a new user and assigns their keys
function createUser(name, pw) {
    var dhKeys = createKeys.GenerateDHKeys();
    var signingKeys = createKeys.GenerateSigningKeys();
    var publicKey = createKeys.GetPublicKey(dhKeys);
    var newUser = new User(name, pw, dhKeys, signingKeys, publicKey);
    return newUser;
}

module.exports = createUser;