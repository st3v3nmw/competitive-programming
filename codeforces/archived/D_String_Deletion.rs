#![allow(unused)]
use std::io::{self, prelude::*}; use std::str;

#[macro_export] macro_rules! dbg { ($expr:expr) => { match $expr { expr => { eprintln!("{}: {} = {:#?}", line!(), stringify!($expr), &expr); expr } } }; ($l:literal, $expr:expr) => { match $expr { expr => { eprintln!(concat!(line!(), ": ", stringify!($expr), " = ", $l), &expr); ($l, expr) } } } }
#[macro_export] macro_rules! ternary { ($condition: expr, $_true: expr, $_false: expr) => { if $condition { $_true } else { $_false } }; }
struct Scanner<R> { reader: R, buf_str: Vec<u8>, buf_iter: str::SplitWhitespace<'static>}
impl<R: BufRead> Scanner<R> { fn new(reader: R) -> Self { Self { reader, buf_str: vec![], buf_iter: "".split_whitespace() } } fn token<T: str::FromStr>(&mut self) -> T { loop { if let Some(token) = self.buf_iter.next() { return token.parse().ok().expect("Failed parse"); } self.buf_str.clear(); self.reader.read_until(b'\n', &mut self.buf_str).expect("Failed read"); self.buf_iter = unsafe { let slice = str::from_utf8_unchecked(&self.buf_str); std::mem::transmute(slice.split_whitespace()) } } } }

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut sc = Scanner::new(stdin.lock()); let mut out = io::BufWriter::new(stdout.lock());

    let g: i64 = sc.token::<i64>();
    for _ in 0..g {
        let n: i64 = sc.token::<i64>();
        let s: String = sc.token::<String>();
        if n == 1 {
            writeln!(out, "1");
            continue;
        }

        let mut state = vec![];

        let (mut i, mut prev, mut cl, mut p) = (0, 0, 0, 0);
        for c in s.chars() {
            if i == 0 {
                i += 1;
                prev = ternary!(c == '1', 1, 0);
                continue;
            }
            p = ternary!(c == '1', 1, 0);
            cl += 1;
            if p != prev {
                prev = p;
                state.push(cl);
                cl = 0;
            }
        }
        state.push(ternary!(cl == 0, 1, cl + 1));
        let mut c = 0;
        loop {
            if (state.len() == 0) {
                break;
            }
            c += 1;
            let n1: i64 = state[state.len() - 1];
            if state[0] > 1 {
                state.remove(0);
            } else if n1 < state[0] { 
                state.remove(0);
            } else {
                state.pop();
                if n1 - 1 != 0 {
                    state.push(n1 - 1);
                }
                if (state.len() == 0) {
                    break;
                }
                state.remove(0);
            }
        }
        writeln!(out, "{}", c);
    }
}