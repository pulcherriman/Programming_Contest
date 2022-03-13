import {
  Application,
  Container,
  Graphics,
  Point,
  InteractionEvent,
} from 'pixi.js';

import { Data, InputData, Plan } from '../../models';
import { ScrollBar, ScrollBarDirection, ScrollBarColors } from './scroll-bar';
import { DrawUtils } from '../';
import { shapeColors } from './color';

const gridWidth = 1;
const paddingLeft = 2;
const paddingTop = 2;
const cellWidth = 40;
const cellHeight = 40;
const cellPadding = 8;
const shapeStrokeWidth = 2;
const hangerRemoveMarkWidth = 1;
const scrollBarWidth = 16;

interface ChartColors {
  grid: number;
  text: number;
  noop: number;
  shapeSetup: number;
  colorSetup: number;
  shapeStroke: number;
  hangerRemoveMark: number;
  labelBackground: number;
}

const chartColors_light: ChartColors = {
  grid: 0x8f8f8f,
  text: 0x000000,
  noop: 0xeeeeee,
  shapeSetup: 0xc0e5ff,
  colorSetup: 0x80eeb0,
  shapeStroke: 0x000000,
  hangerRemoveMark: 0x8f6060,
  labelBackground: 0xffffff,
};
const chartColors_dark: ChartColors = {
  grid: 0x8f8f8f,
  text: 0xffffff,
  noop: 0x222222,
  shapeSetup: 0x60a0bf,
  colorSetup: 0x108e50,
  shapeStroke: 0xffffff,
  hangerRemoveMark: 0x8f6060,
  labelBackground: 0x111111,
};

const scrollBarColors_light: ScrollBarColors = {
  thumb: 0xd0d0d0,
  thumbPointerOver: 0xb8b8b8,
  thumbPointerDown: 0xa0a0a0,
  back: 0xe8e8e8,
};
const scrollBarColors_dark: ScrollBarColors = {
  thumb: 0x404848,
  thumbPointerOver: 0x606868,
  thumbPointerDown: 0x708080,
  back: 0x202020,
};

export class ChartView {
  private input: InputData | null = null;
  private plan: Plan | null = null;

  private rowCount = 0;
  private colCount = 0;
  private bottomColCount = 0;

  private chartWidth = 0;
  private chartHeight = 0;
  private _scale = 1;

  private chart = new Container();
  private grid = new Container();
  private topLabel = new Graphics();
  private leftLabel = new Graphics();
  private topLeftRect = new Graphics();

  private hScrollBar: ScrollBar | null = null;
  private vScrollBar: ScrollBar | null = null;

  private colors: ChartColors = chartColors_light;
  private scrollBarColors: ScrollBarColors = scrollBarColors_light;

  private getCellRowColumn(i: number) {
    if (!this.input) return [0, 0];
    return [Math.floor(i / this.input.H), i % this.input.H];
  }

  private getCellPosition(r: number, h: number) {
    return [(h + 1) * cellWidth, (r + 1) * cellHeight];
  }

  private createTopLeft() {
    const root = this.topLeftRect;
    root.removeChildren();
    root.clear();
    root.lineStyle(gridWidth, this.colors.grid);
    root.beginFill(this.colors.noop);
    root.drawRect(0, 0, cellWidth, cellHeight);
    root.endFill();
    this.chart.addChild(root);
  }

  private createTopLabels() {
    const root = this.topLabel;
    root.removeChildren();
    root.clear();
    {
      root.beginFill(this.colors.labelBackground);
      root.drawRect(0, 0, (this.colCount + 1) * cellWidth, cellHeight);
      root.endFill();
    }
    for (let i = 1; i <= this.colCount; ++i) {
      const x = i * cellWidth + cellWidth / 2;
      const y = cellHeight / 2;
      DrawUtils.createText(root, String(i), this.colors.text, x, y);
    }
    for (let i = 1; i < this.colCount + 2; ++i) {
      const x1 = i * cellWidth;
      const y1 = 0;
      const y2 = cellHeight;
      DrawUtils.drawLine(root, gridWidth, this.colors.grid, x1, y1, x1, y2);
    }
    {
      const x1 = 0;
      const y1 = 0;
      const y2 = y1 + cellHeight;
      const x2 = (this.colCount + 1) * cellWidth;
      DrawUtils.drawLine(root, gridWidth, this.colors.grid, x1, y1, x2, y1);
      DrawUtils.drawLine(root, gridWidth, this.colors.grid, x1, y2, x2, y2);
    }
    this.chart.addChild(root);
  }

