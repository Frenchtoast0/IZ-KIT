CREATE TABLE Info(
  ID          INT           NOT NULL,
  name        VARCHAR(20)   NOT NULL,
  description VARCHAR(50)   NOT NULL,
  type        BINARY        NOT NULL,
  CONSTRAINT PK_Info PRIMARY KEY (ID)
);

CREATE TABLE State(
  ID          INT           NOT NULL UNIQUE,
  state DECIMAL       DEFAULT 0 NOT NULL,
  FOREIGN KEY (ID) REFERENCES Info(ID)
);

CREATE TABLE Users(
  ID        INT           NOT NULL AUTO_INCREMENT,
  username  VARCHAR(20)   NOT NULL,
  password  VARCHAR(50)   NOT NULL,
  CONSTRAINT PK_Users PRIMARY KEY (ID)
);

CREATE TABLE Configs(
  ID        INT           NOT NULL AUTO_INCREMENT,
  userId    INT           NOT NULL,
  filename  VARCHAR(20)   NOT NULL,
  CONSTRAINT PK_Configs PRIMARY KEY (ID),
  FOREIGN KEY (userId) REFERENCES Users(ID)
);

CREATE TABLE Events(
  ID        INT       NOT NULL AUTO_INCREMENT,
  deviceId  INT       NOT NULL,
  onState   DECIMAL   DEFAULT 0 NOT NULL,
  CONSTRAINT PK_Events PRIMARY KEY (ID),
  FOREIGN KEY (deviceId) REFERENCES State(ID)
);

CREATE TABLE Listeners(
  ID            INT       NOT NULL AUTO_INCREMENT,
  deviceId      INT       NOT NULL,
  appendState   DECIMAL   DEFAULT 0 NOT NULL,
  CONSTRAINT PK_Listeners PRIMARY KEY (ID),
  FOREIGN KEY (deviceId) REFERENCES State(ID)
);

CREATE TABLE ListenersToEvents(
  ID          INT       NOT NULL AUTO_INCREMENT,
  listenerId  INT       NOT NULL UNIQUE,
  eventId     INT       NOT NULL,
  CONSTRAINT PK_Events PRIMARY KEY (ID),
  FOREIGN KEY (listenerId) REFERENCES Listeners(ID),
  FOREIGN KEY (eventId) REFERENCES Events(ID)
);
