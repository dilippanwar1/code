// https://doc.rust-lang.org/book/guessing-game.html

use std::io;

fn main() {
    println!("Guess the number!");

    println!("Please input your guess.");

    // The first thing to notice is that this is a let statement, which is used
    // to create ‘variable bindings’. They take this form:
    //   let foo = bar;
    //
    // This will create a new binding named foo, and bind it to the value bar.
    // In many languages, this is called a ‘variable’, but Rust’s variable
    // bindings have a few tricks up their sleeves.
    //
    // Variable binding is immutable by default; use 'mut' to define a mutable
    // binding.
    //
    // The ::new() syntax uses :: because this is an ‘associated function’ of a
    // particular type. That is to say, it’s associated with String itself,
    // rather than a particular instance of a String. Some languages call this
    // a ‘static method’.
    let mut guess = String::new();

    // We’re now calling an associated function on it. If we didn’t use std::io,
    // we could have written this line as std::io::stdin().
    //
    // read_line doesn’t take a String as an argument: it takes a &mut String.
    io::stdin().read_line(&mut guess)
        .expect("Failed to read line");

    // The {}s are a placeholder, and so we pass it guess as an argument.
    println!("You guessed: {}", guess);
}
