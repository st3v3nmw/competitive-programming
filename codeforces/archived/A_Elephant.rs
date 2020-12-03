#![allow(unused)]
use std::io;

#[macro_export]
macro_rules! dbg {
    ($expr:expr) => { match $expr { expr => { eprintln!("{}: {} = {:#?}", line!(), stringify!($expr), &expr); expr } } };
    ($l:literal, $expr:expr) => { match $expr { expr => { eprintln!(concat!(line!(), ": ", stringify!($expr), " = ", $l), &expr); ($l, expr) } } }
}

#[macro_export]
macro_rules! ternary { ($condition: expr, $_true: expr, $_false: expr) => { if $condition { $_true } else { $_false } }; }

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("");
    let x: u32 = input.trim().parse().expect("");
    println!("{}", x / 5 + ternary!(x % 5 > 0, 1, 0));
}