declare var GIF: any; // for https://github.com/jnordberg/gif.js
declare var Module: any;

interface MSG {
  WORD_EOF: string;
  WORD_NL: string;
  NOT_NUM: string;
  NL_EOF: string;
  NL_WORD: string;
  NOT_EQ: string;
  INFO: string;
  GIF_REOPEN: string;
  GIF_WAIT: string;
  DESCRIPTION1: string;
  DESCRIPTION2: string;
  DESCRIPTION3: string;
}
const MSG_JA: MSG = {
  WORD_EOF: "a word expected, but EOF",
  WORD_NL: "a word expected, but newline",
  NOT_NUM: "a number expected, but word ",
  NL_EOF: "newline expected, but EOF",
  NL_WORD: "newline expected, but word ",
  NOT_EQ: "エラー: 入力と出力のreactiveNに齟齬があります。",
  INFO: "\n(指定しているファイルを間違えているか、正しい方法でoutputのファイルが作成されていない可能性が高いです。ご確認ください。)",
  GIF_REOPEN:
    'GIFファイルを作成するには、 このビジュアライザを "file://" ではなく、 "http://" で開かないといけない可能性があります(前者でも大丈夫なこともあります)。 例えば、 "$ python -m SimpleHTTPServer 8000" などとして下さい。',
  GIF_WAIT:
    "GIF作成にしばらく時間がかかります。およそ二分ほどです。 (GIFはサイズが大きくなる可能性が高いので、ある程度scaleを小さくしておくことを推奨します。)",
  DESCRIPTION1:
    "全体的な設備負荷率やペナルティ、稼働時間を把握するのに適したモードです。<br>縦軸は設備、横軸は週を表しており、それぞれのマスは、上側で平日の情報を、下側で休日の情報を表しています。さらに、各マス内のオブジェクトは、縦方向で設備負荷率を、横方向で稼働時間のタイプを示しています。<br>(ここでは見やすさのため、一週間分の稼働パターンをまとめて表していることに注意してください。本来、一週間は5日分の平日パターンと2日分の休日パターンで構成されています。)<br>そして色は、青から赤になるにつれて、納期遅れ注文数（delayの場合）、もしくは、稼働パターンのコスト（costの場合）が大きいことを示しています。<br>また、scaleを拡大させると文字による情報も追加で現れます。",
  DESCRIPTION2:
    "具体的な注文や作業がどのように割り振られているのかを把握するのに適したモードです。<br>縦軸は設備、横軸は週を表しています。<br>特に、delayやcostのモードと異なり、本モードでは正確に設備の稼働パターンを表現していることに注意してください。灰色の部分が設備の稼働時間帯を示しています。色がついている部分は各作業の開始から終了までの時間を示しており、色自体は当該作業とその前の工程の作業との、開始時間の差を表現しています。なお、もし前工程が無ければ時間差は0としています。<br>また、scaleを最大まで拡大させると文字による情報も追加で現れます。",
  DESCRIPTION3:
    "基本的にはwork(waiting time)と同じですが、このモードでは色が各注文毎に塗り分けられています。<br>また、scaleを最大まで拡大させると文字による情報も追加で現れます。",
};
const MSG_EN: MSG = {
  WORD_EOF: "a word expected, but EOF",
  WORD_NL: "a word expected, but newline",
  NOT_NUM: "a number expected, but word ",
  NL_EOF: "newline expected, but EOF",
  NL_WORD: "newline expected, but word ",
  NOT_EQ: "AssertionError: Input reactiveN and output reactiveN is not equal.",
  INFO: "\n(It is most likely that you have specified the wrong file or that you have not created the OUTPUT file in the correct way. Please check.)",
  GIF_REOPEN:
    'to use this feature, you might have to re-open this file via "http://", instead of "file://". e.g. you can use "$ python -m SimpleHTTPServer 8000"',
  GIF_WAIT:
    "please wait for a while, about 2 minutes. (the GIF can be large in size, so we recommend setting the scale as small as possible.)",
  DESCRIPTION1:
    "This mode is suitable for seeing overall load factor of machines, penalties, and operating time.<br>The vertical axis represents machines and the horizontal axis represents weeks, with each cell representing weekday information at the top and holiday information at the bottom.<br>In addition, the objects within the cells indicate the load factor of the machine in the vertical direction and the type of operating time in the horizontal direction.<br>(Note that here, for ease of viewing, a week's operating pattern are represented together.Originally, A week consists of a 5-day weekday pattern and a 2-day holiday pattern.)<br>Plus, the color goes from blue to red, indicating the number of delayed orders (in the delay mode) or the cost of the operating pattern (in the cost mode) is larger.<br>When the scale is enlarged, additional textual information appears.",
  DESCRIPTION2:
    "This mode is suitable for seeing how specific orders and works are assigned.<br>The vertical axis represents machines and the horizontal axis represents weeks.<br>Note that this mode accurately represents the operating pattern of machines, unlike the delay mode and cost mode.<br>The gray area indicates the machine's operating time period.<br>The colored area indicates the time of each work, and the color itself represents the difference in start time between the work and the work in the previous step. If there is no previous step, the time difference is set to 0.<br>When the scale is enlarged to the maximum, additional textual information appears.",
  DESCRIPTION3:
    "This mode is basically the same as the work (waiting time) mode, but in this mode, works of the same order are shown in the same color.<br>When the scale is enlarged to the maximum, additional textual information appears.",
};

enum Lang {
  EN,
  JA,
}

let lang: Lang = Lang.JA;
let msg: MSG = MSG_JA;

// 以下のモジュールはビジュアライザの内容自体ではありません
// This module is not the content of the visualizer itself
module framework {
  export class FileParser {
    private filename: string;
    private content: string[][];
    private y: number;
    private x: number;

    constructor(filename: string, content: string) {
      this.filename = filename;
      this.content = [];
      for (const line of content.split("\n")) {
        const words = line.trim().split(new RegExp("\\s+"));
        this.content.push(words);
      }
      this.y = 0;
      this.x = 0;
    }

    public getWord(): string {
      if (this.content.length <= this.y) {
        this.reportError(msg.WORD_EOF);
      }
      if (this.content[this.y].length <= this.x) {
        this.reportError(msg.WORD_NL);
      }
      const word = this.content[this.y][this.x];
      this.x += 1;
      return word;
    }
    public getInt(): number {
      const word = this.getWord();
      if (!word.match(new RegExp("^[-+]?[0-9]+$"))) {
        this.reportError(msg.NOT_NUM + JSON.stringify(this.content[this.y][this.x]));
      }
      return parseInt(word);
    }
    public getNewline() {
      if (this.content.length <= this.y) {
        this.reportError(msg.NL_WORD);
      }
      if (this.x < this.content[this.y].length) {
        this.reportError(msg.NL_WORD + JSON.stringify(this.content[this.y][this.x]));
      }
      this.x = 0;
      this.y += 1;
    }

    public unwind() {
      if (this.x == 0) {
        this.y -= 1;
        this.x = this.content[this.y].length - 1;
      } else {
        this.x -= 1;
      }
    }
    public reportError(m: string) {
      m = `${this.filename}: line ${this.y + 1}: ${m}`;
      alert(m + msg.INFO);
      throw new Error(m);
    }
  }

  export class FileSelector {
    public callback: (inputContent: string, outputContent: string) => void;

    private inputFile: HTMLInputElement;
    private outputFile: HTMLInputElement;
    private reloadButton: HTMLInputElement;
    private inputDoneButton: HTMLInputElement;
    private check_box: HTMLInputElement;
    private seed_input: HTMLInputElement;

