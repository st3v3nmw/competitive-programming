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
    let mut s: u64 = 0;
    for _ in 0..g {
        let (mut a, b) = (sc.token::<u64>(), sc.token::<u64>());
        let (mut x1, mut x2) = (0, 0);
        match ((a - 1) % 4) {
            0 => x1 = a - 1,
            1 => x1 = 1,
            2 => x1 = a,
            _ => x1 = 0
        }

        match ((a + b - 1) % 4) {
            0 => x2 = a + b - 1,
            1 => x2 = 1,
            2 => x2 = a + b,
            _ => x2 = 0
        }
        
        s ^= (x1 ^ x2);
    }
    write!(out, "{}", ternary!(s == 0, "bolik\n", "tolik\n"));
}