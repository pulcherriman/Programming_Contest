import { Container, Graphics, Point, Text } from 'pixi.js';

export function createText(
  container: Container,
  text: string,
  color: number,
  x: number,
  y: number
): void {
  const _text = new Text(text, { fontSize: 12, fill: color });
  _text.anchor.set(0.5);
  _text.position.set(x, y);
  container.addChild(_text);
}

export function drawLine(
  graphics: Graphics,
  lineWidth: number,
  color: number,
  x1: number,
  y1: number,
  x2: number,
  y2: number
): void {
  graphics.lineStyle(lineWidth, color);
  graphics.moveTo(x1, y1);
  graphics.lineTo(x2, y2);
}

export function drawCross(
  g: Graphics,
  lineWidth: number,
  color: number,
  x1: number,
  y1: number,
  x2: number,
  y2: number
): void {
  g.lineStyle(lineWidth, color);
  g.moveTo(x1, y1);
  g.lineTo(x2, y2);
  g.moveTo(x2, y1);
  g.lineTo(x1, y2);
}

function createTrianglePath(width: number, height: number, invertY = false) {
  const path: Point[] = [];
  const y1 = invertY ? height : 0;
  const y2 = invertY ? 0 : height;
  path.push(new Point(width / 2, y1));
  path.push(new Point(width, y2));
  path.push(new Point(0, y2));
  return path;
}

function createRhombusPath(width: number, height: number) {
  const path: Point[] = [];
  path.push(new Point(width / 2, 0));
  path.push(new Point(width, height / 2));
  path.push(new Point(width / 2, height));
  path.push(new Point(0, height / 2));
  return path;
}

function createStarPath(width: number, height: number) {
  const path: Point[] = [];
  const r = Math.PI * 0.2;
  const d = [Math.min(width, height) / 2, 0];
  d[1] = d[0] * 0.4;
  const cx = width / 2;
  const cy = height / 2;
  for (let i = 0; i < 10; i++) {
    path.push(
      new Point(
        cx + d[i % 2] * Math.sin(r * i),
        cy - d[i % 2] * Math.cos(r * i)
      )
    );
  }
  return path;
}

function createRegularPolygonPath(width: number, height: number, N: number) {
  const path: Point[] = [];
  const r = (Math.PI * 2) / N;
  const d = Math.min(width, height) / 2;
  const cx = width / 2;
  const cy = height / 2;
  for (let i = 0; i < N; i++) {
    path.push(new Point(cx + d * Math.sin(r * i), cy - d * Math.cos(r * i)));
  }
  return path;
}

function createTrapezoidPath(width: number, height: number) {
  const path: Point[] = [];
  const xd = width / 5;
  const y1 = height / 6;
  const y2 = (height * 5) / 6;
  path.push(new Point(xd, y1));
  path.push(new Point(width - xd, y1));
  path.push(new Point(width, y2));
  path.push(new Point(0, y2));
  return path;
}

//Graphics.arcはセグメント数の少なさが目立ったため書き直し
function drawArcAsPoints(
  cx: number,
  cy: number,
  radius: number,
  startAngle: number,
  endAngle: number,
  points: Array<Point>
) {
  const sweep = endAngle - startAngle;
  const n = 20;
  const theta = sweep / (n * 2);
  const theta2 = theta * 2;
  const segMinus = n - 1;
  const remainder = (segMinus % 1) / segMinus;
  for (let i = 0; i <= segMinus; ++i) {
    const real = i + remainder * i;
    const angle = theta + startAngle + theta2 * real;
    const c = Math.cos(angle);
    const s = -Math.sin(angle);
    points.push(new Point(cx + c * radius, cy - s * radius));
  }
}

function createCrescentMoonPath(width: number, height: number) {
  const path: Point[] = [];
  const d = Math.min(width, height) / 2;
  const d2 = d * 0.62;
  const r1 = Math.PI * 0.14;
  const r2 = Math.PI * 0.28;
  const cx = width / 2;
  const cy = height / 2;
  drawArcAsPoints(cx, cy, d, r1, 2 * Math.PI - r1, path);
  drawArcAsPoints(cx + d * 0.5, cy, d2, 2 * Math.PI - r2, r2, path);
  return path;
}

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function createVArrowPath(width: number, height: number, upsideDown = false) {
  const path: Point[] = [];
  const y1 = upsideDown ? height : 0;
  const y2 = upsideDown ? height * 0.4 : height * 0.6;
  const y3 = upsideDown ? 0 : height;
  const x1 = 0;
  const x2 = 0 + width / 4;
  const x3 = width / 2;
  const x4 = width - width / 4;
  const x5 = width;
  path.push(new Point(x3, y1));
  path.push(new Point(x5, y2));
  path.push(new Point(x4, y2));
  path.push(new Point(x4, y3));
  path.push(new Point(x2, y3));
  path.push(new Point(x2, y2));
  path.push(new Point(x1, y2));
  return path;
}

function offsetPath(path: Point[], x: number, y: number) {
  for (const pt of path) {
    pt.x += x;
    pt.y += y;
  }
  return path;
}

export function drawShape(
  graphics: Graphics,
  type: number,
  x: number,
  y: number,
  width: number,
  height: number
): void {
  switch (type) {
    case 0:
      graphics.drawRect(x, y, width, height);
      break;
    case 1:
      graphics.drawPolygon(offsetPath(createTrianglePath(width, height), x, y));
      break;
    case 2:
      graphics.drawCircle(x + width / 2, y + height / 2, width / 2);
      break;
    case 3:
      graphics.drawPolygon(offsetPath(createRhombusPath(width, height), x, y));
      break;
    case 4:
      graphics.drawPolygon(offsetPath(createStarPath(width, height), x, y));
      break;
    case 5:
      graphics.drawPolygon(
        offsetPath(createRegularPolygonPath(width, height, 5), x, y)
      );
      break;
    case 6:
      graphics.drawRect(x, y + height / 4, width, height / 2);
      break;
    case 7:
      graphics.drawPolygon(
        offsetPath(createTrianglePath(width, height, true), x, y)
      );
      break;
    case 8:
      graphics.drawPolygon(
        offsetPath(createTrapezoidPath(width, height), x, y)
      );
      break;
    case 9:
      graphics.drawPolygon(
        offsetPath(createCrescentMoonPath(width, height), x, y)
      );
      break;
    default:
      graphics.drawRect(x, y, width, height);
  }
}
