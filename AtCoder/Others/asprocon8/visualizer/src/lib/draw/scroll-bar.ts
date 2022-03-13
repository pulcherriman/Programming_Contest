import { Container, Graphics, InteractionEvent, Point } from 'pixi.js';

export const ScrollBarDirection = {
  Vertical: 'vertical',
  Horizontal: 'horizontal',
} as const;
type ScrollBarDirection =
  typeof ScrollBarDirection[keyof typeof ScrollBarDirection];

const PointerState = {
  Out: 'out',
  Over: 'over',
  Down: 'down',
} as const;
type PointerState = typeof PointerState[keyof typeof PointerState];

type PointerEventListener = (e: InteractionEvent) => void;

export interface ScrollBarColors {
  thumb: number;
  back: number;
  thumbPointerOver?: number;
  thumbPointerDown?: number;
}

export class ScrollBar extends Container {
  private _pageSize = 10;
  private _documentSize = 100;
  private _scroll = 0;
  private back: Graphics;
  private thumb: Graphics;
  private isDragging = false;
  private dragStartPos: Point = new Point();
  private _thumbState: PointerState = PointerState.Out;
  private eventListeners = new Map<string, PointerEventListener>();

  get pageSize(): number {
    return this._pageSize;
  }
  set pageSize(value: number) {
    this._pageSize = value;
    this.update();
  }
  get documentSize(): number {
    return this._documentSize;
  }
  set documentSize(value: number) {
    this._documentSize = value;
    this.update();
  }
  get scroll(): number {
    return this._scroll;
  }
  set scroll(value: number) {
    value = Math.max(0, Math.min(value, this._documentSize - this._pageSize));
    if (this._scroll == value) return;
    this._scroll = value;
    this.update();
    this.emit('change', this._scroll);
  }
  private set thumbState(value: PointerState) {
    this._thumbState = value;
    this.drawThumb();
  }

  private calcThumbPosition(): number {
    return (this._scroll / this._documentSize) * this.length;
  }

  private calcThumbLength(): number {
    return (this.length * this._pageSize) / this._documentSize;
  }

  private drawThumb() {
    const thumb = this.thumb;
    thumb.clear();
    if (this._pageSize < this._documentSize) {
      thumb.beginFill(
        this._thumbState == PointerState.Down &&
          this.colors.thumbPointerDown != null
          ? this.colors.thumbPointerDown
          : this._thumbState == PointerState.Over &&
            this.colors.thumbPointerOver != null
          ? this.colors.thumbPointerOver
          : this.colors.thumb
      );
      const thumbLength = this.calcThumbLength();
      const thumbPos = this.calcThumbPosition();
      if (this.direction == ScrollBarDirection.Vertical) {
        thumb.drawRect(0, 0, this.barWidth, thumbLength);
      } else {
        thumb.drawRect(0, 0, thumbLength, this.barWidth);
      }
      thumb.endFill();
      if (this.direction == ScrollBarDirection.Vertical) {
        thumb.position.set(0, thumbPos);
      } else {
        thumb.position.set(thumbPos, 0);
      }
    }
  }

  private update() {
    if (this._pageSize < this._documentSize) {
      this.visible = true;
      this.drawThumb();
    } else {
      this.visible = false;
    }
  }

  private enableEventListeners() {
    this.eventListeners.forEach(
      (handler: PointerEventListener, name: string) => {
        (name == 'pointermove' ? this.stage : this.thumb).on(name, handler);
      }
    );
  }

  private disableEventListeners() {
    this.eventListeners.forEach(
      (handler: PointerEventListener, name: string) => {
        (name == 'pointermove' ? this.stage : this.thumb).off(name, handler);
      }
    );
  }

  private scrollOnePage() {
    if (!this.isDragging) return;
    const pt = this.dragStartPos;
    const x = this.direction == ScrollBarDirection.Vertical ? pt.y : pt.x;
    if (x < this.calcThumbPosition()) {
      this.scroll -= this._pageSize;
    } else if (x > this.calcThumbPosition() + this.calcThumbLength()) {
      this.scroll += this._pageSize;
    }
    setTimeout(() => {
      this.scrollOnePage();
    }, 100);
  }

  constructor(
    private stage: Container,
    private direction: ScrollBarDirection,
    private barWidth: number,
    private length: number,
    private colors: ScrollBarColors
  ) {
    super();
    stage.interactive = true;

    this.eventListeners.set('pointermove', (e: InteractionEvent) => {
      const pos = e.data.getLocalPosition(this);
      const delta =
        (this.direction == ScrollBarDirection.Vertical
          ? pos.y - this.dragStartPos.y
          : pos.x - this.dragStartPos.x) *
        (this._documentSize / this.length);
      this.scroll += delta;
      this.dragStartPos = pos;
    });
    this.eventListeners.set('pointerupoutside', () => {
      this.disableEventListeners();
      this.isDragging = false;
      this.thumbState = PointerState.Out;
    });
    this.eventListeners.set('pointerup', () => {
      this.disableEventListeners();
      this.isDragging = false;
      this.thumbState = PointerState.Over;
    });

    const back = new Graphics();
    back.beginFill(this.colors.back);
    if (this.direction == ScrollBarDirection.Vertical) {
      back.drawRect(0, 0, this.barWidth, this.length);
    } else {
      back.drawRect(0, 0, this.length, this.barWidth);
    }
    back.endFill();
    back.interactive = true;
    back.buttonMode = true;
    const back_stageOnPointermove = (e: InteractionEvent) => {
      this.dragStartPos = e.data.getLocalPosition(this);
    };
    back.on('pointerdown', (e: InteractionEvent) => {
      this.dragStartPos = e.data.getLocalPosition(this);
      this.isDragging = true;
      this.scrollOnePage();
      back.on('pointerup', backOnDragEnd);
      back.on('pointerupoutside', backOnDragEnd);
      stage.on('pointermove', back_stageOnPointermove);
    });
    const backOnDragEnd = () => {
      back.off('pointerup', backOnDragEnd);
      back.off('pointerupoutside', backOnDragEnd);
      stage.off('pointermove', back_stageOnPointermove);
      this.isDragging = false;
    };
    this.addChild(back);

    const thumb = new Graphics();
    thumb.interactive = true;
    thumb.buttonMode = true;
    thumb.on('pointerover', () => {
      if (!this.isDragging) this.thumbState = PointerState.Over;
    });
    thumb.on('pointerout', () => {
      if (!this.isDragging) this.thumbState = PointerState.Out;
    });
    thumb.on('pointerdown', (e: InteractionEvent) => {
      this.isDragging = true;
      this.dragStartPos = e.data.getLocalPosition(this);
      this.thumbState = PointerState.Down;
      this.enableEventListeners();
    });
    this.addChild(thumb);

    this.back = back;
    this.thumb = thumb;
    this.update();
  }
}
