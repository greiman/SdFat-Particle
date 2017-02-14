#include "SdFat.h"
// Warning, Particle.timeSync() seems to take a while to happen.
// You may want to set your time zone with Time.zone(offaet).
/*
 * This program tests the dateTimeCallback() function
 * and the timestamp() function.
 */
SdFat sd;

SdFile file;

// Default SD chip select is SS pin
const uint8_t chipSelect = SS;

// create Serial stream
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) sd.errorHalt(F(s))
//------------------------------------------------------------------------------
/*
 * User provided date time callback function.
 * See SdFile::dateTimeCallback() for usage.
 */
void dateTime(uint16_t* date, uint16_t* time) {
  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(Time.year(), Time.month(), Time.day());

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(Time.hour(), Time.minute(), Time.second());
}
//------------------------------------------------------------------------------
/*
 * Function to print all timestamps.
 */
void printTimestamps(SdFile& f) {
  dir_t d;
  if (!f.dirEntry(&d)) {
    error("f.dirEntry failed");
  }

  cout << F("Creation: ");
  f.printFatDate(d.creationDate);
  cout << ' ';
  f.printFatTime(d.creationTime);
  cout << endl;

  cout << F("Modify: ");
  f.printFatDate(d.lastWriteDate);
  cout <<' ';
  f.printFatTime(d.lastWriteTime);
  cout << endl;

  cout << F("Access: ");
  f.printFatDate(d.lastAccessDate);
  cout << endl;
}
//------------------------------------------------------------------------------
void setup(void) {
  Serial.begin(9600);
  // Wait for USB Serial
  while (!Serial) {
    SysCall::yield();
  }
  cout << F("Type any character to start\n");
  while (!Serial.available()) {
    SysCall::yield();  
  }
  
  // Request time sync so example works.
  Particle.syncTime();
  
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) {
    sd.initErrorHalt();
  }

  // remove files if they exist
  sd.remove("callback.txt");
  sd.remove("default.txt");
  sd.remove("stamp.txt");

  // create a new file with default timestamps
  if (!file.open("default.txt", O_CREAT | O_WRITE)) {
    error("open default.txt failed");
  }
  cout << F("\nOpen with default times.\n");
  printTimestamps(file);

  // close file
  file.close();
  /*
   * Test the date time callback function.
   *
   * dateTimeCallback() sets the function
   * that is called when a file is created
   * or when a file's directory entry is
   * modified by sync().
   *
   * The callback can be disabled by the call
   * SdFile::dateTimeCallbackCancel()
   */
   
  // set date time callback function
  SdFile::dateTimeCallback(dateTime);

  cout << F("\nDelay for 10 seconds to insure timeSync happens.\n");
  for (int sec = 0; sec < 10; sec++) {
    delay(1000);
    cout << ' ' << Time.second();
  }
  cout << endl;
  
  // create a new file with callback timestamps
  if (!file.open("callback.txt", O_CREAT | O_WRITE)) {
    error("open callback.txt failed");
  }
  cout << F("\nOpen with callback times\n");
  printTimestamps(file);

  cout << F("\nDelay for 10 seconds before writing to file.\n");
  for (int sec = 0; sec < 10; sec++) {
    delay(1000);
    cout << ' ' << Time.second();
  }
  cout << endl;

  // modify file by writing a byte
  file.write('t');

  // force dir update
  file.sync();

  cout << F("\nTimes after write\n");
  printTimestamps(file);

  // close file
  file.close();
  /*
   * Test timestamp() function
   *
   * Cancel callback so sync will not
   * change access/modify timestamp
   */
  SdFile::dateTimeCallbackCancel();

  // create a new file with default timestamps
  if (!file.open("stamp.txt", O_CREAT | O_WRITE)) {
    error("open stamp.txt failed");
  }
  // set creation date time
  if (!file.timestamp(T_CREATE, 2014, 11, 10, 1, 2, 3)) {
    error("set create time failed");
  }
  // set write/modification date time
  if (!file.timestamp(T_WRITE, 2014, 11, 11, 4, 5, 6)) {
    error("set write time failed");
  }
  // set access date
  if (!file.timestamp(T_ACCESS, 2014, 11, 12, 7, 8, 9)) {
    error("set access time failed");
  }
  cout << F("\nTimes after timestamp() calls\n");
  printTimestamps(file);

  file.close();
  cout << F("\nDone\n");
}

void loop(void) {}