    private generated_inputContent: string;

    private inputTextArea: HTMLTextAreaElement;
    private outputTextArea: HTMLTextAreaElement;

    constructor() {
      this.inputFile = <HTMLInputElement>document.getElementById("inputFile");
      this.outputFile = <HTMLInputElement>document.getElementById("outputFile");
      this.reloadButton = <HTMLInputElement>document.getElementById("reloadButton");
      this.inputDoneButton = <HTMLInputElement>document.getElementById("inputDoneButton");
      this.check_box = <HTMLInputElement>document.getElementById("inputCheckbox");
      this.seed_input = <HTMLInputElement>document.getElementById("inputSeedNumber");

      this.check_box.addEventListener("change", this.onChangeCheck.bind(this));
      this.seed_input.addEventListener("change", this.onChangeSeed.bind(this));

      this.generated_inputContent = "";

      this.inputTextArea = <HTMLTextAreaElement>document.getElementById("inputContainer");
      this.outputTextArea = <HTMLTextAreaElement>document.getElementById("outputContainer");

      this.reloadFilesClosure = () => {
        this.reloadFiles();
      };
      this.inputFile.addEventListener("change", this.reloadFilesClosure);
      this.outputFile.addEventListener("change", this.reloadFilesClosure);
      this.reloadButton.addEventListener("click", this.reloadFilesClosure);
      this.inputDoneButton.addEventListener("click", this.reloadFilesClosure);
    }

    private onChangeSeed(): void {
      const seed = parseInt(this.seed_input.value, 10);
      this.generated_inputContent = Module.ccall("generate_input", "string", ["number"], [seed]);
      this.inputTextArea.innerHTML =
        this.generated_inputContent.split("\n").slice(0, 4).join("\n") + "\n...";
    }

    private onChangeCheck(): void {
      const check_box = <HTMLInputElement>document.getElementById("inputCheckbox");
      const hidden_area = <HTMLElement>document.getElementById("hidden_area");
      if (check_box.checked) {
        hidden_area.style.display = "block";
        this.inputFile.disabled = true;
        this.outputFile.disabled = true;
        this.onChangeSeed();
      } else {
        hidden_area.style.display = "none";
        this.inputFile.disabled = false;
        this.outputFile.disabled = false;
      }
    }

    private reloadFilesClosure: () => void;
    reloadFiles() {
      if (this.check_box.checked) {
        if (this.generated_inputContent == "") {
          // 理論上はあり得ない
          alert("Input is not generated. Please reload the page and try again.");
          throw new Error("Input is not generated.");
        }
        const inputContent = this.generated_inputContent;
        const outputContent = this.outputTextArea.value;
        this.reloadButton.classList.remove("disabled");
        if (this.callback !== undefined) {
          this.callback(inputContent, outputContent);
        }
      } else {
        if (this.inputFile.files.length == 0 || this.outputFile.files.length == 0) return;
        loadFile(this.inputFile.files[0], (inputContent: string) => {
          loadFile(this.outputFile.files[0], (outputContent: string) => {
            this.inputFile.removeEventListener("change", this.reloadFilesClosure);
            this.outputFile.removeEventListener("change", this.reloadFilesClosure);
            this.reloadButton.classList.remove("disabled");
            if (this.callback !== undefined) {
              this.callback(inputContent, outputContent);
            }
          });
        });
      }
    }
  }

  export class RichSeekBar {
    public callback: (value: number) => void;

    private seekRange: HTMLInputElement;
    private seekNumber: HTMLInputElement;
    private fpsInput: HTMLInputElement;
    private firstButton: HTMLInputElement;
    private prevButton: HTMLInputElement;
    private playButton: HTMLInputElement;
    private nextButton: HTMLInputElement;
    private lastButton: HTMLInputElement;
    private runIcon: HTMLElement;
    private intervalId: number;
    private playClosure: () => void;
    private stopClosure: () => void;

    public now_running: Boolean;

    constructor() {
      this.seekRange = <HTMLInputElement>document.getElementById("seekRange");
      this.seekNumber = <HTMLInputElement>document.getElementById("seekNumber");
      this.fpsInput = <HTMLInputElement>document.getElementById("fpsInput");
      this.firstButton = <HTMLInputElement>document.getElementById("firstButton");
      this.prevButton = <HTMLInputElement>document.getElementById("prevButton");
      this.playButton = <HTMLInputElement>document.getElementById("playButton");
      this.nextButton = <HTMLInputElement>document.getElementById("nextButton");
      this.lastButton = <HTMLInputElement>document.getElementById("lastButton");
      this.runIcon = document.getElementById("runIcon");
      this.intervalId = null;
      this.now_running = false;

      this.setMinMax(-1, -1);
      this.seekRange.addEventListener("change", () => {
        this.setValue(parseInt(this.seekRange.value));
      });
      this.seekNumber.addEventListener("change", () => {
        this.setValue(parseInt(this.seekNumber.value) - 1);
      });
      this.seekRange.addEventListener("input", () => {
        this.setValue(parseInt(this.seekRange.value));
      });
      this.seekNumber.addEventListener("input", () => {
        this.setValue(parseInt(this.seekNumber.value) - 1);
      });
      this.fpsInput.addEventListener("change", () => {
        if (this.intervalId !== null) {
          this.play();
        }
      });
      this.firstButton.addEventListener("click", () => {
        this.stop();
        this.setValue(this.getMin());
      });
      this.prevButton.addEventListener("click", () => {
        this.stop();
        this.setValue(this.getValue() - 1);
      });
      this.nextButton.addEventListener("click", () => {
        this.stop();
        this.setValue(this.getValue() + 1);
      });
      this.lastButton.addEventListener("click", () => {
        this.stop();
        this.setValue(this.getMax());
      });
      this.playClosure = () => {
        this.play();
      };
      this.stopClosure = () => {
        this.stop();
      };
      this.playButton.addEventListener("click", this.playClosure);
    }

    public setMinMax(min: number, max: number) {
      this.seekRange.min = min.toString();
      this.seekNumber.min = (min + 1).toString();
      this.seekRange.max = max.toString();
      this.seekNumber.max = (max + 1).toString();
      this.seekRange.step = this.seekNumber.step = "1";
      this.setValue(min);
    }
    public getMin(): number {
      return parseInt(this.seekRange.min);
    }
    public getMax(): number {
      return parseInt(this.seekRange.max);
    }

    public setValue(value: number) {
      if (isNaN(value)) return;
      value = Math.max(this.getMin(), Math.min(this.getMax(), value)); // clamp
      this.seekRange.value = value.toString();
      this.seekNumber.value = (value + 1).toString();
      if (this.callback !== undefined) {
        this.callback(value);
      }
    }
    public getValue(): number {
      return parseInt(this.seekRange.value);
    }

    public getDelay(): number {
      const fps = parseInt(this.fpsInput.value);
      return Math.floor(1000 / fps);
    }
    private resetInterval() {
      if (this.intervalId !== undefined) {
        clearInterval(this.intervalId);
        this.intervalId = undefined;
      }
    }
    public play() {
      this.playButton.removeEventListener("click", this.playClosure);
      this.playButton.addEventListener("click", this.stopClosure);
      this.runIcon.classList.remove("play");
      this.runIcon.classList.add("stop");
      this.now_running = true;
      if (this.getValue() == this.getMax()) {
        // if last, go to first
        this.setValue(this.getMin());
      }
      this.resetInterval();
      this.intervalId = window.setInterval(() => {
        if (this.getValue() == this.getMax()) {
          this.stop();
        } else {
          this.setValue(this.getValue() + 1);
        }
      }, this.getDelay());
    }
    public stop() {
      this.playButton.removeEventListener("click", this.stopClosure);
      this.playButton.addEventListener("click", this.playClosure);
      this.runIcon.classList.remove("stop");
      this.runIcon.classList.add("play");
      this.now_running = false;
      this.resetInterval();
    }
  }

