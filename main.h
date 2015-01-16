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
  Serial.begin(9600);

  for (int thisPin = 0; thisPin < gridSize; thisPin++){
      //we initialize the pins as output's
      pinMode(col[thisPin], OUTPUT);
      pinMode(row[thisPin], OUTPUT);

      // now we have to make the columns high so that all the LED's will be off
      digitalWrite(col[thisPin], HIGH);
  }
}

void loop() {
  lightRow(0);
}

void lightAllDiagonal() {
  for ( int Pin = 0; Pin < gridSize; Pin++){
    setPoint(Pin, Pin, true);
  }
}

void unlightAllDiagonal() {
  for ( int Pin = 0; Pin < gridSize; Pin++){
    setPoint(Pin, Pin, false);
  }
}

void lightColumn(int colId) {
  setColumn(colId, true);
}

void unlightColumn(int colId) {
  setColumn(colId, false);
}

void setColumn(int colId, bool isLit) {
  for ( int Pin = 0; Pin < gridSize; Pin++) {
    setPoint(colId, Pin, isLit);
  }
}

void lightRow(int rowId) {
  setRow(rowId, true);
}

void unlightRow(int rowId) {
  setRow(rowId, false);
}

void setRow(int rowId, bool isLit) {
  for ( int Pin = 0; Pin < gridSize; Pin++) {
    setPoint(Pin, rowId, isLit);
  }
}

void lightPoint(int colId, int rowId) {
  setPoint(colId, rowId, true);
}

void unlightPoint(int colId, int rowId, bool isLit) {
  setPoint(colId, rowId, false);
}

void setPoint(int colId, int rowId, bool isLit) {
  digitalWrite( row[rowId], (isLit) ? (HIGH) : (LOW)); // the anode is high
  digitalWrite( col[colId], (isLit) ? (LOW) : (HIGH));   // the cathode is low

  // this turn the led on now we have to let the led on for some time .... 1 microsecond is enough
  delayMicroseconds(1);

  //now we have tu turn it off so we will inverse the polarity
  digitalWrite( row[rowId], (isLit) ? (LOW) : (HIGH));  // the anode is low
  digitalWrite( col[colId], (isLit) ? (HIGH) : (LOW));  // the cathode is high

  //we have turn the led off, next delay it 1 microsecond and  go to the next row
  delayMicroseconds(1);
}
