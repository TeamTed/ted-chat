/**
 * Created by mac on 12/1/16.
 */
const CreateUser = require('./createUser');
var User = require('./User');
const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function main() {
    var alice = CreateUser("Alice", "Password123");

    var bob = CreateUser("Bob", "Password321");

    alice.addFriend("Bob", bob.publicKey);

    bob.addFriend("Alice", alice.publicKey);

    function readAgain () {
        rl.question("Please enter message: ", function (plaintext) {
            var extra = " I'm extra stuff";
            var plaintext2 = plaintext + extra;
            var message = alice.sendMessage(plaintext, alice.friends[0].publicKey);
            bob.receiveMessage(message);

            var message2 = bob.sendMessage(plaintext2, bob.friends[0].publicKey);
            alice.receiveMessage(message2);
            readAgain();
        });
    };
    readAgain();
}

main();