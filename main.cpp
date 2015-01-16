int incomingByte = 0;

const int gridSize = 2;

const int pinOffset = 2;
const int rowStartingPoint = gridSize + pinOffset;
const int colStartingPoint = (gridSize * 2) + pinOffset;

//const int row[gridSize] = { gridSize, gridSize + 1 }; // the anodes
//const int col[gridSize] = { offset, offset + 1 }; // the cathodes

const int row[gridSize] = { 2, 3 }; // the anodes
const int col[gridSize] = { 4, 5 }; // the cathodes

void setup() {
  for (int thisPin = 0; thisPin < gridSize; thisPin++){
      //we initialize the pins as output's
      pinMode(col[thisPin], OUTPUT);
      pinMode(row[thisPin], OUTPUT);

      // now we have to make the columns high so that all the LED's will be off
      digitalWrite(col[thisPin], HIGH);
  }
}

class Led {
  private:
    int _x_coord;
    int _y_coord;

  public:
    Led (int x_coord, int y_coord) {
      _x_coord = x_coord;
      _y_coord = y_coord;
    }

    void light () {
      set(true);
    }

    void unlight () {
      set(false);
    }

    void set (int isLit) {
      digitalWrite( row[_x_coord], (isLit) ? (HIGH) : (LOW)); // the anode is high
      digitalWrite( col[_y_coord], (isLit) ? (LOW) : (HIGH));   // the cathode is low

      // this turn the led on now we have to let the led on for some time .... 1 microsecond is enough
      delayMicroseconds(1);

      //now we have tu turn it off so we will inverse the polarity
      digitalWrite( row[_x_coord], (isLit) ? (LOW) : (HIGH));  // the anode is low
      digitalWrite( col[_y_coord], (isLit) ? (HIGH) : (LOW));  // the cathode is high

      //we have turn the led off, next delay it 1 microsecond and  go to the next row
      delayMicroseconds(1);
    }
};

class Row {
  private:
    int size;
    int _x_coord;

  public:
    Row (int size, int x_coord) {
      _x_coord = x_coord;
    }

    void light () {
      set(true);
    }

    void unlight () {
      set(false);
    }

    void set (int isLit) {
      for ( int y_coord = 0; y_coord < gridSize; y_coord++) {
        setPoint(y_coord, _x_coord, isLit);
      }
    }
};

class Column {
  private:
    int size;
    int _y_coord;

  public:
    Column (int size, int y_coord) {
      _y_coord = y_coord;
    }

    void light () {
      set(true);
    }

    void unlight () {
      set(false);
    }

    void set (int isLit) {
      for ( int x_coord = 0; x_coord < gridSize; x_coord++) {
        setPoint(_y_coord, x_coord, isLit);
      }
    }
};

class Diagonal {
  private:
    int size;
    int _y_coord;

  public:
    Diagonal (int size) {}

    void light () {
      set(true);
    }

    void unlight () {
      set(false);
    }

    void set (int isLit) {
      for ( int pin = 0; pin < gridSize; pin++){
        setPoint(pin, pin, isLit);
      }
    }
};
void loop() {
  setDiagonal(true);
}

void setDiagonal(bool isLit) {
  Diagonal diagInstance(gridSize);
  diagInstance.set(isLit);
}

void setColumn(int colId, bool isLit) {
  Column colInstance(gridSize, colId);
  colInstance.set(isLit);
}

void setRow(int rowId, bool isLit) {
  Row rowInstance(gridSize, rowId);
  rowInstance.set(isLit);
}

void setPoint(int colId, int rowId, bool isLit) {
  Led ledInstance(colId, rowId);
  ledInstance.set(isLit);
}