  const loadFile = (file: File, callback: (value: string) => void) => {
    const reader = new FileReader();
    reader.readAsText(file);
    reader.onloadend = function () {
      if (reader.result == null || reader.result instanceof ArrayBuffer) {
        return;
      }
      callback(reader.result);
    };
  };

  const saveUrlAsLocalFile = (url: string, filename: string) => {
    const anchor = document.createElement("a");
    anchor.href = url;
    anchor.download = filename;
    const evt = document.createEvent("MouseEvent");
    evt.initEvent("click", true, true);
    anchor.dispatchEvent(evt);
  };

  export class FileExporter {
    constructor(canvas: HTMLCanvasElement, seek: RichSeekBar) {
      const saveAsImage = <HTMLInputElement>document.getElementById("saveAsImage");
      const saveAsVideo = <HTMLInputElement>document.getElementById("saveAsVideo");

      saveAsImage.addEventListener("click", () => {
        saveUrlAsLocalFile(canvas.toDataURL("image/png"), "canvas.png");
      });

      saveAsVideo.addEventListener("click", () => {
        if (location.href.match(new RegExp("^file://"))) {
          alert(msg.GIF_REOPEN);
        }
        seek.stop();
        if (confirm(msg.GIF_WAIT)) {
          const gif = new GIF({
            quality: 10,
            repeat: -1,
          });
          for (let i = seek.getMin(); i <= seek.getMax(); ++i) {
            console.log(`gif progress: ${i}/${seek.getMax()}`);
            seek.setValue(i);
            gif.addFrame(canvas, { copy: true, delay: seek.getDelay() });
          }
          gif.on("finished", function (blob: Blob) {
            saveUrlAsLocalFile(URL.createObjectURL(blob), "canvas.gif");
          });
          gif.render();
        }
      });
    }
  }
}

module visualizer {
  // 以下c++からの移植コードが続きます。 本質的には"class Visualizer"からが重要です
  // The important part of the visualizer is starting from "class Visualizer"

  // Problem.h
  const HOUR: number = 3600;
  const DAY: number = 86400;
  const WEEK: number = DAY * 7;

  const calendarTypeN: number = 9;

  class calendarType {
    public pattern: [number, number][][] = [
      [], // pattern 1
      [[9 * HOUR, 12 * HOUR]], // pattern 2
      [[13 * HOUR, 18 * HOUR]], // pattern 3
      [
        [9 * HOUR, 12 * HOUR],
        [13 * HOUR, 18 * HOUR],
      ], // pattern 4
      [
        [9 * HOUR, 12 * HOUR],
        [13 * HOUR, 20 * HOUR],
      ], // pattern 5
      [
        [9 * HOUR, 12 * HOUR],
        [13 * HOUR, 22 * HOUR],
      ], // pattern 6
      [
        [9 * HOUR, 12 * HOUR],
        [13 * HOUR, 24 * HOUR],
      ], // pattern 7
      [
        [9 * HOUR, 12 * HOUR],
        [13 * HOUR, 26 * HOUR],
      ], // pattern 8
      [
        [9 * HOUR, 12 * HOUR],
        [13 * HOUR, 28 * HOUR],
      ], // pattern 9
    ];

    addcalendar(calendar: [number, number][], week: number, typeA: number, typeB: number) {
      let offset: number = WEEK * week;
      for (let i = 0; i < 5; i++) {
        this.pattern[typeA].forEach((e) => {
          calendar.push([e[0] + offset, e[1] + offset]);
        });
        offset += DAY;
      }
      for (let i = 0; i < 2; i++) {
        this.pattern[typeB].forEach((e) => {
          calendar.push([e[0] + offset, e[1] + offset]);
        });
        offset += DAY;
      }
    }
  }

  class Item {
    public itemNo: number;
    public itemProcN: number; // 工程数 ... number of process
    public proc: number[]; // i番目の工程の資源 ... resources of the i-th process
    public prodTimeRange: [number, number];
  }

  class Resource {
    public resNo: number;
    public procNo: number;

    public costRatio: number = 1.0;
    public calendar1CostRatio: number = 1.0;
    public calendar0CostRatio: number = 0;

    // 入力生成用 ... Parameters for generating input
    public calendarTypeXRatio: number[];
    public workerN: number; // 稼働に必要な作業者数 ... required workers
    public costPerHour: number; // 作業員の時給
    public costPerHourNight: number; // 夜勤時給
    public resDemand: number = 0.0; // 工程需要(この工程を通る品目が生成される確率)
  }

  class Operation {
    public opNo: number;
    public itemNo: number;
    public prodTime: number[] = [];
    public let: number;
  }

  class InputFile {
    public procN; // 工程種類数 ... Number of types of process
    public procDemand: number[]; // 工程需要(ある品目が工程を通る確率) ... Process demand (probability of being selected for a certain item's process)
    public resDemandMutationRatio: number[]; // 資源需要の変化率 ... Rate of change in resource demand
    public procResSet: Set<number>[]; //

    public addCostHoliday: number = (1.2 / 5.0) * 2.0; // 休日の追加コスト ... Additional holiday costs

    public originalcalendar: string[]; // the calendar to use for generating input

    public calendar: [number, number][][]; // i番目の資源の稼働時間は，[calendar[i][j].first, calendar[i][j].second)のリストで表される ... The working time of the i-th resource is represented by the list [calendar[i][j].first, calendar[i][j].second).

    public itemN: number; // 製品数 ... Number of Items
    public resourceN: number; // 資源数 ... Number of Resources
    public operationN: number; // 作業数 ... Number of Operations
    public itemList: Item[] = [];
    public resourceList: Resource[] = [];
    public opList: Operation[] = [];

    public costTypeA: Map<string, number> = new Map(); // 平日の稼働パターンのコスト ... Cost of working pattern on weekdays
    public costTypeB: Map<string, number> = new Map(); // 休日の稼働パターンのコスト ... Cost of working pattern on holiday

    public week: number;
    public rescalendarChangeLimitN: number;
    public reactiveN: number;

