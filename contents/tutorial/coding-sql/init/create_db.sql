DROP TABLE IF EXISTS inventories;
CREATE TABLE inventories (
    id       integer PRIMARY KEY AUTOINCREMENT,
    name     varchar NOT NULL,
    quantity integer NOT NULL
);
