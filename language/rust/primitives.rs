// https://doc.rust-lang.org/book/primitive-types.html

fn main() {
    // Boolean type.
    let x = true;
    let y: bool = false;

    // The char type represents a single Unicode scalar value. Unlike some other
    //  languages, this means that Rust’s char is not a single byte, but four.
    let x = 'x';
    let y = '邓';

    // array is a fixed-size list of elements of the same type. By default,
    // arrays are immutable. Arrays have type [T; N].
    let a = [1, 2, 3];          // a: [i32; 3]
    let mut m = [1, 2, 3];      // m: [i32; 3]

    // In this example, each element of a will be initialized to 0.
    let a = [0; 20]; // a: [i32; 20]

    // Use .len() to find array length.
    let a = [1, 2, 3];
    println!("a has {} elements", a.len());

    // Access a particular element of an array with subscript notation:
    let names = ["Graydon", "Brian", "Niko"]; // names: [&str; 3]
    println!("The second name is: {}", names[1]);
}
