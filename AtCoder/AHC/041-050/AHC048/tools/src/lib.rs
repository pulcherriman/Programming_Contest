#![allow(non_snake_case, unused_macros)]

use itertools::Itertools;
use proconio::input;
use rand::prelude::*;
use std::ops::RangeBounds;
use svg::node::element::{Group, Line, Rectangle, Style, Text, Title};

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

#[derive(Clone, Copy, Debug)]
pub enum Action {
    Add {
        i: usize,
        j: usize,
        k: usize,
    },
    Deliver {
        i: usize,
        j: usize,
    },
    Discard {
        i: usize,
        j: usize,
    },
    Toggle {
        i1: usize,
        j1: usize,
        i2: usize,
        j2: usize,
    },
}

#[derive(Clone, Debug)]
pub struct Input {
    pub N: usize,
    pub K: usize,
    pub H: usize,
    pub T: usize,
    pub D: i32,
    pub own: Vec<[f64; 3]>,
    pub target: Vec<[f64; 3]>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {} {} {} {}", self.N, self.K, self.H, self.T, self.D)?;
        for i in 0..self.own.len() {
            writeln!(
                f,
                "{:.5} {:.5} {:.5}",
                self.own[i][0], self.own[i][1], self.own[i][2]
            )?;
        }
        for i in 0..self.target.len() {
            writeln!(
                f,
                "{:.5} {:.5} {:.5}",
                self.target[i][0], self.target[i][1], self.target[i][2]
            )?;
        }
        Ok(())
    }
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        N: usize, K: usize, H: usize, T: usize, D: i32,
        own: [[f64; 3]; K],
        target: [[f64; 3]; H],
    }
    Input {
        N,
        K,
        H,
        T,
        D,
        own: own.into_iter().map(|x| [x[0], x[1], x[2]]).collect(),
        target: target.into_iter().map(|x| [x[0], x[1], x[2]]).collect(),
    }
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
    pub wall_v: Vec<Vec<bool>>,
    pub wall_h: Vec<Vec<bool>>,
    pub out: Vec<Action>,
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let mut f = f.split_whitespace().peekable();
    let mut wall_v = mat![false; input.N; input.N - 1];
    let mut wall_h = mat![false; input.N - 1; input.N];
    for i in 0..input.N {
        for j in 0..input.N - 1 {
            wall_v[i][j] = read(f.next(), 0..=1)? == 1;
        }
    }
    for i in 0..input.N - 1 {
        for j in 0..input.N {
            wall_h[i][j] = read(f.next(), 0..=1)? == 1;
        }
    }
    let mut out = vec![];
    while f.peek().is_some() {
        let cmd = read(f.next(), 1..=4)?;
        if cmd == 1 {
            let i = read(f.next(), 0..input.N)?;
            let j = read(f.next(), 0..input.N)?;
            let k = read(f.next(), 0..input.K)?;
            out.push(Action::Add { i, j, k });
        } else if cmd == 2 {
            let i = read(f.next(), 0..input.N)?;
            let j = read(f.next(), 0..input.N)?;
            out.push(Action::Deliver { i, j });
        } else if cmd == 3 {
            let i = read(f.next(), 0..input.N)?;
            let j = read(f.next(), 0..input.N)?;
            out.push(Action::Discard { i, j });
        } else if cmd == 4 {
            let i1 = read(f.next(), 0..input.N)?;
            let j1 = read(f.next(), 0..input.N)?;
            let i2 = read(f.next(), 0..input.N)?;
            let j2 = read(f.next(), 0..input.N)?;
            if i1.abs_diff(i2) + j1.abs_diff(j2) != 1 {
                return Err(format!(
                    "({}, {}) and ({}, {}) are not adjacent",
                    i1, j1, i2, j2
                ));
            }
            out.push(Action::Toggle { i1, j1, i2, j2 });
        } else {
            return Err(format!("Invalid command: {}", cmd));
        }
        if out.len() > input.T {
            return Err(format!("Too many actions: {} > {}", out.len(), input.T));
        }
    }
    Ok(Output {
        wall_v,
        wall_h,
        out,
    })
}