  private createLeftLabels() {
    const root = this.leftLabel;
    root.removeChildren();
    root.clear();
    {
      root.beginFill(this.colors.labelBackground);
      root.drawRect(0, 0, cellWidth, (this.rowCount + 1) * cellHeight);
      root.endFill();
    }
    for (let i = 1; i <= this.rowCount; ++i) {
      const x = cellWidth / 2;
      const y = i * cellHeight + cellHeight / 2;
      DrawUtils.createText(root, String(i), this.colors.text, x, y);
    }
    for (let i = 1; i < this.rowCount + 2; ++i) {
      const x1 = 0;
      const y1 = i * cellHeight;
      const x2 = cellWidth;
      DrawUtils.drawLine(root, gridWidth, this.colors.grid, x1, y1, x2, y1);
    }
    {
      const x1 = 0;
      const x2 = x1 + cellWidth;
      const y1 = cellHeight;
      const y2 = (this.rowCount + 1) * cellHeight;
      DrawUtils.drawLine(root, gridWidth, this.colors.grid, x1, y1, x1, y2);
      DrawUtils.drawLine(root, gridWidth, this.colors.grid, x2, y1, x2, y2);
    }
    this.chart.addChild(root);
  }

  private drawSetupSpace(
    graphics: Graphics,
    startIndex: number,
    endIndex: number,
    color: number,
    yOffset: number,
    height: number
  ) {
    if (!this.input) return;
    const [re, he] = this.getCellRowColumn(endIndex);
    for (let [r, h] = this.getCellRowColumn(startIndex); r <= re; h = 0, r++) {
      const h2 = r == re ? he : this.input.H - 1;
      const [x, y] = this.getCellPosition(r, h);
      graphics.beginFill(color);
      graphics.drawRect(x, y + yOffset, cellWidth * (h2 - h + 1), height);
      graphics.endFill();
    }
  }

  private drawShape(
    graphics: Graphics,
    x: number,
    y: number,
    index: number,
    shape: number,
    color: number | null,
    lineAlpha: number
  ) {
    graphics.lineStyle({
      color: this.colors.shapeStroke,
      width: shapeStrokeWidth,
      alpha: lineAlpha,
    });
    const size = Math.min(cellWidth, cellHeight) - cellPadding * 2;
    if (color != null) graphics.beginFill(color);
    DrawUtils.drawShape(
      graphics,
      shape,
      x + cellPadding,
      y + cellHeight - size - cellPadding,
      size,
      size
    );
    if (color != null) graphics.endFill();
  }

  private drawHangerRemoveMark(g: Graphics, x: number, y: number) {
    const size = (cellWidth - cellPadding * 2) / 8;
    const cx = x + cellWidth / 2;
    const cy = y + cellHeight / 2;
    DrawUtils.drawCross(
      g,
      hangerRemoveMarkWidth,
      this.colors.hangerRemoveMark,
      cx - size,
      cy - size,
      cx + size,
      cy + size
    );
  }

