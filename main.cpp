class Matrix {
  private:
    int _gridSize;
    int _pinOffset;
    void setPinsToOutput();
  public:
    Matrix (int pinOffset, int gridSize);
    int getPinForXCoord(int xCoord);
    int getPinForYCoord(int yCoord);
    void setup();
};

Matrix::Matrix (int pinOffset, int gridSize) {
  _gridSize = gridSize;
  _pinOffset = pinOffset;
}

void Matrix::setup () {
   setPinsToOutput();
}

int Matrix::getPinForXCoord (int xCoord) {
  return _pinOffset + xCoord;
}

int Matrix::getPinForYCoord (int yCoord) {
  return _pinOffset + _gridSize + yCoord;
}

void Matrix::setPinsToOutput () {
  for (int thisPin = 0; thisPin < _gridSize; thisPin++){
    pinMode(getPinForXCoord(thisPin), OUTPUT);
    pinMode(getPinForYCoord(thisPin), OUTPUT);

    // now we have to make the columns high so that all the LED's will be off
    digitalWrite(getPinForYCoord(thisPin), HIGH);
  }
};

Matrix matrix(2, 2);

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
      digitalWrite( matrix.getPinForXCoord(_x_coord), (isLit) ? (HIGH) : (LOW)); // the anode is high
      digitalWrite( matrix.getPinForYCoord(_y_coord), (isLit) ? (LOW) : (HIGH));   // the cathode is low

      // this turn the led on now we have to let the led on for some time .... 1 microsecond is enough
      delayMicroseconds(1);

      //now we have tu turn it off so we will inverse the polarity
      digitalWrite( matrix.getPinForXCoord(_x_coord), (isLit) ? (LOW) : (HIGH));  // the anode is low
      digitalWrite( matrix.getPinForYCoord(_y_coord), (isLit) ? (HIGH) : (LOW));  // the cathode is high

      //we have turn the led off, next delay it 1 microsecond and  go to the next row
      delayMicroseconds(1);
    }
};







// =========================================================>


void setup() {
  matrix.setup();
}

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