    constructor(content: string) {
      const parser = new framework.FileParser("<input-file>", content);

      this.week = parser.getInt();
      parser.getNewline();
      this.rescalendarChangeLimitN = parser.getInt();
      parser.getNewline();
      this.reactiveN = parser.getInt();
      parser.getNewline();
      this.itemN = parser.getInt();
      parser.getNewline();

      for (let i = 0; i < this.itemN; i++) {
        const e = new Item();
        e.itemNo = parser.getInt();
        e.itemProcN = parser.getInt();
        parser.getNewline();
        e.prodTimeRange = [0, 0];
        e.prodTimeRange[0] = parser.getInt();
        e.prodTimeRange[1] = parser.getInt();
        parser.getNewline();
        e.proc = Array(e.itemProcN);
        for (let j = 0; j < e.itemProcN; j++) {
          e.proc[j] = parser.getInt();
        }
        parser.getNewline();
        this.itemList.push(e);
      }

      this.resourceN = parser.getInt();
      parser.getNewline();
      for (let i = 0; i < this.resourceN; i++) {
        const e = new Resource();
        e.resNo = parser.getInt();
        parser.getNewline();
        e.procNo = parser.getInt();
        e.resDemand = parser.getInt();
        e.workerN = parser.getInt();
        e.costPerHour = parser.getInt();
        e.costPerHourNight = parser.getInt();
        parser.getNewline();
        e.costRatio = Number(parser.getWord());
        e.calendar0CostRatio = Number(parser.getWord());
        e.calendar1CostRatio = Number(parser.getWord());
        parser.getNewline();
        e.calendarTypeXRatio = [];
        for (let i = 0; i < calendarTypeN; i++) {
          e.calendarTypeXRatio.push(Number(parser.getWord()));
        }
        parser.getNewline();
        this.resourceList.push(e);
      }

      this.operationN = parser.getInt();
      parser.getNewline();
      for (let i = 0; i < this.operationN; i++) {
        const e = new Operation();
        e.opNo = parser.getInt();
        e.itemNo = parser.getInt();
        e.let = parser.getInt();
        parser.getNewline();
        const procN: number = this.itemList[e.itemNo].itemProcN;
        e.prodTime = Array(procN);
        for (let j = 0; j < procN; j++) {
          e.prodTime[j] = parser.getInt();
        }
        parser.getNewline();
        this.opList.push(e);
      }

      const sz = parser.getInt();
      parser.getNewline();
      for (let e = 0; e < sz; e++) {
        const i = Math.floor(e / calendarTypeN);
        const k = e % calendarTypeN;
        const costA = parser.getInt();
        const costB = parser.getInt();
        parser.getNewline();
        this.costTypeA.set([i, k].join(","), costA);
        this.costTypeB.set([i, k].join(","), costB);
      }

      this.procN = parser.getInt();
      parser.getNewline();
      this.procDemand = Array(this.procN);
      for (let i = 0; i < this.procN; i++) {
        this.procDemand[i] = parseFloat(parser.getWord());
        parser.getNewline();
      }

      this.calendar = Array(this.resourceN);
      this.originalcalendar = Array(this.resourceN);

      for (let i = 0; i < this.resourceN; i++) {
        const sz = parser.getInt();
        parser.getNewline();
        this.calendar[i] = Array(sz);
        for (let j = 0; j < sz; j++) {
          const fi = parser.getInt();
          const se = parser.getInt();
          this.calendar[i][j] = [fi, se];
          parser.getNewline();
        }
        for (let j = 0; j < this.resourceN; j++) {
          this.originalcalendar[j] = parser.getWord();
          parser.getNewline();
        }
      }

      this.addCostHoliday = parseFloat(parser.getWord());
      parser.getNewline();

      console.log("input done.");
    }

    public N: number;

    // 資源i週j における稼働時間の総和を求める
    // Calculate the total working time of resource i week j
    GetResourceTotalTime(calendar: [number, number][][]): Map<string, number> {
      let t: Map<string, number> = new Map();
      let res: number = 0;
      calendar.forEach((i) => {
        i.forEach((j) => {
          if (!(j[0] < j[1])) {
            const msg: string = `Assertion Error: !(j[0] < j[1])`;
            alert(msg);
            throw new Error(msg);
          }
          const key: string = [res, Math.floor((j[0] - 4 * 3600) / WEEK)].join(",");
          if (t.has(key)) {
            t.set(key, t.get(key) + j[1] - j[0]);
          } else {
            t.set(key, j[1] - j[0]);
          }
        });
        res++;
      });
      return t;
    }