  private createGrid() {
    if (!this.input || !this.plan) return;
    const root = this.grid;
    const insts = this.plan.instructions;
    root.removeChildren();
    // draw background
    {
      const background = new Graphics();
      root.addChild(background);
      const g = background;
      // draw noop
      for (let i = 0; i < this.plan.K; ++i) {
        if (insts[i].s >= 0) continue;
        const [r, h] = this.getCellRowColumn(i);
        const [x, y] = this.getCellPosition(r, h);
        background.beginFill(this.colors.noop);
        background.drawRect(x, y, cellWidth, cellHeight);
        background.endFill();
      }
      // draw setup space
      {
        let prevInstIndex = -1;
        for (let i = 0; i < this.plan.K; ++i) {
          if (insts[i].s < 0) continue;
          if (prevInstIndex >= 0) {
            this.drawSetupSpace(
              background,
              prevInstIndex + 1,
              Math.min(
                prevInstIndex +
                  this.input.A_ss[insts[prevInstIndex].s][insts[i].s],
                i
              ),
              this.colors.shapeSetup,
              0,
              cellHeight / 2
            );
            this.drawSetupSpace(
              background,
              prevInstIndex + 1,
              Math.min(
                prevInstIndex +
                  this.input.B_cc[insts[prevInstIndex].c][insts[i].c],
                i
              ),
              this.colors.colorSetup,
              cellHeight / 2,
              cellHeight / 2
            );
          }
          prevInstIndex = i;
        }
      }
      // draw shape
      {
        const hanger = new Array<number>(this.input.H).fill(-1);
        for (let i = 0; i < this.plan.K; ++i) {
          const [r, h] = this.getCellRowColumn(i);
          const [x, y] = this.getCellPosition(r, h);
          if (insts[i].s < 0) {
            if (insts[i].s == -1) {
              hanger[h] = -1;
              this.drawHangerRemoveMark(background, x, y);
            }
            if (hanger[h] >= 0) {
              this.drawShape(background, x, y, i, hanger[h], null, 0.5);
            }
          } else {
            this.drawShape(
              background,
              x,
              y,
              i,
              insts[i].s,
              shapeColors[insts[i].c % shapeColors.length],
              0.8
            );
            hanger[h] = insts[i].s;
          }
        }
      }
      // draw horizontal grid
      for (let i = 0; i < this.rowCount + 2; ++i) {
        const x1 = cellWidth;
        const y1 = i * cellHeight;
        const x2 =
          ((i == this.rowCount + 1 ? this.bottomColCount : this.colCount) + 1) *
          cellWidth;
        DrawUtils.drawLine(g, gridWidth, this.colors.grid, x1, y1, x2, y1);
      }
      // draw vertical grid
      for (let i = 0; i < this.colCount + 2; ++i) {
        const x1 = i * cellWidth;
        const y1 = cellHeight;
        const y2 =
          (this.rowCount + (this.bottomColCount + 1 < i ? 0 : 1)) * cellHeight;
        DrawUtils.drawLine(g, gridWidth, this.colors.grid, x1, y1, x1, y2);
      }
    }
    this.chart.addChild(root);
  }

  private createHScrollBar() {
    const left = cellWidth * this._scale;
    const hScrollBar = new ScrollBar(
      this.app.stage,
      ScrollBarDirection.Horizontal,
      scrollBarWidth,
      this.chartWidth - left - scrollBarWidth,
      this.scrollBarColors
    );
    hScrollBar.position.set(left, this.chartHeight - scrollBarWidth);
    hScrollBar.pageSize = this.chartWidth - left - scrollBarWidth;
    hScrollBar.documentSize = cellWidth * this.colCount;
    hScrollBar.documentSize *= this._scale;
    const onChange = () => {
      if (!this.hScrollBar || !this.vScrollBar) return;
      this.grid.position.set(-hScrollBar.scroll, -this.vScrollBar.scroll);
      this.topLabel.position.set(-hScrollBar.scroll, 0);
    };
    hScrollBar.on('change', onChange);
    onChange();
    this.chart.addChild((this.hScrollBar = hScrollBar));
  }

  private createVScrollBar() {
    const top = cellHeight * this._scale;
    const vScrollBar = new ScrollBar(
      this.app.stage,
      ScrollBarDirection.Vertical,
      scrollBarWidth,
      this.chartHeight - top - scrollBarWidth,
      this.scrollBarColors
    );
    vScrollBar.position.set(this.chartWidth - scrollBarWidth, top);
    vScrollBar.pageSize = this.chartHeight - top - scrollBarWidth;
    vScrollBar.documentSize = cellHeight * this.rowCount;
    vScrollBar.documentSize *= this._scale;
    const onChange = () => {
      if (!this.hScrollBar || !this.vScrollBar) return;
      this.grid.position.set(-this.hScrollBar.scroll, -vScrollBar.scroll);
      this.leftLabel.position.set(0, -vScrollBar.scroll);
    };
    vScrollBar.on('change', onChange);
    onChange();
    this.chart.addChild((this.vScrollBar = vScrollBar));
  }

  private createGridMask() {
    // make mask
    const root = this.grid;
    const scale = this._scale;
    if (!this.vScrollBar || !this.hScrollBar) return;
    {
      const left = cellWidth * scale;
      const top = cellHeight * scale;
      const g = new Graphics();
      g.beginFill(0);
      g.drawRect(
        paddingLeft + left,
        paddingTop + top,
        this.chartWidth - left - (this.vScrollBar.visible ? scrollBarWidth : 0),
        this.chartHeight - top - (this.hScrollBar.visible ? scrollBarWidth : 0)
      );
      g.endFill();
      root.mask = g;
    }
  }

