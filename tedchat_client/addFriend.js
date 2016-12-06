/**
 * Created by mac on 12/6/16.
 */
const user = require('./User');
const Friend = require('./Friend');

function addFriend(user, name, publicKey) {
    friend = new Friend(name, publicKey);
    user.friends.push(friend);
}

module.exports = addFriend;