    sequenceForward(
      icalendar: [number, number][][],
      strcalendar: string[]
    ): [
      number,
      number,
      Map<string, number>,
      Map<string, number>,
      Map<string, number>,
      Map<string, number[]>
    ] {
      const t3: number[] = Array(this.resourceN).fill(0); // ESSEE
      const ridx: number[] = Array(this.resourceN).fill(0); // ESSEE

      const base: Map<string, number> = this.GetResourceTotalTime(icalendar); // ユーザーに渡された総稼働時間
      const used: Map<string, number> = new Map(); // 作業を処理した時間
      const let_cnt: Map<string, number> = new Map();

      // visualizer用変数 Variables for Visualizer
      const vis1_resource: Map<string, number> = new Map();
      const vis2_optimes: Map<string, number[]> = new Map();
      //

      let changeLimitViolationCnt = 0;
      for (let i = 0; i < this.resourceN; i++) {
        if (strcalendar[i].length != this.week * 2) {
          const msg: string = `Assertion Error: strcalendar[i].length() != week * 2`;
          alert(msg);
          throw new Error(msg);
        }
        let cntCh = 0;
        for (let j = 0; j < this.week * 2 - 2; j++) {
          if (strcalendar[i][j] != strcalendar[i][j + 2]) cntCh++;
        }
        changeLimitViolationCnt += Math.max(0, cntCh - this.rescalendarChangeLimitN);
      }

      // 初期化
      for (let i = 0; i < this.resourceN; i++) {
        for (let j = 0; j < this.week; j++) {
          used.set([i, j].join(","), 0);
          let_cnt.set([i, j].join(","), 0);
        }
      }

      const that = this;
      function Assign(op: Operation, opn: number) {
        // [( startTime, endTime ), ... ]
        let lstAssigned: [number, number][] = [[-1, 0]];
        let lstAssignedTotalTime = 1;

        let assignedList: [number, number][][] = Array(that.itemList[op.itemNo].itemProcN);
        for (let i = 0; i < assignedList.length; i++) {
          assignedList[i] = [];
        }

        for (let i = 0; i < that.itemList[op.itemNo].itemProcN; i++) {
          const res: number = that.itemList[op.itemNo].proc[i];
          const prod: number = op.prodTime[i];
          let remainProd: number = prod;

          lstAssigned.forEach((startTime_and_endTime) => {
            const startTime: number = startTime_and_endTime[0];
            const endTime: number = startTime_and_endTime[1];
            const curProd: number = Math.floor(
              ((endTime - startTime) * prod) / lstAssignedTotalTime
            );
            let remainCurProd: number = curProd;
            remainProd -= curProd;

            let est: number = Math.max(startTime, t3[res]);
            while (icalendar[res][ridx[res]][1] <= est + 0.1) ridx[res]++;
            est = Math.max(est, icalendar[res][ridx[res]][0]);

            // とりあえず前詰めをする。 ... First, front justification
            // 後詰めの場合は前詰めするときの最後の終わり時間から開始時間を探します。 ... In the case of back justification, the start time is searched from the last end time when front justified.
            while (remainCurProd > 0.1) {
              let curStartTime: number = 0;
              let curEndTime: number = 0;
              // ESSEE
              if (endTime - est >= remainCurProd - 0.1) {
                curEndTime = endTime;
                curStartTime = curEndTime - remainCurProd;
              } else {
                curStartTime = est;
                curEndTime = curStartTime + remainCurProd;
              }

              if (curEndTime >= icalendar[res][ridx[res]][1] - 0.1) {
                curEndTime = icalendar[res][ridx[res]][1];
                ridx[res]++;
                est = icalendar[res][ridx[res]][0];
              }

              t3[res] = curEndTime;
              remainCurProd -= curEndTime - curStartTime;
              assignedList[i].push([curStartTime, curEndTime]);
            }
          });

          while (remainProd > 0.1) {
            // 小数の問題があるので、微妙な判定条件に
            const est = t3[res];
            const curStartTime = est;
            let curEndTime = est + remainProd;
            if (curEndTime >= icalendar[res][ridx[res]][1] - 0.1) {
              curEndTime = icalendar[res][ridx[res]][1];
              ridx[res]++;
            }

            t3[res] = curEndTime;
            remainProd -= curEndTime - curStartTime;
            assignedList[i].push([curStartTime, curEndTime]);
          }

          // 終わり時間から逆算する  ... calculate backwards from the end time
          const endTime: number = assignedList[i].slice(-1)[0][1];
          let bidx: number = ridx[res];
          remainProd = prod;
          assignedList[i].length = 0;

          while (remainProd > 0.1) {
            while (icalendar[res][bidx][0] >= endTime - 0.1) bidx--;
            let curStartTime = icalendar[res][bidx][0];
            const curEndTime = Math.min(icalendar[res][bidx][1], endTime);

            if (curEndTime - curStartTime > remainProd + 0.1)
              curStartTime = curEndTime - remainProd;
            bidx--;

            remainProd -= curEndTime - curStartTime;
            assignedList[i].push([curStartTime, curEndTime]);
          }

          // 追加変数
          let vis2_optimes_data: number[] = [];
          //

          assignedList[i].reverse();
          assignedList[i].forEach((startTime_and_endTime) => {
            const startTime: number = startTime_and_endTime[0];
            const endTime: number = startTime_and_endTime[1];

            // 追加変数 (終了時刻のset) DAY/4は6時スタートで時刻を考えている為、そのズレを修正する用
            // popを挟んでいるのは、前回のendTime==今回のstartTimeとなることがあるので、処理を軽くする為にしている
            if (
              vis2_optimes_data.length > 0 &&
              vis2_optimes_data[vis2_optimes_data.length - 1] ===
                Math.min(WEEK * that.week + DAY / 4, startTime)
            ) {
              vis2_optimes_data.pop();
              vis2_optimes_data.push(Math.min(WEEK * that.week + DAY / 4, endTime));
            } else {
              vis2_optimes_data.push(Math.min(WEEK * that.week + DAY / 4, startTime));
              vis2_optimes_data.push(Math.min(WEEK * that.week + DAY / 4, endTime));
            }
            //

            const curWeek = Math.floor((startTime - 4 * 3600) / WEEK);
            if (curWeek < that.week) {
              const key: string = [res, curWeek].join(",");
              if (used.has(key)) {
                used.set(key, used.get(key) + endTime - startTime);
              } else {
                used.set(key, endTime - startTime);
              }
            }
          });

          lstAssigned = assignedList[i];
          lstAssignedTotalTime = prod;

          // 追加変数
          vis2_optimes_data.sort((a, b) => (a < b ? -1 : 1));
          vis1_resource.set([opn, i].join(","), res);
          vis2_optimes.set([opn, i].join(","), vis2_optimes_data);
          //
        }

        const let_: boolean = lstAssigned.slice(-1)[0][1] > op.let;
        if (let_) {
          // 納期遅れしてたら，該当作業の終了時刻に属する 週にメモを入れる ... Check week including processing time for let operation
          const se: Set<[number, number]> = new Set();
          let i: number = 0;
          assignedList.forEach((vec) => {
            const res = that.itemList[op.itemNo].proc[i];
            vec.forEach((startTime_and_endTime) => {
              const startTime: number = startTime_and_endTime[0];
              // const endTime: number = startTime_and_endTime[1];
              const curWeek = Math.floor((startTime - 4 * 3600) / WEEK);
              if (curWeek < that.week) se.add([res, curWeek]);
            });
            i++;
          });
          se.forEach((p) => {
            const key: string = p.join(",");
            if (let_cnt.has(key)) {
              let_cnt.set(key, let_cnt.get(key) + 1);
            } else {
              let_cnt.set(key, 1);
            }
          });
        }
        return let_;
      }
      let let_: number = 0;
      for (let i = 0; i < this.operationN; i++) {
        const letFlag: boolean = Assign(this.opList[i], i);
        let_ += letFlag === true ? 1 : 0;
      }

      // assert( used.size() == base.size() );
      const loadRate: Map<string, number> = new Map();

      used.forEach((e1, e0) => {
        //value,key
        if (isNaN(e1)) {
          const msg: string = `Assertion Error: NaN found`;
          alert(msg);
          throw new Error(msg);
        }
        if (e0.slice(e0.search(",")) == this.week.toString()) {
          return;
        }
        if (!base.has(e0)) {
          base.set(e0, 0);
        }
        loadRate.set(e0, e1 / Math.max(1.0, base.get(e0)));
      });

      return [let_, changeLimitViolationCnt, loadRate, let_cnt, vis1_resource, vis2_optimes];
    }
  }

  class OutputFile {
    public resoucesN: number;
    public weeks: number;
    public queries: string[][] = [];

    constructor(content: string) {
      const parser = new framework.FileParser("<output-file>", content);

      parser.getInt();
      parser.getNewline();

      this.resoucesN = parser.getInt();
      this.weeks = parser.getInt();
      const queries_num: number = parser.getInt();
      parser.getNewline();

      this.queries = Array(queries_num);
      for (let i = 0; i < queries_num; i++) {
        this.queries[i] = Array(this.resoucesN);
        for (let j = 0; j < this.resoucesN; j++) {
          const answer = parser.getWord();
          if (answer.length != 2 * this.weeks) {
            console.log(answer);
            alert(`query:${i + 1} resource:${j + 1}\n` + "output is not correct format.");
            throw new Error("AssertionError");
          }
          for (let idx = 0; idx < answer.length; idx++) {
            const x = parseInt(answer.charAt(idx));
            if (!(1 <= x && x <= 9)) {
              console.log(x);
              alert(`query:${i + 1} resource:${j + 1}\n` + "output is not correct format.");
              throw new Error("AssertionError");
            }
          }
          this.queries[i][j] = answer;
          parser.getNewline();
        }
      }

      console.log("output done.");
    }
  }

  class TesterFrame {
    public age: number;
    public score: number;
    public query: string[];
    public calendar: [number, number][][];
    public loadRate: Map<string, number>;
    public letOpCount: Map<string, number>;
    public penalty: Map<string, number> = new Map();

    // ビジュアライザ用変数 Variables for Visualizer
    // key -> (注文に関するインデックス, 工程に関するインデックス)
    // key -> (order index, step index)

    // value -> この工程を処理する設備のインデックス
    // value -> Index of machine that handles this step
    public vis1_resource: Map<string, number>;
    // value -> この工程に関する設備の稼働時間の配列
    // value -> Array of operating time for this step
    public vis2_optimes: Map<string, number[]>;
    // value -> 同じ注文に関する前工程との開始時間の差 (前工程が存在しない場合は0)
    // value -> Difference in start time from the previous step (0 if no previous step exists)
    public vis3_waiting_time: Map<string, number>;
    // ビジュアライズに際して基準となる値 (厳密に中央値ではない)
    // Reference value for visualization
    public vis3_waiting_time_mid: number;

