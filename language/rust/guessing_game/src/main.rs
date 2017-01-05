// https://doc.rust-lang.org/book/guessing-game.html
extern crate rand;

use std::io;
use std::cmp::Ordering;

// We’re going to use a method in a moment, and it requires that Rng be in scope
// to work. The basic idea is this: methods are defined on something called
// ‘traits’, and for the method to work, it needs the trait to be in scope.
use rand::Rng;

fn main() {
    println!("Guess the number!");

    // We use the rand::thread_rng() function to get a copy of the random number
    // generator, which is local to the particular thread of execution we’re in.
    // Because we use rand::Rng’d above, it has a gen_range() method available.
    let secret_number = rand::thread_rng().gen_range(1, 101);
    println!("The secret number is: {}", secret_number);

    loop {
        println!("Please input your guess.");

        // The first thing to notice is that this is a let statement, which is
        // used to create ‘variable bindings’. They take this form:
        //   let foo = bar;
        //
        // This will create a new binding named foo, and bind it to the value
        // bar. In many languages, this is called a ‘variable’, but Rust’s
        // variable bindings have a few tricks up their sleeves.
        //
        // Variable binding is immutable by default; use keyword 'mut' to define
        // a mutable binding.
        //
        // The ::new() syntax uses :: because this is an ‘associated function’
        // of a particular type. That is to say, it’s associated with String
        // itself, rather than a particular instance of a String. Some languages
        // call this a ‘static method’.
        let mut guess = String::new();

        // We’re now calling an associated function on it. If we didn’t use
        // std::io, we could have written this line as std::io::stdin().
        //
        // read_line doesn’t take a String as an argument: it takes a &mut String.
        io::stdin().read_line(&mut guess)
            .expect("Failed to read line");

        // Rust allows us to ‘shadow’ the previous guess with a new one. This is
        // often used in this exact situation, where guess starts as a String,
        // but we want to convert it to an u32.
        //
        // The trim() method on Strings will eliminate any white space at the
        // beginning and end of our string. This is important, as we had to
        // press the ‘return’ key to satisfy read_line(). This means that if
        // we type 5 and hit return, guess looks like this: 5\n. The \n represents
        // ‘newline’, the enter key. trim() gets rid of this, leaving our string
        // with only the 5.
        //
        // This is how you generally move from ‘crash on error’ to ‘actually
        // handle the error’, by switching from expect() to a match statement.
        // A Result is returned by parse(), this is an enum like Ordering, but
        // in this case, each variant has some data associated with it: Ok is
        // a success, and Err is a failure.
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        // The {}s are a placeholder, and so we pass it guess as an argument.
        println!("You guessed: {}", guess);

        // The cmp() method can be called on anything that can be compared, and
        // it takes a reference to the thing you want to compare it to. It
        // returns the Ordering type we used earlier. We use a match statement
        // to determine exactly what kind of Ordering it is. Ordering is an enum.
        match guess.cmp(&secret_number) {
            Ordering::Less    => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal   => {
                println!("You win!");
                break;
            }
        }
    }
}
