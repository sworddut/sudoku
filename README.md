# Sudoku项目

本项目是面向对象编程课程作业，分别使用C++和JavaScript编写，实现了数独游戏的用户自定义输入与提示等功能。



## JavaScript子项目

主要功能被定义在`sudoku.js`文件中，得益于JavaScript被各浏览器广泛地支持，本项目制作了一个简易界面，用于更好地实现用户交互和功能展示，这些ui逻辑被定义在`index.html`中。

### 主要功能的实现:

首先设置一个Grid类，实现基本功能的方法（方法具体内容省略），包括构造grid，对输入进行检查，读取行列以及box。

```javascript
class Grid {
    constructor(grid) 
    get rows () {...}
    get columns () {...}
    get boxes () {...}
    getRow = row => {...}
    getColumn = col => {...}
    getBox = (row, col) => {...}
    // 生成空grid
    getEmptyGrid = () => {...}
    static getEmptyGrid = (num) => {...}
    _check = (grid) => {...}
}
```

随后基于Grid类实现Sudoku类，实现基本功能的方法（方法具体内容省略），包括构造sudoku，对输入进行检查，完成字符串向二维数组的转化以及得到提示值。

```Javascript
class Sudoku extends Grid {
    constructor(input) {...}
    _check = () => {...}
    static _checkStr = (input) => {...}
    static parse = (input) => {...}
    getInference = () => {...}
    _getCandidate = (row, col) => {...}
}
```

为了后续更好地调用，上面的某些方法被标注为`static`方法。

## UI界面的编写

在`index.html`中，调用了`sudoku.js`，来实例化sudoku，编写了一个html元素并注册了一些监听事件，以方便用户的使用。具体实现省略。

本项目为纯静态网页，已部署至http://8.130.122.11:5500/static/shudo/index.html





## C++子项目

实现逻辑与js子项目类似，都是先构造Grid类再基于此实现Sudoku类。不同是为了实现可视化需要增加若干`show`函数。