  private onPointerOver(x: number, y: number, text: string) {
    const tooltip = document.getElementById('tooltip');
    if (!tooltip) return;
    tooltip.setAttribute(
      'style',
      `left: ${x}px; top: ${y}px; visibility: visible;`
    );
    tooltip.innerHTML = `<p>${text}</p>`;
  }

  private onPointerOut() {
    const tooltip = document.getElementById('tooltip');
    if (!tooltip) return;
    tooltip.setAttribute('style', `visibility: hidden;`);
  }

  private updatePointerPos(pos: Point) {
    if (!this.input || !this.plan || !this.vScrollBar || !this.hScrollBar) {
      return;
    }
    const scale = this._scale;
    const rect = this.app.view.getBoundingClientRect();
    if (pos.x < 0 || pos.y < 0 || pos.x >= rect.width || pos.y >= rect.height) {
      this.onPointerOut();
      return;
    }
    const row = Math.floor(
      (pos.y - cellHeight * scale + this.vScrollBar.scroll) / cellHeight / scale
    );
    const column = Math.floor(
      (pos.x - cellWidth * scale + this.hScrollBar.scroll) / cellWidth / scale
    );
    if (
      row < 0 ||
      row >= this.rowCount ||
      column < 0 ||
      column >= this.colCount ||
      (row == this.rowCount - 1 && column >= this.bottomColCount)
    ) {
      this.onPointerOut();
      return;
    }
    const index = row * this.input.H + column;
    const inst = this.plan.instructions[index];
    const text = inst.s < 0 ? `(${inst.s})` : `(${inst.s + 1}, ${inst.c + 1})`;
    this.onPointerOver(
      window.scrollX + rect.left + pos.x,
      window.scrollY + rect.top + pos.y,
      text
    );
  }

  private setEventListener() {
    const stageOnPointermove = (e: InteractionEvent) => {
      this.updatePointerPos(e.data.global);
    };
    const containerOnRemoved = () => {
      this.app.stage.off('pointermove', stageOnPointermove);
      this.grid.off('removed', containerOnRemoved);
    };
    this.app.stage.on('pointermove', stageOnPointermove);
    this.grid.on('removed', containerOnRemoved);
  }

  private createChartMask() {
    const g = new Graphics();
    g.beginFill(0);
    g.drawRect(paddingLeft, paddingTop, this.chartWidth, this.chartHeight);
    g.endFill();
    this.chart.mask = g;
  }

  private draw() {
    if (!this.input || !this.plan) return;
    this.chart.removeChildren();
    this.createGrid();
    this.createTopLabels();
    this.createLeftLabels();
    this.createTopLeft();
    this.applyScale();
    this.setEventListener();
  }

  private applyScale() {
    const scale = this._scale;
    for (const cont of [
      this.grid,
      this.topLeftRect,
      this.topLabel,
      this.leftLabel,
    ]) {
      cont.scale.set(scale, scale);
    }
    for (const cont of [this.hScrollBar, this.vScrollBar]) {
      if (cont && cont.parent) {
        cont.parent.removeChild(cont);
      }
    }
    this.createHScrollBar();
    this.createVScrollBar();
    this.createGridMask();
  }

  private onResize() {
    this.chartWidth = this.app.screen.width - paddingLeft;
    this.chartHeight = this.app.screen.height - paddingTop;
    this.createChartMask();
    this.applyScale();
  }

  set scale(value: number) {
    this._scale = Math.exp(value / 10);
    this.applyScale();
  }

  constructor(private app: Application) {
    app.stage.addChild(this.chart);
    this.chart.x = paddingLeft;
    this.chart.y = paddingTop;
    this.chartWidth = this.app.screen.width - paddingLeft;
    this.chartHeight = this.app.screen.height - paddingTop;
    app.renderer.on('resize', () => {
      this.onResize();
    });
    this.createChartMask();
  }

  hide(): void {
    this.chart.visible = false;
  }

  show(): void {
    this.chart.visible = true;
  }

  update(data: Data): void {
    this.input = data.input;
    this.plan = data.plan;

    this.rowCount = Math.ceil(this.plan.K / this.input.H);
    this.colCount = this.input.H;
    this.bottomColCount = ((this.plan.K - 1) % this.input.H) + 1;

    this.draw();
  }

  setColorMode(mode: 'light' | 'dark'): void {
    this.colors = mode == 'light' ? chartColors_light : chartColors_dark;
    this.scrollBarColors =
      mode == 'light' ? scrollBarColors_light : scrollBarColors_dark;
    this.draw();
  }
}
