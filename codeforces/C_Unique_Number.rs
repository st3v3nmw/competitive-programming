#![allow(unused)]
use std::io::{self, prelude::*}; use std::str;

#[macro_export] macro_rules! dbg { ($expr:expr) => { match $expr { expr => { eprintln!("{}: {} = {:#?}", line!(), stringify!($expr), &expr); expr } } }; ($l:literal, $expr:expr) => { match $expr { expr => { eprintln!(concat!(line!(), ": ", stringify!($expr), " = ", $l), &expr); ($l, expr) } } } }
#[macro_export] macro_rules! ternary { ($condition: expr, $_true: expr, $_false: expr) => { if $condition { $_true } else { $_false } }; }
struct Scanner<R> { reader: R, buf_str: Vec<u8>, buf_iter: str::SplitWhitespace<'static>}
impl<R: BufRead> Scanner<R> { fn new(reader: R) -> Self { Self { reader, buf_str: vec![], buf_iter: "".split_whitespace() } } fn token<T: str::FromStr>(&mut self) -> T { loop { if let Some(token) = self.buf_iter.next() { return token.parse().ok().expect("Failed parse"); } self.buf_str.clear(); self.reader.read_until(b'\n', &mut self.buf_str).expect("Failed read"); self.buf_iter = unsafe { let slice = str::from_utf8_unchecked(&self.buf_str); std::mem::transmute(slice.split_whitespace()) } } } }

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut sc = Scanner::new(stdin.lock()); let mut out = io::BufWriter::new(stdout.lock());

    let g: u32 = sc.token::<u32>();
    for _ in 0..g {
        let mut n: i32 = sc.token::<i32>();
        if n > 45 {
            write!(out, "-1\n");
            continue;
        }
        let (mut r, mut c): (i32, u32) = (0, 0);
        for i in 1..10 {
            if n - (10 - i) >= 0 {
                r += (10 - i) * 10_i32.pow(c);
                c += 1;
                n -= (10 - i);
            }
        }
        write!(out, "{}\n", r);
    }
}