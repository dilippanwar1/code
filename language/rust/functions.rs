// Functions in rust
//
// https://doc.rust-lang.org/book/functions.html

// Every Rust program has at least one function, the main function.
fn main() {
    print_number(5);
    print_sum(5, 2);

    println!("x add one is {}", add_one(5));
    println!("x add one v2 is {}", add_one_2(5));
    fn_pointer();

    diverges();
}

// print_number takes an argument. function arguments work very similar to let
// declarations: you add a type to the argument name, after a colon. Unlike let,
// you must declare the types of function arguments. We agree that forcing
// functions to declare types while allowing for inference inside of function
// bodies is a wonderful sweet spot between full inference and no inference.
fn print_number(x: i32) {
    println!("x is: {}", x);
}

// print_sum takes two arguments.
fn print_sum(x: i32, y: i32) {
    println!("x + y is: {}", x+y);
}

// Rust functions return exactly one value, and you declare the type after an
// ‘arrow’. The last line of a function determines what it returns. You’ll note
// the lack of a semicolon here.
//
// Rust is primarily an expression-based language. There are only two kinds of
// statements, and everything else is an expression. So what's the difference?
// Expressions return a value, and statements do not. That’s why we end up with
// ‘not all control paths return a value’ here (if the last line has a ';'): the
// statement x + 1; doesn’t return a value. There are two kinds of statements in
// Rust: ‘declaration statements’ and ‘expression statements’. Everything else
// is an expression.
//
// Our function claims to return an i32, but with a semicolon, it would return
// () instead.
fn add_one(x: i32) -> i32 {
    x + 1
}

// This is a more intuitive version of add_one if you haven’t worked in an
// expression-based language before.
fn add_one_2(x: i32) -> i32 {
    return x + 1;
}

// Unlike println!(), panic!() causes the current thread of execution to crash
// with the given message. Because this function will cause a crash, it will
// never return, and so it has the type ‘!’, which is read ‘diverges’.
fn diverges() -> ! {
    panic!("This function never returns!");
}

// We can also create variable bindings which point to functions:
//   let f: fn(i32) -> i32;Run
// f is a variable binding which points to a function that takes an i32 as
// an argument and returns an i32. For example:
fn fn_pointer() {
    // without type inference
    let f: fn(i32) -> i32 = plus_one;

    // with type inference
    let f = plus_one;

    println!("x plus one is {}", f(5));
}

// For function pointer demonstration.
fn plus_one(i: i32) -> i32 {
    i + 1
}