pub fn gen(seed: u64, fix_K: Option<usize>, fix_T: Option<usize>, fix_D: Option<i32>) -> Input {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed);
    let N = 20;
    let mut K = rng.gen_range(4i32..=20) as usize;
    if let Some(fix_K) = fix_K {
        K = fix_K;
    }
    let H = 1000;
    let mut T = f64::round(4000.0 * f64::powf(2.0, rng.gen_range(0.0..4.0))) as usize;
    if let Some(fix_T) = fix_T {
        T = fix_T;
    }
    let mut D = f64::round(f64::powf(10.0, rng.gen_range(1.0..4.0))) as i32;
    if let Some(fix_D) = fix_D {
        D = fix_D;
    }
    let mut own = vec![];
    for _ in 0..K {
        own.push([
            rng.gen_range(0i32..=100000) as f64 * 1e-5,
            rng.gen_range(0i32..=100000) as f64 * 1e-5,
            rng.gen_range(0i32..=100000) as f64 * 1e-5,
        ]);
    }
    let mut target = vec![];
    for _ in 0..H {
        let mut xs = (0..K).map(|_| -(rng.gen::<f64>().ln())).collect_vec();
        let sum = xs.iter().sum::<f64>();
        xs.iter_mut().for_each(|x| *x /= sum);
        target.push([
            f64::round(1e5 * xs.iter().zip(&own).map(|(x, y)| x * y[0]).sum::<f64>()) * 1e-5,
            f64::round(1e5 * xs.iter().zip(&own).map(|(x, y)| x * y[1]).sum::<f64>()) * 1e-5,
            f64::round(1e5 * xs.iter().zip(&own).map(|(x, y)| x * y[2]).sum::<f64>()) * 1e-5,
        ]);
    }
    Input {
        N,
        K,
        H,
        T,
        D,
        own,
        target,
    }
}

pub fn compute_score(input: &Input, out: &Output) -> (i64, String) {
    let (mut score, err, _) = compute_score_details(input, &out, out.out.len());
    if err.len() > 0 {
        score = 0;
    }
    (score, err)
}

pub struct State {
    pub wall_v: Vec<Vec<bool>>,
    pub wall_h: Vec<Vec<bool>>,
    pub ids: Vec<Vec<usize>>,
    pub caps: Vec<i32>,
    pub vols: Vec<f64>,
    pub colors: Vec<[f64; 3]>,
    pub delivered: Vec<[f64; 3]>,
    pub V: i32,
    pub E: f64,
}

pub fn get_ids(
    wall_v: &Vec<Vec<bool>>,
    wall_h: &Vec<Vec<bool>>,
) -> (usize, Vec<Vec<usize>>, Vec<i32>) {
    let N = wall_v.len();
    let mut ids = mat![!0; N; N];
    let mut ID = 0;
    let mut caps = vec![];
    for i in 0..N {
        for j in 0..N {
            if ids[i][j] != !0 {
                continue;
            }
            let mut stack = vec![(i, j)];
            ids[i][j] = ID;
            let mut cap = 0;
            while let Some((i, j)) = stack.pop() {
                cap += 1;
                if j + 1 < N && !wall_v[i][j] && ids[i][j + 1] == !0 {
                    ids[i][j + 1] = ID;
                    stack.push((i, j + 1));
                }
                if i + 1 < N && !wall_h[i][j] && ids[i + 1][j] == !0 {
                    ids[i + 1][j] = ID;
                    stack.push((i + 1, j));
                }
                if j > 0 && !wall_v[i][j - 1] && ids[i][j - 1] == !0 {
                    ids[i][j - 1] = ID;
                    stack.push((i, j - 1));
                }
                if i > 0 && !wall_h[i - 1][j] && ids[i - 1][j] == !0 {
                    ids[i - 1][j] = ID;
                    stack.push((i - 1, j));
                }
            }
            caps.push(cap);
            ID += 1;
        }
    }
    (ID, ids, caps)
}

fn mix(v1: f64, p1: [f64; 3], v2: f64, p2: [f64; 3]) -> [f64; 3] {
    let sum = v1 + v2;
    if sum <= 0.0 {
        return [0.0, 0.0, 0.0];
    }
    [
        (v1 * p1[0] + v2 * p2[0]) / sum,
        (v1 * p1[1] + v2 * p2[1]) / sum,
        (v1 * p1[2] + v2 * p2[2]) / sum,
    ]
}

