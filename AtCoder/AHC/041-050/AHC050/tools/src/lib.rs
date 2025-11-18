#![allow(non_snake_case, unused_macros)]

use itertools::Itertools;
use proconio::{input, marker::Chars};
use rand::prelude::*;
use std::ops::RangeBounds;
#[cfg(feature = "vis")]
use svg::node::element::{Group, Line, Rectangle, Style, Title};

pub trait SetMinMax {
    fn setmin(&mut self, v: Self) -> bool;
    fn setmax(&mut self, v: Self) -> bool;
}
impl<T> SetMinMax for T
where
    T: PartialOrd,
{
    fn setmin(&mut self, v: T) -> bool {
        *self > v && {
            *self = v;
            true
        }
    }
    fn setmax(&mut self, v: T) -> bool {
        *self < v && {
            *self = v;
            true
        }
    }
}

#[macro_export]
macro_rules! mat {
	($($e:expr),*) => { Vec::from(vec![$($e),*]) };
	($($e:expr,)*) => { Vec::from(vec![$($e),*]) };
	($e:expr; $d:expr) => { Vec::from(vec![$e; $d]) };
	($e:expr; $d:expr $(; $ds:expr)+) => { Vec::from(vec![mat![$e $(; $ds)*]; $d]) };
}

#[derive(Clone, Debug)]
pub struct Input {
    pub N: usize,
    pub M: usize,
    pub S: Vec<Vec<char>>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {}", self.N, self.M)?;
        for row in &self.S {
            writeln!(f, "{}", row.iter().collect::<String>())?;
        }
        Ok(())
    }
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        N: usize, M: usize,
        S: [Chars; N],
    }
    Input { N, M, S }
}

pub fn read<T: Copy + PartialOrd + std::fmt::Display + std::str::FromStr, R: RangeBounds<T>>(
    token: Option<&str>,
    range: R,
) -> Result<T, String> {
    if let Some(v) = token {
        if let Ok(v) = v.parse::<T>() {
            if !range.contains(&v) {
                Err(format!("Out of range: {}", v))
            } else {
                Ok(v)
            }
        } else {
            Err(format!("Parse error: {}", v))
        }
    } else {
        Err("Unexpected EOF".to_owned())
    }
}

pub struct Output {
    pub out: Vec<(usize, usize)>,
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let mut f = f.split_whitespace().peekable();
    let mut out = vec![];
    while f.peek().is_some() {
        let i = read(f.next(), 0..input.N)?;
        let j = read(f.next(), 0..input.N)?;
        out.push((i, j));
        if out.len() > input.N * input.N - input.M {
            return Err("Too many outputs".to_owned());
        }
    }
    Ok(Output { out })
}

pub fn gen(seed: u64, fix_N: Option<usize>, fix_M: Option<usize>) -> Input {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed);
    let mut N = 40;
    if let Some(fix_N) = fix_N {
        if fix_N > 50 {
            panic!("N must be at most 50, but got {}", fix_N);
        }
        N = fix_N;
    }
    let mut M = rng.gen_range(((N * N + 9) / 10) as i32..=(N * N / 4) as i32) as usize;
    if let Some(fix_M) = fix_M {
        M = fix_M;
    }
    assert!(M <= N * N);
    let mut ps = (0..N * N).collect_vec();
    ps.shuffle(&mut rng);
    let mut S = mat!['.'; N; N];
    for p in ps.into_iter().take(M) {
        S[p / N][p % N] = '#';
    }
    Input { N, M, S }
}

pub fn compute_score(input: &Input, out: &Output) -> (i64, String) {
    let (mut score, err, _) = compute_score_details(input, &out.out);
    if err.len() > 0 {
        score = 0;
    }
    (score, err)
}

pub struct State {
    pub S: Vec<Vec<char>>,
    pub prob: Vec<Vec<f64>>,
    pub lives: Vec<f64>,
}

pub fn compute_score_details(input: &Input, out: &[(usize, usize)]) -> (i64, String, State) {
    let mut S = input.S.clone();
    let mut crt = mat![0.0; input.N; input.N];
    for i in 0..input.N {
        for j in 0..input.N {
            if input.S[i][j] == '.' {
                crt[i][j] = 1.0 / (input.N * input.N - input.M) as f64;
            }
        }
    }
    let mut ret = 0.0;
    let mut lives = vec![1.0];
    let mut life = 1.0;
    for t in 0.. {
        let mut next = mat![0.0; input.N; input.N];
        for i in 0..input.N {
            for j in 0..input.N {
                if crt[i][j] == 0.0 {
                    continue;
                }
                for (di, dj) in [(!0, 0), (1, 0), (0, !0), (0, 1)] {
                    let mut i2 = i;
                    let mut j2 = j;
                    while i2 + di < input.N && j2 + dj < input.N && S[i2 + di][j2 + dj] == '.' {
                        i2 += di;
                        j2 += dj;
                    }
                    next[i2][j2] += crt[i][j] * 0.25;
                }
            }
        }
        crt = next;
        if t >= out.len() {
            break;
        }
        let (bi, bj) = out[t];
        if S[bi][bj] == '#' {
            return (
                0,
                format!("({}, {}) is already blocked (turn {})", bi, bj, t),
                State {
                    S,
                    prob: crt,
                    lives,
                },
            );
        }
        life -= crt[bi][bj];
        crt[bi][bj] = 0.0;
        S[bi][bj] = '#';
        ret += life;
        lives.push(life);
    }
    let ub = (input.N * input.N - input.M - 1) as f64;
    let score = (ret / ub * 1e6).round() as i64;
    let err = if out.len() < input.N * input.N - input.M {
        "Not finished".to_owned()
    } else {
        String::new()
    };
    (
        score,
        err,
        State {
            S,
            prob: crt,
            lives,
        },
    )
}