    constructor(input: InputFile, output: OutputFile, idx: number, calendar: calendarType) {
      this.age = idx;
      this.query = output.queries[idx];

      this.calendar = Array(input.resourceN);
      for (let i = 0; i < this.calendar.length; i++) {
        this.calendar[i] = [];
      }
      let cost: number = 0;

      for (let i = 0; i < input.resourceN; i++) {
        for (let j = 0; j < input.week; j++) {
          const calendarTypeA: number = parseInt(this.query[i].slice(j * 2, j * 2 + 1), 10) - 1;
          const calendarTypeB: number = parseInt(this.query[i].slice(j * 2 + 1, j * 2 + 2), 10) - 1;

          calendar.addcalendar(this.calendar[i], j, calendarTypeA, calendarTypeB);

          let cTA: number = input.costTypeA.get([i, calendarTypeA].join(","));
          let cTB: number = input.costTypeB.get([i, calendarTypeB].join(","));
          if (isNaN(cTA)) cTA = 0;
          if (isNaN(cTB)) cTB = 0;
          cost += cTA + cTB;

          // for visualizer
          this.penalty.set([i, j].join(","), cTA + cTB);
        }
      }
      for (let j = 0; j < input.resourceN; j++) {
        this.calendar[j].push([1e9, 2e9]);
      }
      const res_of_sequenceForward = input.sequenceForward(this.calendar, this.query);
      const let_: number = res_of_sequenceForward[0];
      const chLimVioCnt: number = res_of_sequenceForward[1];
      this.loadRate = res_of_sequenceForward[2];
      this.letOpCount = res_of_sequenceForward[3];

      // 追加変数
      this.vis1_resource = res_of_sequenceForward[4];
      this.vis2_optimes = res_of_sequenceForward[5];
      this.vis3_waiting_time = new Map();
      for (var i = 0; i < input.operationN; i++) {
        for (var j = 0; j < input.itemList[input.opList[i].itemNo].itemProcN; j++) {
          const key = [i, j].join(",");
          if (j == 0) {
            this.vis3_waiting_time.set(key, 0);
          } else {
            this.vis3_waiting_time.set(
              key,
              this.vis2_optimes.get(key)[0] - this.vis2_optimes.get([i, j - 1].join(","))[0]
            );
          }
        }
      }
      const temp: number[] = Array.from(this.vis3_waiting_time.values());
      temp.sort((a, b) => a - b);
      let _i = 0;
      for (; _i < temp.length; _i++) {
        if (temp[_i] > 0) {
          break;
        }
      }
      this.vis3_waiting_time_mid = temp[Math.floor((_i + temp.length - 2) / 2)] * 2;
      this.vis3_waiting_time_mid = Math.max(1, this.vis3_waiting_time_mid);
      //

      const curScore =
        let_ + chLimVioCnt == 0 ? Math.round((10.0 - Math.log10(cost / input.week)) * 1e9) : 0;
      this.score = curScore;
    }
  }

  class Tester {
    public frames: TesterFrame[];

    public input: InputFile;
    public output: OutputFile;
    public bestScore: number;

    constructor(inputContent: string, outputContent: string) {
      this.frames = [];
      this.input = new InputFile(inputContent);
      this.output = new OutputFile(outputContent);
      this.bestScore = 0;

      if (this.input.reactiveN != this.output.queries.length) {
        alert(msg.NOT_EQ + msg.INFO);
        throw new Error(msg.NOT_EQ);
      }

      const calendar = new calendarType();
      for (let k = 0; k < this.input.reactiveN; k++) {
        const new_frame = new TesterFrame(this.input, this.output, k, calendar);
        this.frames.push(new_frame);
        this.bestScore = Math.max(this.bestScore, new_frame.score);
      }

      console.log("Tester done.");
    }
  }

  class Visualizer {
    private canvas: HTMLCanvasElement;
    private ctx: CanvasRenderingContext2D;

    private week_Input: HTMLInputElement;
    private itemN_Input: HTMLInputElement;
    private resourceN_Input: HTMLInputElement;
    private score_this_frame_Input: HTMLInputElement;
    private score_Input: HTMLInputElement;

    public operationcon_cf_Input: HTMLInputElement;
    public operationcon_rb_Input: HTMLInputElement;
    public letonly_Input: HTMLInputElement;
    public cost_Input: HTMLInputElement;

    public expansion_plus: HTMLInputElement;
    public expansion_minus: HTMLInputElement;
    public scale_level: number = 8;
    public scales: number[] = [
      0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 2.0, 3.0, 4.0, 5.0, 7.5, 10.0, 15.0,
    ];

    private color_palette: number[] = [
      (0 * 256) / 19,
      (8 * 256) / 19,
      (16 * 256) / 19,
      (5 * 256) / 19,
      (13 * 256) / 19,
      (2 * 256) / 19,
      (10 * 256) / 19,
      (18 * 256) / 19,
      (7 * 256) / 19,
      (15 * 256) / 19,
      (4 * 256) / 19,
      (12 * 256) / 19,
      (1 * 256) / 19,
      (9 * 256) / 19,
      (17 * 256) / 19,
      (6 * 256) / 19,
      (14 * 256) / 19,
      (3 * 256) / 19,
      (11 * 256) / 19,
    ];

    constructor() {
      this.canvas = <HTMLCanvasElement>document.getElementById("canvas");
      const size = 800;
      this.canvas.height = size;
      this.canvas.width = size;
      const temp = this.canvas.getContext("2d");
      if (temp == null) {
        alert("unsupported browser");
        return;
      }
      this.ctx = temp;
      this.week_Input = <HTMLInputElement>document.getElementById("week_Input");
      this.expansion_plus = <HTMLInputElement>document.getElementById("expansion_plus");
      this.expansion_minus = <HTMLInputElement>document.getElementById("expansion_minus");
      this.operationcon_cf_Input = <HTMLInputElement>(
        document.getElementById("operationcon_colorful")
      );
      this.operationcon_rb_Input = <HTMLInputElement>document.getElementById("operationcon_rb");
      this.letonly_Input = <HTMLInputElement>document.getElementById("letonly");
      this.cost_Input = <HTMLInputElement>document.getElementById("cost");
      this.itemN_Input = <HTMLInputElement>document.getElementById("chlim_Input");
      this.resourceN_Input = <HTMLInputElement>document.getElementById("resourceN_Input");
      this.score_this_frame_Input = <HTMLInputElement>(
        document.getElementById("score_now_frame_Input")
      );
      this.score_Input = <HTMLInputElement>document.getElementById("score_Input");
    }

    private draw_operation(
      x: number,
      w: number,
      y: number,
      h: number,
      i: number,
      is_wake: boolean,
      color_mode: boolean // true->colorful false->rb
    ): void {
      if (color_mode) {
        if (is_wake) {
          this.ctx.fillStyle = `hsl(${this.color_palette[i % this.color_palette.length]},80%,60%)`;
        } else {
          this.ctx.fillStyle = `hsl(${
            this.color_palette[i % this.color_palette.length]
          },80%,60%,20%)`;
        }
      } else {
        const r1 = 255;
        const g1 = 31;
        const b1 = 31;
        const r2 = 30;
        const g2 = 144;
        const b2 = 255;
        const r = Math.floor((r1 - r2) * i + r2);
        const g = Math.floor((g1 - g2) * i + g2);
        const b = Math.floor((b1 - b2) * i + b2);
        if (is_wake) {
          this.ctx.fillStyle = `rgb(${r},${g},${b})`;
        } else {
          this.ctx.fillStyle = `rgba(${r},${g},${b},0.2)`;
        }
      }
      this.ctx.fillRect(x, y, w, h);
    }