impl State {
    pub fn new(out: &Output) -> Self {
        let (ID, ids, caps) = get_ids(&out.wall_v, &out.wall_h);
        let vols = vec![0.0; ID];
        let colors = vec![[0.0; 3]; ID];
        Self {
            wall_v: out.wall_v.clone(),
            wall_h: out.wall_h.clone(),
            ids,
            caps,
            vols,
            colors,
            V: 0,
            E: 0.0,
            delivered: vec![],
        }
    }
    pub fn apply(&mut self, input: &Input, action: Action) -> Result<(), String> {
        match action {
            Action::Add { i, j, k } => {
                self.V += 1;
                let id = self.ids[i][j];
                let w = self.caps[id] as f64 - self.vols[id];
                if w <= 1.0 {
                    self.colors[id] = mix(self.vols[id], self.colors[id], w, input.own[k]);
                    self.vols[id] = self.caps[id] as f64;
                } else {
                    self.colors[id] = mix(self.vols[id], self.colors[id], 1.0, input.own[k]);
                    self.vols[id] += 1.0;
                }
            }
            Action::Deliver { i, j } => {
                if self.delivered.len() >= input.H {
                    return Err("Cannot deliver more than H times".to_owned());
                }
                if self.vols[self.ids[i][j]] < 1.0 - 1e-6 {
                    return Err(format!(
                        "Cannot deliver: {:.10} < 1 gram",
                        self.vols[self.ids[i][j]]
                    ));
                }
                let color = self.colors[self.ids[i][j]];
                let target = input.target[self.delivered.len()];
                self.E += ((color[0] - target[0]).powi(2)
                    + (color[1] - target[1]).powi(2)
                    + (color[2] - target[2]).powi(2))
                .sqrt();
                self.vols[self.ids[i][j]] = (self.vols[self.ids[i][j]] - 1.0).max(0.0);
                self.delivered.push(color);
            }
            Action::Discard { i, j } => {
                self.vols[self.ids[i][j]] = (self.vols[self.ids[i][j]] - 1.0).max(0.0);
            }
            Action::Toggle { i1, j1, i2, j2 } => {
                if i1 == i2 {
                    // Toggle vertical wall
                    let i = i1;
                    let j = j1.min(j2);
                    self.wall_v[i][j] ^= true;
                } else {
                    // Toggle horizontal wall
                    let i = i1.min(i2);
                    let j = j1;
                    self.wall_h[i][j] ^= true;
                }
                let (ID, ids, caps) = get_ids(&self.wall_v, &self.wall_h);
                if self.ids[i1][j1] == self.ids[i2][j2] && ids[i1][j1] != ids[i2][j2] {
                    let id1 = ids[i1][j1];
                    let id2 = ids[i2][j2];
                    let v = self.vols[self.ids[i1][j1]];
                    let mut vols = vec![0.0; ID];
                    let mut colors = vec![[0.0; 3]; ID];
                    for i in 0..input.N {
                        for j in 0..input.N {
                            vols[ids[i][j]] = self.vols[self.ids[i][j]];
                            colors[ids[i][j]] = self.colors[self.ids[i][j]];
                        }
                    }
                    vols[id1] = v * caps[id1] as f64 / (caps[id1] + caps[id2]) as f64;
                    vols[id2] = v * caps[id2] as f64 / (caps[id1] + caps[id2]) as f64;
                    self.ids = ids;
                    self.caps = caps;
                    self.vols = vols;
                    self.colors = colors;
                } else if self.ids[i1][j1] != self.ids[i2][j2] && ids[i1][j1] == ids[i2][j2] {
                    let id = ids[i1][j1];
                    let id1 = self.ids[i1][j1];
                    let id2 = self.ids[i2][j2];
                    let v1 = self.vols[id1];
                    let v2 = self.vols[id2];
                    let c1 = self.colors[id1];
                    let c2 = self.colors[id2];
                    let mut vols = vec![0.0; ID];
                    let mut colors = vec![[0.0; 3]; ID];
                    for i in 0..input.N {
                        for j in 0..input.N {
                            vols[ids[i][j]] = self.vols[self.ids[i][j]];
                            colors[ids[i][j]] = self.colors[self.ids[i][j]];
                        }
                    }
                    vols[id] = v1 + v2;
                    colors[id] = mix(v1, c1, v2, c2);
                    self.ids = ids;
                    self.caps = caps;
                    self.vols = vols;
                    self.colors = colors;
                }
            }
        }
        Ok(())
    }
}