/// 0 <= val <= 1
pub fn color(mut val: f64) -> String {
    val.setmin(1.0);
    val.setmax(0.0);
    let (r, g, b) = if val < 0.5 {
        let x = val * 2.0;
        (
            30. * (1.0 - x) + 144. * x,
            144. * (1.0 - x) + 255. * x,
            255. * (1.0 - x) + 30. * x,
        )
    } else {
        let x = val * 2.0 - 1.0;
        (
            144. * (1.0 - x) + 255. * x,
            255. * (1.0 - x) + 30. * x,
            30. * (1.0 - x) + 70. * x,
        )
    };
    format!(
        "#{:02x}{:02x}{:02x}",
        r.round() as i32,
        g.round() as i32,
        b.round() as i32
    )
}

#[cfg(feature = "vis")]
pub fn rect(x: usize, y: usize, w: usize, h: usize, fill: &str) -> Rectangle {
    Rectangle::new()
        .set("x", x)
        .set("y", y)
        .set("width", w)
        .set("height", h)
        .set("fill", fill)
}

#[cfg(feature = "vis")]
pub fn group(title: String) -> Group {
    Group::new().add(Title::new(title))
}

#[cfg(feature = "vis")]
pub fn vis_default(input: &Input, out: &Output) -> (i64, String, String) {
    let (mut score, err, svg) = vis(input, &out.out);
    if err.len() > 0 {
        score = 0;
    }
    (score, err, svg)
}

#[cfg(feature = "vis")]
pub fn vis(input: &Input, out: &[(usize, usize)]) -> (i64, String, String) {
    let D = 600 / input.N;
    let W = D * input.N;
    let H = W + 300;
    let (score, err, state) = compute_score_details(input, &out);
    let mut doc = svg::Document::new()
        .set("id", "vis")
        .set("viewBox", (-5, -5, W + 10, H + 10))
        .set("width", W + 10)
        .set("height", H + 10)
        .set("style", "background-color:white");
    doc = doc.add(Style::new(format!(
        "text {{text-anchor: middle;dominant-baseline: central;}}"
    )));
    for i in 0..input.N {
        for j in 0..input.N {
            if state.S[i][j] == '#' {
                if out.len() > 0 && out[out.len() - 1] == (i, j) {
                    doc = doc.add(group(format!("({}, {})", i, j)).add(rect(
                        j * D,
                        i * D,
                        D,
                        D,
                        "black",
                    )));
                } else {
                    doc = doc.add(group(format!("({}, {})", i, j)).add(rect(
                        j * D,
                        i * D,
                        D,
                        D,
                        "gray",
                    )));
                }
            } else {
                let c = format!(
                    "#FF0000{:02X}",
                    (255 + state.prob[i][j]
                        .max(f64::powi(1.03, -255))
                        .log(1.03)
                        .round() as i32)
                        .max(0)
                        .min(255)
                );
                doc = doc.add(
                    group(format!("({}, {})\nprob = {}", i, j, state.prob[i][j]))
                        .add(rect(j * D, i * D, D, D, &c))
                        .set("onclick", format!("manual_click({}, {})", i, j)),
                );
            }
        }
    }
    for i in 0..=input.N {
        doc = doc.add(
            Line::new()
                .set("x1", 0)
                .set("y1", i * D)
                .set("x2", W)
                .set("y2", i * D)
                .set("stroke", "#404040")
                .set("stroke-width", 1),
        );
    }
    for j in 0..=input.N {
        doc = doc.add(
            Line::new()
                .set("x1", j * D)
                .set("y1", 0)
                .set("x2", j * D)
                .set("y2", W)
                .set("stroke", "#404040")
                .set("stroke-width", 1),
        );
    }

    use plotters::prelude::*;
    use svg::node::Blob;

    let graph_width = W as u32 - 10;
    let graph_height = 280u32;
    let max_t = (input.N * input.N - input.M) as usize;
    let lives = &state.lives;
    let mut buf = String::new();
    {
        let area =
            SVGBackend::with_string(&mut buf, (graph_width, graph_height)).into_drawing_area();
        let mut chart = ChartBuilder::on(&area)
            .x_label_area_size(30)
            .y_label_area_size(30)
            .build_cartesian_2d(0f64..max_t as f64, 0f64..1f64)
            .unwrap();
        chart
            .configure_mesh()
            .max_light_lines(0)
            .x_label_formatter(&|v| format!("{:.0}", v))
            .draw()
            .unwrap();
        chart
            .draw_series(LineSeries::new(
                lives.iter().enumerate().map(|(t, &l)| (t as f64, l as f64)),
                &BLUE,
            ))
            .unwrap();
        area.present().unwrap();
    }
    let mut plot_group = Group::new().set("transform", format!("translate(0,{})", W + 20));
    plot_group = plot_group.add(Blob::new(buf));
    doc = doc.add(plot_group);

    (score, err, doc.to_string())
}
