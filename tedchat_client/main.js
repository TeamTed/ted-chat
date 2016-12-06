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
    //console.log(alice);

    var bob = CreateUser("Bob", "Password321");
    //console.log(bob);

    alice.addFriend("Bob", bob.publicKey);
    //console.log(alice);

    bob.addFriend("Alice", alice.publicKey);
    //console.log(bob);

    function readAgain () {
        rl.question("Please enter message: ", function (plaintext) {
            var extra = " I'm extra stuff";
            var plaintext2 = plaintext + extra;
            var message = alice.sendMessage(plaintext, alice.friends[0].publicKey);
            bob.receiveMessage(message);

            var message2 = bob.sendMessage(plaintext2, bob.friends[0].publicKey);
            alice.receiveMessage(message2);
            readAgain(); //Calling this function again to ask new question
        });
    };
    readAgain();
}

main();