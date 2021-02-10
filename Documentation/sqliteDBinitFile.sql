--onlinux transfer file using the command: scp [this File] pi@[IP of pi]:/var/www/db/
--on server create db by: sqlite3 izkit.db < [this file].sql
--TODO connect pi to git

CREATE TABLE Info(
  ID          INT PRIMARY KEY NOT NULL,
  name        VARCHAR(20)   NOT NULL,
  description VARCHAR(50)   NOT NULL,
  type        BINARY        NOT NULL
);

CREATE TABLE State(
  ID          INT           NOT NULL UNIQUE,
  state DECIMAL       DEFAULT 0 NOT NULL,
  FOREIGN KEY (ID) REFERENCES Info(ID)
);


CREATE TABLE Users(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
  username  VARCHAR(20)   NOT NULL,
  password  VARCHAR(50)   NOT NULL
);

CREATE TABLE Configs(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
  userId    INTEGER       NOT NULL,
  filename  VARCHAR(20)   NOT NULL,
  FOREIGN KEY(userId) REFERENCES Users(ID)
);

CREATE TABLE Events(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
  deviceId  INT       NOT NULL,
  onState   DECIMAL   DEFAULT 0 NOT NULL,
  FOREIGN KEY(deviceId) REFERENCES Device(ID)
);

CREATE TABLE Listeners(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
  deviceId      INT       NOT NULL,
  modState   DECIMAL   DEFAULT 0 NOT NULL,
  FOREIGN KEY(deviceId) REFERENCES Device(ID)
);

CREATE TABLE ListenersToEvents(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
  listenerId  INT       NOT NULL UNIQUE,
  eventId     INT       NOT NULL,
  FOREIGN KEY(eventId) REFERENCES Events(ID),
  FOREIGN KEY(listenerId) REFERENCES Listeners(ID)
);