    private draw_calendar_color_map(
      x: number,
      y: number,
      w: number,
      h: number,
      calendarType: number,
      loadRate: number,
      color: number
    ) {
      color = Math.min(Math.max(color, 0), 255);
      const r1 = 255;
      const g1 = 31;
      const b1 = 31;
      const r2 = 30;
      const g2 = 144;
      const b2 = 255;
      const r = Math.floor(((r1 - r2) * color) / 256 + r2);
      const g = Math.floor(((g1 - g2) * color) / 256 + g2);
      const b = Math.floor(((b1 - b2) * color) / 256 + b2);
      this.draw_calendar(x, y, w, h, calendarType, loadRate, r, g, b);
    }
    private draw_calendar(
      x: number,
      y: number,
      w: number,
      h: number,
      calendarType: number,
      loadRate: number,
      r: number,
      g: number,
      b: number
    ): void {
      x -= (6 * w) / 24;
      this.ctx.strokeRect(x + (6 * w) / 24, y, w, h);
      this.ctx.fillStyle = `rgb(${r}, ${g}, ${b})`;
      h = Math.floor(h / 10 + (h * 9 * loadRate) / 10);
      if (calendarType == 1) {
        // None
      } else if (calendarType == 2) {
        this.ctx.fillRect(x + (9 * w) / 24, y, (3 * w) / 24, h);
      } else if (calendarType == 3) {
        this.ctx.fillRect(x + (13 * w) / 24, y, (5 * w) / 24, h);
      } else if (calendarType == 4) {
        this.ctx.fillRect(x + (9 * w) / 24, y, (3 * w) / 24, h);
        this.ctx.fillRect(x + (13 * w) / 24, y, (5 * w) / 24, h);
      } else if (calendarType == 5) {
        this.ctx.fillRect(x + (9 * w) / 24, y, (3 * w) / 24, h);
        this.ctx.fillRect(x + (13 * w) / 24, y, (7 * w) / 24, h);
      } else if (calendarType == 6) {
        this.ctx.fillRect(x + (9 * w) / 24, y, (3 * w) / 24, h);
        this.ctx.fillRect(x + (13 * w) / 24, y, (9 * w) / 24, h);
      } else if (calendarType == 7) {
        this.ctx.fillRect(x + (9 * w) / 24, y, (3 * w) / 24, h);
        this.ctx.fillRect(x + (13 * w) / 24, y, (11 * w) / 24, h);
      } else if (calendarType == 8) {
        this.ctx.fillRect(x + (9 * w) / 24, y, (3 * w) / 24, h);
        this.ctx.fillRect(x + (13 * w) / 24, y, (13 * w) / 24, h);
      } else if (calendarType == 9) {
        this.ctx.fillRect(x + (9 * w) / 24, y, (3 * w) / 24, h);
        this.ctx.fillRect(x + (13 * w) / 24, y, (15 * w) / 24, h);
      } else {
        const msg: string = `Invalid calendar type: ${calendarType + 1}`;
        alert(msg);
        throw new Error(msg);
      }
    }

    public draw(frame: TesterFrame, tester: Tester) {
      // update input tags
      this.week_Input.value = tester.input.week.toString();
      this.itemN_Input.value = tester.input.rescalendarChangeLimitN.toString();
      this.resourceN_Input.value = tester.input.resourceN.toString();
      this.score_this_frame_Input.value = frame.score.toLocaleString();
      this.score_Input.value = tester.bestScore.toLocaleString();

      const left_margin = 110;
      const right_margin = 70;
      const top_margin = 60;
      const bottom_margin = 10;
      const cellw = 100;
      const cellh_margin = 20;
      const cellh = 50 + cellh_margin;
      const scale = this.scales[this.scale_level];

      const quality = 1.25; // 解像度が低い問題を解決している
      const w = tester.input.week * cellw * scale + left_margin + right_margin;
      const h = tester.input.resourceN * cellh + top_margin + bottom_margin;
      this.canvas.width = w * quality;
      this.canvas.height = h * quality;
      this.ctx.scale(quality, quality);

      this.canvas.style.width = w + "px";
      this.canvas.style.height = h + "px";
      // canvasの最大寸法はMDN公式によると、高さ・幅、共に32767pixels(ただ、これは古い情報っぽい? 念の為これに従う) scaleの最大倍率は15倍
      // weekの最大値は16でresouceNの最大値は20
      // よって、(scale分を考慮しても)確実に制限内に収まる

      this.ctx.fillStyle = "white";
      this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
      this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);

      this.ctx.font = "20px serif";
      this.ctx.fillStyle = "Black";

      this.ctx.textAlign = "center";
      this.ctx.fillText(
        (frame.age + 1).toString() + "/" + tester.input.reactiveN.toString(),
        left_margin / 2,
        top_margin / 2
      );
      for (let i = 0; i < tester.input.week; i++) {
        this.ctx.fillText(
          (this.scale_level > 4 ? "week" : "") + (i + 1).toString().padStart(2, "0"),
          (i + 0.5) * cellw * scale + left_margin,
          top_margin / 2
        );
      }
      for (let i = 0; i < tester.input.resourceN; i++) {
        this.ctx.fillText(
          (this.scale_level > 4 ? "machine" : "") + (i + 1).toString().padStart(2, "0"),
          left_margin / 2,
          (i + 0.5) * cellh + top_margin
        );
      }

