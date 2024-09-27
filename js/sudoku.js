// 测试输入是否为平方数
const isPerfectSquare = (num) => {
    return Math.sqrt(num) === Math.floor(Math.sqrt(num))
}

class Grid {
    constructor(grid) {
        this._check(grid)
        this.grid = grid
        this.BOX_SIZE = Math.sqrt(grid.length)
        this.GRID_SIZE = grid.length
    }

    get rows () {
        return this.grid
    }

    get columns () {
        return this.grid[0].map((_, i) => this.grid.map(row => row[i]))
    }

    get boxes () {
        const boxes = []
        for (let boxRow = 0; boxRow < this.BOX_SIZE; boxRow++) {
            for (let boxCol = 0; boxCol < this.BOX_SIZE; boxCol++) {
                const box = []
                for (let i = 0; i < this.BOX_SIZE; i++) {
                    for (let j = 0; j < this.BOX_SIZE; j++) {
                        box.push(this.grid[boxRow * this.BOX_SIZE + i][boxCol * this.BOX_SIZE + j])
                    }
                }
                boxes.push(box)
            }
        }
        return boxes
    }

    getRow = row => this.rows[row]

    getColumn = col => this.columns[col]

    getBox = (row, col) => {
        const boxRow = Math.floor(row / this.BOX_SIZE)
        const boxCol = Math.floor(col / this.BOX_SIZE)
        return this.boxes[boxRow * this.BOX_SIZE + boxCol]
    }

    // 生成空grid
    getEmptyGrid = () => Array.from({ length: this.GRID_SIZE }, () => Array(this.GRID_SIZE).fill(0));

    static getEmptyGrid = (num) => Array.from({ length: num }, () => Array(num).fill(0));

    _check = (grid) => {
        if (grid && grid.length != 0 && isPerfectSquare(grid.length)) {
            return
        } else {
            throw new Error("Invalid Grid")
        }

    }
}

class Sudoku extends Grid {

    constructor(input) {
        // 先调用父类的构造函数
        super(Sudoku.parse(input))
        if (!this._check())
            throw new Error("Invalid Sudoku")
    }

    _check = () => this.grid.every(row => row.every(col => col => 0 && col <= this.GRID_SIZE));

    static _checkStr = (input) => typeof input === 'string' && input.length > 0 && parseFloat(input) > 0 && isPerfectSquare(input.length);

    static parse = (input) => {
        if (Sudoku._checkStr(input)) {
            const grid = Grid.getEmptyGrid(Math.sqrt(input.length))
            for (let i = 0; i < Math.sqrt(input.length); i++) {
                for (let j = 0; j < Math.sqrt(input.length); j++) {
                    grid[i][j] = parseInt(input[i * Math.sqrt(input.length) + j])
                }
            }
            return grid
        } else {
            throw new Error("Invalid Input")
        }
    }

    getInference = () => {
        const inference = this.getEmptyGrid()
        for (let i = 0; i < this.GRID_SIZE; i++)
            for (let j = 0; j < this.GRID_SIZE; j++) {
                inference[i][j] = this.grid[i][j] === 0 ? this._getCandidate(i, j) : 0
            }
        return inference
    }

    _getCandidate = (row, col) => {
        const candidate = Array.from({ length: this.GRID_SIZE }, (_, i) => i + 1)
        // 过滤掉同行同列同box的数
        return candidate.filter(num => !this.getBox(row, col).includes(num) && !this.getColumn(col).includes(num) && !this.getRow(row).includes(num))
    }
}
