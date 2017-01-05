// Variable bindings in rust
//
// https://doc.rust-lang.org/book/variable-bindings.html

fn main() {
    // Simple assignment.
    let x = 5;

    let (x, y) = (1, 2);

    // Rust has this thing called ‘type inference’. If it can figure out what
    // the type of something is, Rust doesn’t require you to explicitly type
    // it out. We can add the type if we want to, though. Types come after a
    // colon (:).
    let x: i32 = 5;

    // By default, bindings are immutable. If you want a binding to be mutable,
    // you can use mut. Additionally, variable bindings can be shadowed. This
    // means that a later variable binding with the same name as another binding
    // that is currently in scope will override the previous binding. shadowing
    // enables us to rebind a name to a value of a different type. It is also
    // possible to change the mutability of a binding. Note that shadowing a
    // name does not alter or destroy the value it was bound to, and the value
    // will continue to exist until it goes out of scope, even if it is no longer
    // accessible by any means.
    let mut x = 5;              // mut x: i32
    x = 10;

    // Variable binding scope.
    let x: i32 = 17;
    {
        let y: i32 = 3;
        println!("The value of x is {} and value of y is {}", x, y); // 17, 3
    }
    println!("The value of x is {} and value of y is {}", x, y); // 17, 2
}