      const detail_level = 9;
      if (this.letonly_Input.checked) {
        this.ctx.font = "12px serif";
        for (var i = 0; i < tester.input.resourceN; i++) {
          for (var j = 0; j < tester.input.week; j++) {
            const key = [i, j].join(",");
            this.draw_calendar_color_map(
              j * cellw * scale + left_margin,
              i * cellh + top_margin,
              cellw * scale,
              ((cellh - cellh_margin) * 5) / 7,
              parseInt(frame.query[i].slice(2 * j, 2 * j + 1)),
              frame.loadRate.get(key),
              Math.floor(255 - 510 / (2 + frame.letOpCount.get(key)))
            );
            this.draw_calendar_color_map(
              j * cellw * scale + left_margin,
              i * cellh + ((cellh - cellh_margin) * 5) / 7 + top_margin,
              cellw * scale,
              ((cellh - cellh_margin) * 2) / 7,
              parseInt(frame.query[i].slice(2 * j + 1, 2 * j + 2)),
              frame.loadRate.get(key),
              Math.floor(255 - 510 / (2 + frame.letOpCount.get(key)))
            );
            if (this.scale_level >= detail_level) {
              this.ctx.fillText(
                "delay:" +
                  frame.letOpCount.get(key).toString() +
                  "/loadRate:" +
                  (100 * Math.min(1, frame.loadRate.get(key))).toFixed(1) +
                  "%",
                (j + 0.5) * cellw * scale + left_margin,
                (i + 0.93) * cellh + top_margin
              );
            }
          }
        }
      }
      if (this.cost_Input.checked) {
        this.ctx.font = "12px serif";
        for (var i = 0; i < tester.input.resourceN; i++) {
          for (var j = 0; j < tester.input.week; j++) {
            const key = [i, j].join(",");
            this.draw_calendar_color_map(
              j * cellw * scale + left_margin,
              i * cellh + top_margin,
              cellw * scale,
              ((cellh - cellh_margin) * 5) / 7,
              parseInt(frame.query[i].slice(2 * j, 2 * j + 1)),
              frame.loadRate.get(key),
              Math.floor(255 - 510 / (2 + frame.penalty.get(key) / 1000000))
            );
            this.draw_calendar_color_map(
              j * cellw * scale + left_margin,
              i * cellh + ((cellh - cellh_margin) * 5) / 7 + top_margin,
              cellw * scale,
              ((cellh - cellh_margin) * 2) / 7,
              parseInt(frame.query[i].slice(2 * j + 1, 2 * j + 2)),
              frame.loadRate.get(key),
              Math.floor(255 - 510 / (2 + frame.penalty.get(key) / 1000000))
            );
            if (this.scale_level >= detail_level) {
              this.ctx.fillText(
                "cost:" +
                  frame.penalty.get(key).toString() +
                  "/loadRate:" +
                  Math.round(100 * Math.min(1, frame.loadRate.get(key))).toString() +
                  "%",
                (j + 0.5) * cellw * scale + left_margin,
                (i + 0.93) * cellh + top_margin
              );
            }
          }
        }
      }
      if (this.operationcon_cf_Input.checked || this.operationcon_rb_Input.checked) {
        if (this.scale_level >= detail_level) {
          this.ctx.font = "15px serif";
          for (let i = 0; i < tester.input.week; i++) {
            for (let k = 0; k < 7; k++) {
              this.ctx.fillText(
                "day" + (k + 1).toString(),
                (i + (k + 0.5) / 7) * cellw * scale + left_margin,
                top_margin - 7.5
              );
            }
          }
        }
        for (var i = 0; i < tester.input.resourceN; i++) {
          for (var j = 0; j < tester.input.week; j++) {
            for (var k = 0; k < 5; k++) {
              this.draw_calendar(
                cellw * scale * (j + k / 7) + left_margin,
                i * cellh + top_margin,
                (cellw * scale) / 7,
                cellh - cellh_margin,
                parseInt(frame.query[i].slice(2 * j, 2 * j + 1)),
                1,
                200,
                200,
                200
              );
            }
            for (var k = 5; k < 7; k++) {
              this.draw_calendar(
                cellw * scale * (j + k / 7) + left_margin,
                i * cellh + top_margin,
                (cellw * scale) / 7,
                cellh - cellh_margin,
                parseInt(frame.query[i].slice(2 * j + 1, 2 * j + 2)),
                1,
                175,
                175,
                175
              );
            }
          }
        }
        if (this.scale_level == this.scales.length - 1) {
          this.ctx.font = "8px serif";
          this.ctx.fillStyle = "Black";
          for (let i = 0; i < tester.input.resourceN; i++) {
            this.ctx.fillText(
              "op index % 100",
              left_margin / 2,
              (i + 1) * cellh - cellh_margin / 2 + top_margin
            );
          }
        }
        for (var i = 0; i < tester.input.operationN; i++) {
          for (var j = 0; j < tester.input.itemList[tester.input.opList[i].itemNo].itemProcN; j++) {
            const key: string = [i, j].join(",");
            const pc2 = frame.vis2_optimes.get(key);
            console.assert(pc2.length % 2 == 0);
            for (let k = 0; k < pc2.length - 1; k++) {
              if (k % 2 == 0) {
                this.draw_operation(
                  ((pc2[k] - DAY / 4) / 6048) * scale + left_margin, //x
                  (pc2[k + 1] / 6048 - pc2[k] / 6048) * scale, //w
                  frame.vis1_resource.get(key) * cellh + top_margin, //y
                  (cellh - cellh_margin) * 0.8, //h
                  this.operationcon_cf_Input.checked
                    ? i
                    : Math.min(1.0, frame.vis3_waiting_time.get(key) / frame.vis3_waiting_time_mid),
                  true,
                  this.operationcon_cf_Input.checked
                );
              } else {
                this.draw_operation(
                  ((pc2[k] - DAY / 4) / 6048) * scale + left_margin, //x
                  (pc2[k + 1] / 6048 - pc2[k] / 6048) * scale, //w
                  frame.vis1_resource.get(key) * cellh + top_margin, //y
                  (cellh - cellh_margin) * 0.8, //h
                  this.operationcon_cf_Input.checked
                    ? i
                    : Math.min(1.0, frame.vis3_waiting_time.get(key) / frame.vis3_waiting_time_mid),
                  false,
                  this.operationcon_cf_Input.checked
                );
              }
            }
            if (this.scale_level == this.scales.length - 1) {
              this.ctx.fillText(
                ((i + 1) % 100).toString(),
                (((pc2[0] + pc2[pc2.length - 1]) / 2 - DAY / 4) / 6048) * scale + left_margin, //x
                frame.vis1_resource.get(key) * cellh +
                  (cellh - cellh_margin) +
                  cellh_margin / 2 +
                  top_margin //y
              );
            }
          }
        }
      }
    }

    public getCanvas(): HTMLCanvasElement {
      return this.canvas;
    }
  }

  export class App {
    public visualizer: Visualizer;
    public tester: Tester;
    public loader: framework.FileSelector;
    public seek: framework.RichSeekBar;
    public exporter: framework.FileExporter;

    constructor() {
      this.visualizer = new Visualizer();
      this.loader = new framework.FileSelector();
      this.seek = new framework.RichSeekBar();
      this.exporter = new framework.FileExporter(this.visualizer.getCanvas(), this.seek);

      this.seek.callback = (value: number) => {
        if (this.tester !== undefined) {
          this.visualizer.draw(this.tester.frames[value], this.tester);
        }
      };

      this.loader.callback = (inputContent: string, outputContent: string) => {
        this.tester = new Tester(inputContent, outputContent);
        this.seek.setMinMax(0, this.tester.frames.length - 1);
        this.seek.setValue(0);
        this.seek.play();
      };
    }
  }
}

window.onload = () => {
  const App = new visualizer.App();

  const lang_ja_button = document.getElementById("lang_ja_button");
  const lang_en_button = document.getElementById("lang_en_button");
  lang_ja_button.onclick = () => {
    lang_ja_button.classList.add("teal");
    lang_en_button.classList.remove("teal");
    lang = Lang.JA;
    msg = MSG_JA;
  };
  lang_en_button.onclick = () => {
    lang_ja_button.classList.remove("teal");
    lang_en_button.classList.add("teal");
    lang = Lang.EN;
    msg = MSG_EN;
  };
  document.getElementById("modal_button").addEventListener("click", set_modal_content);
  function set_modal_content() {
    const d1 = document.getElementById("description1");
    d1.innerHTML = msg.DESCRIPTION1;
    const d2 = document.getElementById("description2");
    d2.innerHTML = msg.DESCRIPTION2;
    const d3 = document.getElementById("description3");
    d3.innerHTML = msg.DESCRIPTION3;
    ($(".ui.modal") as any).modal("setting", "transition", "fade up").modal("show");
  }

  const vis = App.visualizer;

  vis.letonly_Input.onchange = () => {
    if (App.seek.getValue() === App.seek.getMax()) App.seek.play();
  };
  vis.cost_Input.onchange = () => {
    if (App.seek.getValue() === App.seek.getMax()) App.seek.play();
  };
  vis.operationcon_cf_Input.onchange = () => {
    if (vis.operationcon_cf_Input.checked) {
      if (vis.scale_level < 11) {
        if (vis.scale_level == 0) vis.expansion_minus.disabled = false;
        vis.scale_level = 11;
      }
    }
    if (App.seek.getValue() === App.seek.getMax()) App.seek.play();
  };
  vis.operationcon_rb_Input.onchange = () => {
    if (vis.operationcon_rb_Input.checked) {
      if (vis.scale_level < 11) {
        if (vis.scale_level == 0) vis.expansion_minus.disabled = false;
        vis.scale_level = 11;
      }
    }
    if (App.seek.getValue() === App.seek.getMax()) App.seek.play();
  };
  vis.expansion_minus.onclick = () => {
    if (vis.scale_level == vis.scales.length - 1) vis.expansion_plus.disabled = false;
    if (vis.scale_level > 0) vis.scale_level--;
    if (vis.scale_level == 0) vis.expansion_minus.disabled = true;
    if (!App.seek.now_running) vis.draw(App.tester.frames[App.seek.getValue()], App.tester);
  };
  vis.expansion_plus.onclick = () => {
    if (vis.scale_level == 0) vis.expansion_minus.disabled = false;
    if (vis.scale_level < vis.scales.length - 1) vis.scale_level++;
    if (vis.scale_level == vis.scales.length - 1) vis.expansion_plus.disabled = true;
    if (!App.seek.now_running) vis.draw(App.tester.frames[App.seek.getValue()], App.tester);
  };
};