pub fn compute_score_details(input: &Input, out: &Output, t: usize) -> (i64, String, State) {
    let mut state = State::new(out);
    for i in 0..t {
        if let Err(err) = state.apply(input, out.out[i]) {
            return (0, err, state);
        }
    }
    let score = 1
        + input.D as i64 * (state.V as i64 - state.delivered.len() as i64)
        + f64::round(1e4 * state.E) as i64;
    let mut err = String::new();
    if state.delivered.len() < input.H {
        err = "Not enough deliveries".to_owned();
    }
    (score, err, state)
}

pub fn rect(x: usize, y: usize, w: usize, h: usize, fill: &str) -> Rectangle {
    Rectangle::new()
        .set("x", x)
        .set("y", y)
        .set("width", w)
        .set("height", h)
        .set("fill", fill)
}

pub fn group(title: String) -> Group {
    Group::new().add(Title::new(title))
}

pub fn vis_default(input: &Input, out: &Output) -> (i64, String, String) {
    let (mut score, err, svg) = vis(input, &out, out.out.len());
    if err.len() > 0 {
        score = 0;
    }
    (score, err, svg)
}

pub fn vis(input: &Input, out: &Output, t: usize) -> (i64, String, String) {
    let W = 600;
    let H = 720;
    let D = 30;
    let (score, err, state) = compute_score_details(input, &out, t);
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
            let id = state.ids[i][j];
            let vol = state.vols[id];
            let cap = state.caps[id];
            let color = state.colors[id];
            let mut group = group(format!(
                "({}, {})\ncolor = ({:.6},{:.6},{:.6})\nvol / cap = {:.10} / {}",
                i, j, color[0], color[1], color[2], vol, cap
            ))
            .add(rect(j * D, i * D, D, D, "white"));
            if vol / cap as f64 > 0.1 / (input.N * input.N) as f64 {
                let w = (((vol / cap as f64).sqrt() * (D - 3) as f64).round() as usize) + 3;
                // let h = 5 + ((D - 5) as f64 * (vol / cap as f64)).round() as usize;
                group = group.add(rect(
                    j * D + (D - w) / 2,
                    i * D + (D - w) / 2,
                    w,
                    w,
                    &format!(
                        "rgb({:.0},{:.0},{:.0})",
                        (1.0 - color[0]) * 255.0,
                        (1.0 - color[1]) * 255.0,
                        (1.0 - color[2]) * 255.0
                    ),
                ));
            }
            doc = doc.add(group);
        }
    }
    doc = doc.add(
        rect(0, 0, W, W, "none")
            .set("stroke", "black")
            .set("stroke-width", 3),
    );
    for i in 0..input.N {
        for j in 0..input.N {
            if j + 1 < input.N {
                if state.wall_v[i][j] {
                    doc = doc.add(
                        Line::new()
                            .set("x1", j * D + D)
                            .set("y1", i * D)
                            .set("x2", j * D + D)
                            .set("y2", (i + 1) * D)
                            .set("stroke", "black")
                            .set("stroke-width", 3),
                    );
                } else {
                    doc = doc.add(
                        Line::new()
                            .set("x1", j * D + D)
                            .set("y1", i * D)
                            .set("x2", j * D + D)
                            .set("y2", (i + 1) * D)
                            .set("stroke", "lightgray")
                            .set("stroke-width", 1),
                    );
                }
            }
            if i + 1 < input.N {
                if state.wall_h[i][j] {
                    doc = doc.add(
                        Line::new()
                            .set("x1", j * D)
                            .set("y1", i * D + D)
                            .set("x2", (j + 1) * D)
                            .set("y2", i * D + D)
                            .set("stroke", "black")
                            .set("stroke-width", 3),
                    );
                } else {
                    doc = doc.add(
                        Line::new()
                            .set("x1", j * D)
                            .set("y1", i * D + D)
                            .set("x2", (j + 1) * D)
                            .set("y2", i * D + D)
                            .set("stroke", "lightgray")
                            .set("stroke-width", 1),
                    );
                }
            }
        }
    }
    if t < out.out.len() {
        match out.out[t] {
            Action::Add { i, j, .. } | Action::Deliver { i, j } | Action::Discard { i, j } => {
                doc = doc.add(
                    rect(j * D + 3, i * D + 3, D - 6, D - 6, "none")
                        .set("stroke", "red")
                        .set("stroke-width", 3),
                );
            }
            Action::Toggle { i1, j1, i2, j2 } => {
                doc = doc.add(
                    rect(j1 * D + 3, i1 * D + 3, D - 6, D - 6, "none")
                        .set("stroke", "red")
                        .set("stroke-width", 3),
                );
                doc = doc.add(
                    rect(j2 * D + 3, i2 * D + 3, D - 6, D - 6, "none")
                        .set("stroke", "red")
                        .set("stroke-width", 3),
                );
            }
        }
    }
    for i in 0..=3 {
        doc = doc.add(
            Line::new()
                .set("x1", 0)
                .set("y1", W + D * (i + 1))
                .set("x2", W)
                .set("y2", W + D * (i + 1))
                .set("stroke", "black")
                .set("stroke-width", 1),
        );
    }
    for i in 0..=input.N {
        if i == 1 {
            continue;
        }
        doc = doc.add(
            Line::new()
                .set("x1", i * D)
                .set("y1", W + D)
                .set("x2", i * D)
                .set("y2", W + 4 * D)
                .set("stroke", "black")
                .set("stroke-width", 1),
        );
    }
    doc = doc.add(
        Text::new("i")
            .set("x", D)
            .set("y", W + D + D / 2)
            .set("font-size", 13)
            .set("fill", "black"),
    );
    doc = doc.add(
        Text::new("target[i]")
            .set("x", D)
            .set("y", W + D * 2 + D / 2)
            .set("font-size", 13)
            .set("fill", "black"),
    );
    doc = doc.add(
        Text::new("made[i]")
            .set("x", D)
            .set("y", W + D * 3 + D / 2)
            .set("font-size", 13)
            .set("fill", "black"),
    );
    let i0 = (state.delivered.len().max(10) - 10).min(input.H - 18);
    for i in i0..i0 + 18 {
        doc = doc.add(
            Text::new(format!("{i}"))
                .set("x", 2 * D + D * (i - i0) + D / 2)
                .set("y", W + D + D / 2)
                .set("font-size", 13)
                .set("fill", "black"),
        );
        if i < input.target.len() {
            let target = input.target[i];
            doc = doc.add(
                group(format!(
                    "target[{i}] = ({:.6}, {:.6}, {:.6})",
                    target[0], target[1], target[2]
                ))
                .add(rect(
                    2 * D + D * (i - i0),
                    W + D * 2,
                    D,
                    D,
                    &format!(
                        "rgb({:.0},{:.0},{:.0})",
                        (1.0 - target[0]) * 255.0,
                        (1.0 - target[1]) * 255.0,
                        (1.0 - target[2]) * 255.0
                    ),
                )),
            );
            if i < state.delivered.len() {
                let made = state.delivered[i];
                let error = ((made[0] - target[0]).powi(2)
                    + (made[1] - target[1]).powi(2)
                    + (made[2] - target[2]).powi(2))
                .sqrt();
                doc = doc.add(
                    group(format!(
                        "target[{i}] = ({:.6}, {:.6}, {:.6})\nmade[{i}] = ({:.6}, {:.6}, {:.6})\nError = {:.10}",
                        target[0], target[1], target[2], made[0], made[1], made[2], error
                    ))
                    .add(rect(
                        2 * D + D * (i - i0),
                        W + D * 3,
                        D,
                        D,
                        &format!(
                            "rgb({:.0},{:.0},{:.0})",
                            (1.0 - made[0]) * 255.0,
                            (1.0 - made[1]) * 255.0,
                            (1.0 - made[2]) * 255.0
                        ),
                    )),
                );
            }
        }
    }
    (score, err, doc.to_string())
}
